/**
 * A possible solution to exercise 2.
 */
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"

#define MAIN_PERIOD_MS 1000
#define TASK1_MSG_PERIOD_MS 2000
#define TASK2_MSG_PERIOD_MS 2300

#define TASK1_STACK_DEPTH (10000 - 8300)
#define TASK2_STACK_DEPTH 10000

#define TASK1_PRIORITY 5
#define TASK2_PRIORITY 5

static const char TAG[] = "TSK";

static void task1(void *taskParameters) {

    // A function implementing a task must not return, unless
    // it deletes itself.
    while (true) {
        ESP_LOGI(TAG, "Hello from task1");
        vTaskDelay(pdMS_TO_TICKS(TASK1_MSG_PERIOD_MS));
    }
}

static void task2(void *taskParameters) {

    // A function implementing a task must not return, unless
    // it deletes itself.
    while (true) {
        ESP_LOGI(TAG, "Hello from task2");
        vTaskDelay(pdMS_TO_TICKS(TASK2_MSG_PERIOD_MS));
    }
}

void app_main(void) {

    TaskHandle_t task1_handle;

    // Start first task.
    BaseType_t rs = xTaskCreate(task1, "task1", TASK1_STACK_DEPTH,
                                NULL, TASK1_PRIORITY, &task1_handle);
    if (rs != pdPASS) {
        ESP_LOGE(TAG, "Error from xTaskCreate");
        goto exit_on_fatal_error;
    }

    // Start second task.
    rs = xTaskCreate(task2, "task2", TASK2_STACK_DEPTH,
                     NULL, TASK1_PRIORITY, NULL);
    if (rs != pdPASS) {
        ESP_LOGE(TAG, "Error from xTaskCreate");
        goto exit_on_fatal_error;
    }

    // Now, enter an infinite loop, so that the tasks are not deleted.
    uint32_t iteration_nb = 1;
    UBaseType_t high_water_mark;
    while  (true) {
        vTaskDelay(pdMS_TO_TICKS(MAIN_PERIOD_MS));
        // Display stack water mark information for task 1.
        if (iteration_nb % 10 == 0) {
            high_water_mark = uxTaskGetStackHighWaterMark(task1_handle);
            ESP_LOGI(TAG, "High water mark: %u", high_water_mark);
        }
        if (iteration_nb == UINT32_MAX) {
            iteration_nb = 0;
        } else {
            iteration_nb++;
        }
    }

    exit_on_fatal_error:
    ESP_LOGE(TAG, "Exiting");
}
