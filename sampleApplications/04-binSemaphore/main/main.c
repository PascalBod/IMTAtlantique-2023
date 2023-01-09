/**
 * This sample application demonstrates how to use a binary semaphore to
 * synchronize a task with an ISR.
 */

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"

#include "driver/gpio.h"
#include "esp_log.h"

#define MAIN_PERIOD_MS 1000

// Side button is connected to GPIO15 (check the schematic).
#define GPIO_SIDE_BUTTON GPIO_NUM_15
// Wait period between two successive checks of the button press
// flag, in ms.
#define CHECK_PERIOD_MS 100

// Wait period for the semaphore take operation, in ms.
#define TAKE_PERIOD_MS 10000

#define TASK_STACK_DEPTH 3000

#define TASK_PRIORITY 5

static const char TAG[] = "SEM";

static SemaphoreHandle_t press_semaphore = NULL;

// GPIO interrupt handler.
static void gpio_interrupt_handler(void *arg) {

    BaseType_t higher_priority_task_woken = pdFALSE;

    xSemaphoreGiveFromISR(press_semaphore, &higher_priority_task_woken);

    if (higher_priority_task_woken) {
        // We must allow the higher priority task to be scheduled.
        portYIELD_FROM_ISR();
    }

}

// Processing task.
static void process_press(void *taskParameters) {

    // A function implementing a task must not return, unless
    // it deletes itself.
    while (true) {
        if (xSemaphoreTake(press_semaphore,
                           pdMS_TO_TICKS(TAKE_PERIOD_MS)) == pdTRUE) {
            ESP_LOGI(TAG, "Press detected");
        } else {
            ESP_LOGI(TAG, "Semaphore take expired");
        }
    }
}


void app_main(void) {

    // Create binary semaphore which will be used by the processing
    // task to wait for a press on the side button.
    press_semaphore = xSemaphoreCreateBinary();

    // Install GPIO ISR service. According to Espressif's
    // gpio_example_main.c example, 0 seems to be a good value for the
    // argument to gpio_install_isr_service.
    esp_err_t es_rs = gpio_install_isr_service(0);

    if (es_rs != ESP_OK) {
            ESP_LOGE(TAG, "Error from gpio_install_isr_service: %s",
                     esp_err_to_name(es_rs));
            goto exit_on_fatal_error;
        }

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
    es_rs = gpio_config(&io_conf);
    if (es_rs != ESP_OK) {
        ESP_LOGE(TAG, "Error from gpio_config: %s",
                 esp_err_to_name(es_rs));
        goto exit_on_fatal_error;
    }
    // At this stage, GPIO configuration is OK.
    // Now, configure interruption.
    // Assign the interrupt handler.
    es_rs = gpio_isr_handler_add(GPIO_NUM_15, gpio_interrupt_handler,
                                 NULL);
    if (es_rs != ESP_OK) {
        ESP_LOGE(TAG, "Error from gpio_isr_handler_add: %s",
                esp_err_to_name(es_rs));
        goto exit_on_fatal_error;
    }
    // Now, enable interrupt for the GPIO.
    es_rs = gpio_set_intr_type(GPIO_NUM_15, GPIO_INTR_NEGEDGE);
    if (es_rs != ESP_OK) {
        ESP_LOGE(TAG, "Error from gpio_set_intr_type: %s",
                esp_err_to_name(es_rs));
        goto exit_on_fatal_error;
    }

    // Start the task which will process the press.
    BaseType_t rs = xTaskCreate(process_press, "process_press", TASK_STACK_DEPTH,
                     NULL, TASK_PRIORITY, NULL);
    if (rs != pdPASS) {
        ESP_LOGE(TAG, "Error from xTaskCreate");
        goto exit_on_fatal_error;
    }

    exit_on_fatal_error:
    ESP_LOGI(TAG, "Exiting app_main");

}
