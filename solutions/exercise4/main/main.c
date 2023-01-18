/**
 * Possible solution to exercise 4.
 */
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"

#include "esp_log.h"

#define TASK1_MSG_PERIOD_MS 2000
#define TASK2_MSG_PERIOD_MS 2300

#define TASK1_STACK_DEPTH 10000
#define TASK2_STACK_DEPTH 10000

#define TASK1_PRIORITY 5
#define TASK2_PRIORITY 5

// Wait time for xQueueReceive(), in ms.
static const uint32_t WAIT_QUEUE_REC_PERIOD_MS = 60000;

static const UBaseType_t QUEUE_LENGTH = 2;

static const char TAG[] = "MSG";

// Message types we use.
typedef enum {
    MSG_TASK1,
    MSG_TASK2,
} msg_type_t;

// In this sample application, a message is made of a message type and
// of a counter.
typedef struct {
    msg_type_t type;
    uint32_t counter;
} msg_t;

typedef struct {
    uint8_t task_number;
    uint8_t msg_type;
    uint32_t wait_period_ms;
    uint32_t *counter;
} task_param_t;

// Our queue.
static QueueHandle_t queue;

static void task_body(task_param_t *taskParameters) {

    // Get task configuration.
    uint8_t task_number = taskParameters->task_number;
    uint8_t msg_type = taskParameters->msg_type;
    uint32_t wait_period_ms = taskParameters->wait_period_ms;
    uint32_t *counter = taskParameters->counter;

    while (true) {
        ESP_LOGI(TAG, "Task %d is sending a message", task_number);
        msg_t msg = {msg_type, *counter};
        // xQueueSend makes its own copy of msg. So that's not a problem to
        // use a pointer to an automatic variable as argument.
        BaseType_t rs = xQueueSend(queue, &msg, 0);
        if (rs != pdTRUE) {
            ESP_LOGE(TAG, "Task %d - Error from xQueueSend: %d", task_number, rs);
        }
        // Nothing special is done when counter wraps.
        (*counter)++;
        // Wait a bit before next transmission.
        vTaskDelay(pdMS_TO_TICKS(wait_period_ms));
    }
}

void app_main(void) {

    msg_t msg;

    // Delay used for xTicksToWait when calling xQueueReceive().
    const TickType_t delay_queue_rec = pdMS_TO_TICKS(WAIT_QUEUE_REC_PERIOD_MS);

    // Create the queue.
    queue = xQueueCreate(QUEUE_LENGTH, sizeof(msg_t));
    if (queue == NULL) {
        ESP_LOGE(TAG, "Error from xQueueCreate");
        goto exit_on_fatal_error;
    }

    // Start tasks.
    uint32_t task1_counter = 0;
    task_param_t task1_param = {1, MSG_TASK1, TASK1_MSG_PERIOD_MS, &task1_counter};
    BaseType_t rs = xTaskCreate((TaskFunction_t)task_body, "task1", TASK1_STACK_DEPTH,
                                &task1_param, TASK1_PRIORITY, NULL);
    if (rs != pdPASS) {
        ESP_LOGE(TAG, "Error from xTaskCreate");
        goto exit_on_fatal_error;
    }
    uint32_t task2_counter = 0;
    task_param_t task2_param = {2, MSG_TASK2, TASK2_MSG_PERIOD_MS, &task2_counter};
    rs = xTaskCreate((TaskFunction_t)task_body, "task2", TASK2_STACK_DEPTH,
                     &task2_param, TASK1_PRIORITY, NULL);
    if (rs != pdPASS) {
        ESP_LOGE(TAG, "Error from xTaskCreate");
        goto exit_on_fatal_error;
    }

    while (true) {

        // Wait for an incoming message.
        BaseType_t fr_rs = xQueueReceive(queue, &msg, delay_queue_rec);
        if (fr_rs != pdTRUE) {
            ESP_LOGI(TAG, "End of wait for xQueueReceive");
            continue;
        }
        // At this stage, we have message. Check which one.
        switch (msg.type) {
        case MSG_TASK1:
            ESP_LOGI(TAG, "Message from task 1 - %u", msg.counter);
            break;
        case MSG_TASK2:
            ESP_LOGI(TAG, "Message from task 2 - %u", msg.counter);
            break;
        default:
            // Error!
            ESP_LOGE(TAG, "Unknown message type: %d", msg.type);
            goto exit_on_fatal_error;
        }

    }

    exit_on_fatal_error:
    ESP_LOGI(TAG, "Exiting");

}
