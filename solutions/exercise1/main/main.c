/**
 * A possible solution to exercise 1:
 * - Right after reset, the detection LED is off
 * - Pressing on the side button and keeping it pressed turns the LED on
 * - Releasing the button turns the LED off
 */

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"
#include "esp_log.h"

// Side button is connected to GPIO15 (check the schematic).
#define GPIO_SIDE_BUTTON GPIO_NUM_15
// Detection LED is controlled by GPIO 21 (check the schematic).
#define GPIO_DETECT_LED GPIO_NUM_21

// Wait period between two successive checks of the button press
// flag, in ms.
#define CHECK_PERIOD_MS 100

static const char TAG[] = "EX1";

static volatile bool press_detected;

typedef enum {
    SWITCH_PRESS,
    SWITCH_RELEASE,
} switch_direction_t;

static const char SWITCH_RELEASED_STR[] = " released";
static const char SWITCH_PRESSED_STR[] = " pressed";

static volatile switch_direction_t switch_direction;

// GPIO interrupt handler.
static void gpio_interrupt_handler(void *arg) {

    press_detected = true;
    if (gpio_get_level(GPIO_SIDE_BUTTON) == 0) {
        switch_direction = SWITCH_PRESS;
    } else {
        switch_direction = SWITCH_RELEASE;
    }

}

// Returns true if initialization succeeds, false otherwise.
static bool init_led(void) {

    // Select GPIO function for the pin, enable pull-up, disable I/O.
    // No need to check returned status: it is always ESP_OK.
    gpio_reset_pin(GPIO_DETECT_LED);
    // Disable pull-up, as there is an external pull-down.
    esp_err_t rs = gpio_set_pull_mode(GPIO_DETECT_LED, GPIO_FLOATING);
    if (rs != ESP_OK) {
        ESP_LOGE(TAG, "Error from gpio_set_pull_mode: %s", esp_err_to_name(rs));
        return false;
    }
    rs = gpio_set_direction(GPIO_DETECT_LED, GPIO_MODE_OUTPUT);
    if (rs != ESP_OK) {
        ESP_LOGE(TAG, "Error from gpio_set_direction: %s", esp_err_to_name(rs));
        return false;
    }
    return true;

}

// Returns true if initialization succeeds, false otherwise.
static bool init_button(void) {

    // Let's configure the GPIO.
    gpio_config_t io_conf = {0};
    // Pin bit mask is 64-bit long => ULL suffix.
    io_conf.pin_bit_mask = (1ULL << GPIO_NUM_15);
    io_conf.mode = GPIO_MODE_INPUT;
    // Activate internal pull-up so that when the button is not pushed,
    // GPIO level is 3.3 V.
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    // Disable interrupts while configuring.
    io_conf.intr_type = GPIO_INTR_DISABLE;
    esp_err_t es_rs = gpio_config(&io_conf);
    if (es_rs != ESP_OK) {
        ESP_LOGE(TAG, "Error from gpio_config: %s",
                 esp_err_to_name(es_rs));
        return false;
    }
    // At this stage, GPIO configuration is OK.
    press_detected = false;
    // Now, configure interruption.
    // Assign the interrupt handler.
    es_rs = gpio_isr_handler_add(GPIO_NUM_15, gpio_interrupt_handler,
                                 NULL);
    if (es_rs != ESP_OK) {
        ESP_LOGE(TAG, "Error from gpio_isr_handler_add: %s",
                esp_err_to_name(es_rs));
        return false;
    }
    // Now, enable interrupt for the GPIO.
    es_rs = gpio_set_intr_type(GPIO_NUM_15, GPIO_INTR_ANYEDGE);
    if (es_rs != ESP_OK) {
        ESP_LOGE(TAG, "Error from gpio_set_intr_type: %s",
                esp_err_to_name(es_rs));
        return false;
    }
    return true;

}

void app_main(void) {

    // Install GPIO ISR service. According to Espressif's
    // gpio_example_main.c example, 0 seems to be a good value for the
    // argument to gpio_install_isr_service.
    esp_err_t es_rs = gpio_install_isr_service(0);
    if (es_rs != ESP_OK) {
            ESP_LOGE(TAG, "Error from gpio_install_isr_service: %s",
                     esp_err_to_name(es_rs));
            goto exit_on_fatal_error;
        }

    bool bool_rs = init_led();
    if (!bool_rs) goto exit_on_fatal_error;

    bool_rs = init_button();
    if (!bool_rs) goto exit_on_fatal_error;

    // Now, check the global flag.
    while (true) {
        if (press_detected) {
            press_detected = false;
            char *state_str;
            if (switch_direction == SWITCH_PRESS) {
                state_str = (char *)SWITCH_PRESSED_STR;
                // Set LED on.
                es_rs = gpio_set_level(GPIO_DETECT_LED, 1);
                if (es_rs != ESP_OK) {
                    ESP_LOGE(TAG, "Error from gpio_set_level: %s", esp_err_to_name(es_rs));
                    goto exit_on_fatal_error;
                }

            } else {
                state_str = (char *)SWITCH_RELEASED_STR;
                // Set LED off.
                es_rs = gpio_set_level(GPIO_DETECT_LED, 0);
                if (es_rs != ESP_OK) {
                    ESP_LOGE(TAG, "Error from gpio_set_level: %s", esp_err_to_name(es_rs));
                    goto exit_on_fatal_error;
                }
            }
            ESP_LOGI(TAG, "Switch new state detected: %s", state_str);
        }
        // Call a FreeRTOS function, to be sure not to trigger the task
        // watchdog.
        vTaskDelay(pdMS_TO_TICKS(CHECK_PERIOD_MS));
    }

    exit_on_fatal_error:
    ESP_LOGI(TAG, "Exiting");

}
