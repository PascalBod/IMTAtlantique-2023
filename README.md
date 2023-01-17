# IMT Atlantique - 2023 - OS for embedded devices

## Embedded software development

### Communication

* [Webex link](https://imt-atlantique.webex.com/meet/MSc-IT)
* [Mattermost link](https://mattermost.imt-atlantique.fr/mooc-plido/channels/os-and-ml)

### Schedule

* Tue 03-Jan - 09:30-10:45, 11:00-12:15 - session 1 - Webex
* Wed 04-Jan - 09:30-10:45, 11:00-12:15 - session 2 - Webex
* Tue 10-Jan - 09:30-10:45, 11:00-12:15 - session 3 - on site
* Wed 11-Jan - 09:30-10:45 - session 4a - on site
* Tue 17-Jan - 15:15-16:30 - session 4b - Webex
* Wed 18-Jan - 09:30-10:45, 11:00-12:15 - session 5 - Webex

Practical sessions:
* Wed 11-Jan - 11:00-12:15
* Tue 17-Jan - 09:30-10:45, 11:00-12:15, 13:45-15:00

### Course material

* Some extracts from [this presentation about connected devices](https://pascalbod.github.io/iot-en-presentation/#/)
* [This presentation about RTOS](https://pascalbod.github.io/rtos-en-presentation/) 
* An [ESP-EYE](https://www.espressif.com/en/products/devkits/esp-eye/overview)

### Session 1 - 03-Jan - Hardware, and a little bit of software

* [Hardware progress](https://pascalbod.github.io/iot-en-presentation/connectedDevice.html#/device-2)
* [Memory, processing power and application](https://pascalbod.github.io/iot-en-presentation/connectedDevice.html#/device-3)
* [Connected device architecture](https://pascalbod.github.io/iot-en-presentation/connectedDevice.html#/device-4)
  * Computer vs microcontroller
  * Memory
  * Architecture
* [Important characteristics](https://pascalbod.github.io/iot-en-presentation/connectedDevice.html#/4/11)
* [Common microcontroller families for connected devices](https://pascalbod.github.io/iot-en-presentation/connectedDevice.html#/4/16)
* [Peripherals](https://pascalbod.github.io/iot-en-presentation/connectedDevice.html#/device-5)
* [Interfacing with peripherals](https://pascalbod.github.io/iot-en-presentation/connectedDevice.html#/device-6)
* [Floating point arithmetic](https://pascalbod.github.io/iot-en-presentation/connectedDevice.html#/device-6b)

### Session 2 - 04-Jan - Software - part 1

* [Cross development](https://pascalbod.github.io/iot-en-presentation/connectedDevice.html#/8/1)
* [Execution environments](https://pascalbod.github.io/iot-en-presentation/connectedDevice.html#/8/5)
  * OS
  * RTOS
  * [Bare metal ](https://pascalbod.github.io/iot-en-presentation/connectedDevice.html#/8/19)
    * Interruptions and background task
    * Usual architecture of a bare metal application
* [Useful design patterns](https://pascalbod.github.io/iot-en-presentation/connectedDevice.html#/8/54)
* [RTOS](https://pascalbod.github.io/rtos-en-presentation/) - up to *Tasks* section

### Session 3 - 10-Jan - Playing with the target board

* [RTOS](https://pascalbod.github.io/rtos-en-presentation/) - Concurrency control, synchronizaton, communication

**Note**: for what follows, the development environment must have been installed (see farther below).

#### Development environment

* [Eclipse IDE](https://www.eclipse.org/ide/) - open source, free, developed by the Eclipse Foundation
* [Eclipse IDF plugin](https://github.com/espressif/idf-eclipse-plugin) - open source, free, developed by Espressif
* ESP-IDF:
  * [Overview](https://www.espressif.com/en/products/sdks/esp-idf)
  * [Getting started](https://docs.espressif.com/projects/esp-idf/en/v4.4.3/esp32/get-started/index.html)
  * open source, free, developed by Espressif
* FreeRTOS:
  * [Website](https://www.freertos.org)
  * [Developer Docs](https://www.freertos.org/features.html)
* C language: [a list of resources](https://systev.com/c-a-list-of-resources/)

#### Hardware environment

* ESP32:
  * [Main webpage](https://www.espressif.com/en/products/socs/esp32)
  * [Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf)
  * [Technical Reference Manual](https://www.espressif.com/sites/default/files/documentation/esp32_technical_reference_manual_en.pdf)
  * [Programming Guide](https://docs.espressif.com/projects/esp-idf/en/v4.4.3/esp32/index.html)
* ESP-EYE:
  * [Main webpage](https://www.espressif.com/en/products/devkits/esp-eye/overview)
  * [Getting Started Guide](https://github.com/espressif/esp-who/blob/master/docs/en/get-started/ESP-EYE_Getting_Started_Guide.md)

#### Software development

##### Some sample examples

* `Hello World`
  * Eclipse workspace
  * A first ESP-IDF project
  * ESP-IDF automatically starts FreeRTOS scheduler
  * Then it starts the `app_main` task, which must be implemented by the developer
  * Build, flash, check messages
* First sample application: `01-detectionLed`
  * [Overview of ESP-EYE](https://github.com/espressif/esp-who/blob/master/docs/en/get-started/ESP-EYE_Getting_Started_Guide.md)
  * The schematic, from the [Reference Design](https://www.espressif.com/sites/default/files/documentation/ESP-EYE_V2.1_Reference_Design_0.zip)
    * ESP32 pin layout: section 2.1 of the DS
    * ESP32 GPIO: section 4.1.1 of the DS, section 4 of the TRM
    * Which state after reset: section 4.10 of the TRM
    * Pull-down resistor
    * Summary: the project `README` file
  * [ESP-IDF GPIO](https://docs.espressif.com/projects/esp-idf/en/v4.4.3/esp32/api-reference/peripherals/gpio.html)
    * A rapid overview
    * A link to some examples
    * The API
  * Import project
  * Build, flash, check messages
  * Modify
* Second sample application: `02-sideButton`
  * Using `gpio_install_isr_service` instead of `gpio_isr_register`
  * Build, flash, check messages
  * Modify for detection on rising edge and falling edge

How the LED and the button could be used in a real-life application? Pressing on the side button could start some data acquisition and an inference, the end of the inference could be signaled by the LED...

### Session 4 - 17-Jan - End of RTOS part + part 1 of Communications

* [RTOS](https://pascalbod.github.io/rtos-en-presentation/) - Time, memory allocation
* Integrating AI and RTOS: `06-skeletonApp`
* [Data interchange](https://pascalbod.github.io/iot-en-presentation/#/communications-7)
  * Stream or message
  * Transparency, endianness, serialization
  * MQTT, CoAP, other
* [Integration in the Internet](https://pascalbod.github.io/iot-en-presentation/#/communications-8)

### Session 5 - 18-Jan - Communications - part 2

* [Public land mobile networks](https://pascalbod.github.io/iot-en-presentation/#/communications-2)
* [Unlicensed LPWAN](https://pascalbod.github.io/iot-en-presentation/#/communications-3)
* [Satellite networks](https://pascalbod.github.io/iot-en-presentation/#/communications-4)
* [PMR](https://pascalbod.github.io/iot-en-presentation/#/communications-5)
* [On short distances](https://pascalbod.github.io/iot-en-presentation/#/communications-6)

## Practical sessions

### ESP32

The [ESP32](https://www.espressif.com/en/products/socs/esp32) is a microcontroller with Wi-Fi and Bluetooth connectivity. It has been created by [Espressif](https://www.espressif.com/en). It's part of the [ESP family](https://pascalbod.github.io/iot-en-presentation/connectedDevice.html#/4/38). We will look at this microcontroller in more details during the course.

[ESP-IDF](https://www.espressif.com/en/products/sdks/esp-idf) (IoT Development Framework) is Espressif's SDK (Software Development Kit) for developing applications for the ESP32.

### Overview of ESP-IDF

ESP-IDF is based on [FreeRTOS](https://www.freertos.org/) and provides a rich set of libraries.

FreeRTOS, as an RTOS (Real-Time Operating System), provides the means to architect an application: tasks, synchronization primitives, etc. The libraries, on their side, provide the means to handle hardware resources: Wi-Fi, Bluetooth, Flash memory, interfaces, etc.

An application can be developped using three different types of environments:

* [Eclipse IDE](https://www.eclipse.org/ide/) (Integrated Development Environment), thanks to a [dedicated plugin](https://github.com/espressif/idf-eclipse-plugin)
* [Visual Studio Code](https://code.visualstudio.com/), thanks to a [dedicated extension](https://marketplace.visualstudio.com/items?itemName=espressif.esp-idf-extension)
* the [command line](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/linux-macos-setup.html), with any code editor

Eclipse, Visual Studio Code and ESP-IDF can be used in Linux, macOS or Windows.

In our practical sessions, we will use Eclipse with the dedicated plugin.

Programming language will be C.

### Installation of the development environment

Install the following applications in this order (see below for some additional information):
1. *Eclipse for C/C++ Developers*, version 2022‑09 R
2. *Eclipse IDF plugin*, version 2.7.0
3. *ESP-IDF*, version 4.4.3

**Beware**: stick to the Eclipse version and to the ESP-IDF version.

Eclipse for C/C++ Developers can be installed thanks to the *Eclipse Installer*, which can be downloaded from [this page](https://www.eclipse.org/downloads/packages/release/2022-09/r). Select the suitable version for your operating system and computer (Linux Intel or Arm, macOS Intel or Arm, Windows).

The Eclipse IDF plugin can be installed according to the installation instructions from [this page](https://github.com/espressif/idf-eclipse-plugin). Among the prerequisites listed by the page, only two are really mandatory, in our case:
* Python 3.6 or above
* Git

Java has been installed by the Eclipse Installer, Eclipse has been installed by you, and ESP-IDF will be installed by the Eclipse plugin.

Once the Eclipse plugin is installed, use it to install ESP-IDF and Tools, as described in the same page.

**Note**: you can follow the instructions from [this page](https://github.com/PascalBod/lm-esp32-eclipse) to create a virtual machine with the above applications. Creating a virtual machine allows you not to modify the configuration of your computer (excepted for *VirtualBox* installation).

### A first sample application

Follow [these instructions](https://github.com/PascalBod/lm-esp32-eclipse#sample-application) to create a first sample application, based on the *hello_world* template.

Compile the project, flash it on the ESP32 board, and display the output of the application.

### Let's dive in

#### Development environment

* [Eclipse IDE](https://www.eclipse.org/ide/) - open source, free, developed by the Eclipse Foundation
* [Eclipse IDF plugin](https://github.com/espressif/idf-eclipse-plugin) - open source, free, developed by Espressif
* ESP-IDF:
  * [Overview](https://www.espressif.com/en/products/sdks/esp-idf)
  * [Getting started](https://docs.espressif.com/projects/esp-idf/en/v4.4.3/esp32/get-started/index.html)
  * open source, free, developed by Espressif
* FreeRTOS:
  * [Website](https://www.freertos.org)
  * [Developer Docs](https://www.freertos.org/features.html)
* C language: [a list of resources](https://systev.com/c-a-list-of-resources/)

#### Hardware environment

* ESP32:
  * [Main webpage](https://www.espressif.com/en/products/socs/esp32)
  * [Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf)
  * [Technical Reference Manual](https://www.espressif.com/sites/default/files/documentation/esp32_technical_reference_manual_en.pdf)
  * [Programming Guide](https://docs.espressif.com/projects/esp-idf/en/v4.4.3/esp32/index.html)
* ESP-EYE:
  * [Main webpage](https://www.espressif.com/en/products/devkits/esp-eye/overview)
  * [Getting Started Guide](https://github.com/espressif/esp-who/blob/master/docs/en/get-started/ESP-EYE_Getting_Started_Guide.md)

#### Some sample examples

* `Hello World`
  * Eclipse workspace
  * A first ESP-IDF project
  * ESP-IDF automatically starts FreeRTOS scheduler
  * Then it starts the `app_main` task, which must be implemented by the developer
  * Build, flash, check messages
* `01-detectionLed`
  * [Overview of ESP-EYE](https://github.com/espressif/esp-who/blob/master/docs/en/get-started/ESP-EYE_Getting_Started_Guide.md)
  * The schematic, from the [Reference Design](https://www.espressif.com/sites/default/files/documentation/ESP-EYE_V2.1_Reference_Design_0.zip)
    * ESP32 pin layout: section 2.1 of the DS
    * ESP32 GPIO: section 4.1.1 of the DS, section 4 of the TRM
    * Which state after reset: section 4.10 of the TRM
    * Pull-down resistor
    * Summary: the project `README` file
  * [ESP-IDF GPIO](https://docs.espressif.com/projects/esp-idf/en/v4.4.3/esp32/api-reference/peripherals/gpio.html)
    * A rapid overview
    * A link to some examples
    * The API
  * Import project
  * Build, flash, check messages
  * Modify
* `02-sideButton`
  * Using `gpio_install_isr_service` instead of `gpio_isr_register`
  * Build, flash, check messages
  * Modify for detection on rising edge and falling edge

How the LED and the button could be used in a real-life application? Pressing on the side button could start some data acquisition and an inference, the end of the inference could be signaled by the LED...

#### Exercise 1

Create an application according to the following specifications:
* Right after reset, the LED is off
* Pressing on the button and keeping it pressed turns the LED on
* Releasing the button turns the LED off

The project must be named `exercise1`.

#### Going on with sample applications

* `03-tasks`
  * A [task is a FreeRTOS object](https://freertos.org/taskandcr.html)
  * A task has its own stack

Note: [FreeRTOS has been slightly adapted to ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/v4.4.3/esp32/api-reference/system/freertos.html).

#### Exercise 2

Question 1: each task displays a trace message. How does it happen that the contents of the messages are not mixed, from time to time?

Question 2: remove the call to `vTaskDelay` function in one task. Build, run, check trace messages. What happens? How do you explain this?

Question 3: reduce task stack size to 100. Build, run, check trace messages. What happens?

Question 4: read the [description of the `uxTaskGetStackHighWaterMark` function](https://freertos.org/uxTaskGetStackHighWaterMark.html). Then, use the function to find a minimal value for task1 stack depth, and test it.

#### Going on with sample applications

* `04-binSemaphore`
  * How to use a (binary) semaphore to synchronize a task and an ISR

#### Exercise 3

Modify `exercise1` in order to use synchronization on a binary semaphore instead of polling of a flag.

#### Going on with sample applications

* `05-messageQueue`
  * How to exchange data between asynchronous code, and to synchronize: the main task waits for messages sent by two other tasks. Every message contains a counter
  * Additionally: how to serialize events

#### Exercise 4

Create a copy of `05-messageQueue` and modify it so that you can let the two tasks use the same function. In other words, instead of having two very similar `task1` and `task2` functions, you'll have only one function. But the application will still start two tasks, one sending `MSG_TASK1` messages and the other one sending `MSG_TASK2` messages.

#### Going on with sample applications

* `06-skeletonApp`
  * When the user clicks on the side button, the camera starts returning a stream of pictures
  * Every picture is sent to a function provided by the user. This function may perform some processing on the picture
  * When the user function is done, it can call a function provided by the skeleton, which will set the detection LED on for a short period of time

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

The user function may be written in C++.

Check the `README` file of the project for more information.

**Important**: the project reuses components provided by [ESP-WHO](https://github.com/espressif/esp-who). If ESP-WHO is not installed yet, download it:

```shell
$ git clone --recursive https://github.com/espressif/esp-who.git
```

Then, configure `06-skeletonApp` by modifying the top `CMakeLists.txt` file in order to adapt the definition of `EXTRA_COMPONENT_DIRS` to your ESP-WHO installation:

```
# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

set(EXTRA_COMPONENT_DIRS /home/developer/DevTools/esp-who/components)  # <== adapt directory path
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})
```

Finally:
* Select the type of the board (ESP-EYE) with **Component Config > ESP-WHO Configuration**
* Enable SPI RAM (PSRAM) with **Component Config > ESP32-specific > Support for external, SPI-connected RAM**