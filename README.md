# IMT Atlantique - 2023 - OS for embedded devices

## Embedded software development

### Course material

* Some extracts from [this presentation about connected devices](https://pascalbod.github.io/iot-en-presentation/#/)
* [This presentation about RTOS](https://pascalbod.github.io/rtos-en-presentation/) 
* An [ESP-EYE](https://www.espressif.com/en/products/devkits/esp-eye/overview)

### Hardware, and a little bit of software

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
* Floating point arithmetic

### Target board

#### ESP32 microcontroller

* Microcontroller characteristics
* Hardware documentation
* Software documentation
* Wi-Fi
* Bluetooth
* Interrupt matrix
* IO_MUX and GPIO matrix
* GPIO
* I2S
* Serial link
* Timer

#### ESP32-EYE board

* Characteristics
* Schematics

#### Software

* ESP-IDF
* ESP-WHO

### Software

* [Cross development](https://pascalbod.github.io/iot-en-presentation/connectedDevice.html#/7/1)
* [Execution environments](https://pascalbod.github.io/iot-en-presentation/connectedDevice.html#/7/5)
  * OS
  * RTOS
  * [Bare metal ](https://pascalbod.github.io/iot-en-presentation/connectedDevice.html#/7/19)
    * Interruptions and background task
    * Usual architecture of a bare metal application
* [Useful design patterns](https://pascalbod.github.io/iot-en-presentation/connectedDevice.html#/7/54)
* [RTOS](https://pascalbod.github.io/rtos-en-presentation/)
  * Components
  * Accessing shared resources
  * Exchanging data between tasks
  * Synchronizing
  * Time
  * Memory allocation
  * Middleware

### Communications

* [Public land mobile networks](https://pascalbod.github.io/iot-en-presentation/#/communications-2)
* [Unlicensed LPWAN](https://pascalbod.github.io/iot-en-presentation/#/communications-3)
* [Satellite networks](https://pascalbod.github.io/iot-en-presentation/#/communications-4)
* [PMR](https://pascalbod.github.io/iot-en-presentation/#/communications-5)
* [On short distances](https://pascalbod.github.io/iot-en-presentation/#/communications-6)
* [Data interchange](https://pascalbod.github.io/iot-en-presentation/#/communications-7)
  * Stream or message
  * Transparency, endianness, serialization
  * MQTT, CoAP, other
* [Integration in the Internet](https://pascalbod.github.io/iot-en-presentation/#/communications-8)

## Practical sessions

### ESP32

The [ESP32](https://www.espressif.com/en/products/socs/esp32) is a microcontroller with Wi-Fi and Bluetooth connectivity. It has been created by [Espressif](https://www.espressif.com/en). It's part of the [ESP family](https://pascalbod.github.io/iot-en-presentation/connectedDevice.html#/4/38). We will look at this microcontroller in more details during the course.

[ESP-IDF](https://www.espressif.com/en/products/sdks/esp-idf) (IoT Development Framework) is Espressif's SDK (Software Development Kit) for developing applications for the ESP32.

### Overview of ESP-IDF

ESP-IDF is based on [FreeRTOS](https://www.freertos.org/) and provides a rich set of libraries.

FreeRTOS, as an RTOS (Real-Time Operating System), provides the means to architect an application: tasks, synchronization primitives, etc. The libraries, on their side, provide the means to handle hardware resources: Wi-Fi, Bluetooth, Flash memory, interfaces, etc.

An application can be developped using three different types of environments:

* [Eclipse IDE](https://www.eclipse.org/ide/) (Integrated Development Environment), thanks to a [dedicated plugin](https://github.com/espressif/idf-eclipse-plugin/blob/master/README.md)
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