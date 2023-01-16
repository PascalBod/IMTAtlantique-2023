# Skeleton app for insertion of inference code

## Environment

The target board is the ESP-EYE board.

The development environment is ESP-IDF version ?

## Functional point of view

This sample code provides the following skeleton application, at a functional point of view:
* When the user clicks on the side button, the camera starts returning a stream of pictures
* Every picture is sent to a function provided by the user. This function may perform some processing on the picture
* When the user function is done, it can call a function provided by the skeleton, which will set the detection LED on for a short period of time

## Technical point of view

The architecture of the skeleton application relies on the following elements:
* Several tasks are running
* A first task, named the *button task*, is in charge of detecting a press on the side button
* A second task, named the *led task*, is in charge of controlling the detection LED
* A third task, named the *camera task*, is in charge of starting and stopping the camera component provided by ESP-WHO
* A fourth task, named the *frame task*, receives the camera frames provided by the camera component, and calls the user function
* A fifth task, named the *main task*:
  * Waits for a message from the button task, which tells it that the button has been pressed
  * Tells the camera task to start the camera
  * Waits for a second press on the button, which would indicate that the camera has to be stopped
* The led task waits for a message from the frame task, which tells it to set the LED on for a short period of time

Commnunication between tasks is implemented with message queues.

The following picture depicts inter-task communication:

```
+--------+                                                        +------------+
| button |                                          . . . . . . . | esp-camera |
+--------+                                          .             +------------+
    |                                               .                    |
    |  BUTTON_PRESSED    +------+  START/STOP  +--------+                | FRAME
    +------------------->| main |------------->| camera |                |
                         +------+              +--------+                v
                                                                     +-------+
                                                                     | frame |
                                                                     +-------+
                                                                         |
                                                                         | ON
                                                                         |
                                                                         v
                                                                      +-----+
                                                                      | led |
                                                                      +-----+
```

If the user function preempts a core for too long a period, ESP-IDF core watchdog will reset the application. The current watchog timeout period is set to 5 seconds. It can be increased with in *sdkconfig*: **Component Config > ESP System Settings > Task Watchdog imeout period**.

