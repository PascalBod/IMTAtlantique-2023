/**
 * This sample application demonstrates how to control the detection LED
 * of the ESP-EYE board.
 */

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"
#include "esp_log.h"

// Detection LED is controlled by GPIO 21 (check the schematic).
#define GPIO_DETECT_LED GPIO_NUM_21
// Blinking half period, in ms.
#define BLINK_PERIOD_MS 100

static const char TAG[] = "LED";

void app_main(void)
{
	esp_err_t rs;

	// Select GPIO function for the pin, enable pullup, disable I/O.
	// No need to check returned status: it is always ESP_OK.
	gpio_reset_pin(GPIO_DETECT_LED);
	// Disable pullup, as there is an external pulldown.
	rs = gpio_set_pull_mode(GPIO_DETECT_LED, GPIO_FLOATING);
	if (rs != ESP_OK) {
		ESP_LOGE(TAG, "Error from gpio_set_pull_mode: %s", esp_err_to_name(rs));
		goto exit_on_fatal_error;
	}
	rs = gpio_set_direction(GPIO_DETECT_LED, GPIO_MODE_OUTPUT);
	if (rs != ESP_OK) {
		ESP_LOGE(TAG, "Error from gpio_set_direction: %s", esp_err_to_name(rs));
		goto exit_on_fatal_error;
	}
	uint32_t led_level = 0;
	rs = gpio_set_level(GPIO_DETECT_LED, led_level);
	if (rs != ESP_OK) {
		ESP_LOGE(TAG, "Error from gpio_set_level: %s", esp_err_to_name(rs));
		goto exit_on_fatal_error;
	}

    while (true) {
        ESP_LOGI(TAG, "Waiting...");
        vTaskDelay(pdMS_TO_TICKS(BLINK_PERIOD_MS));
        ESP_LOGI(TAG, "Switching LED...");
        if (led_level == 0) {
        	led_level = 1;
        } else {
        	led_level = 0;
        }
    	rs = gpio_set_level(GPIO_DETECT_LED, led_level);
    	if (rs != ESP_OK) {
    		ESP_LOGE(TAG, "Error from gpio_set_level: %s", esp_err_to_name(rs));
    		goto exit_on_fatal_error;
    	}
    }

	exit_on_fatal_error:
	ESP_LOGI(TAG, "Exiting");
}
