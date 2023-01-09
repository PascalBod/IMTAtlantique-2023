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

// Our queue.
static QueueHandle_t queue;

static void task1(void *taskParameters) {

    // This static is not the same type of static as for queue variable.
    static uint32_t counter = 0;

    while (true) {
        ESP_LOGI(TAG, "Task 1 is sending a message");
        msg_t msg = {MSG_TASK1, counter};
        // xQueueSend makes its own copy of msg. So that's not a problem to
        // use a pointer to an automatic variable as argument.
        BaseType_t rs = xQueueSend(queue, &msg, 0);
        if (rs != pdTRUE) {
            ESP_LOGE(TAG, "Task 1 - Error from xQueueSend: %d", rs);
        }
        // Nothing special is done when counter wraps.
        counter++;
        // Wait a bit before next transmission.
        vTaskDelay(pdMS_TO_TICKS(TASK1_MSG_PERIOD_MS));
    }
}

static void task2(void *taskParameters) {

    static uint32_t counter = 0;

    while (true) {
        ESP_LOGI(TAG, "Task 2 is sending a message");
        msg_t msg = {MSG_TASK2, counter};
        // xQueueSend makes its own copy of msg. So that's not a problem to
        // use a pointer to an automatic variable as argument.
        BaseType_t rs = xQueueSend(queue, &msg, 0);
        if (rs != pdTRUE) {
            ESP_LOGE(TAG, "Task 2 - Error from xQueueSend: %d", rs);
        }
        // Nothing special is done when counter wraps.
        counter++;
        // Wait a bit before next transmission.
        vTaskDelay(pdMS_TO_TICKS(TASK2_MSG_PERIOD_MS));
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
    BaseType_t rs = xTaskCreate(task1, "task1", TASK1_STACK_DEPTH,
                                NULL, TASK1_PRIORITY, NULL);
    if (rs != pdPASS) {
        ESP_LOGE(TAG, "Error from xTaskCreate");
        goto exit_on_fatal_error;
    }
    rs = xTaskCreate(task2, "task2", TASK2_STACK_DEPTH,
                     NULL, TASK1_PRIORITY, NULL);
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
