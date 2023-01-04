# Controlling the detection LED

The ESP-EYE schematic can be found from [this page](https://www.espressif.com/en/support/documents/technical-documents): this is the archive file named *ESP-EYE_V2.1 Reference Design*. The archive file contains the schematic.

This schematic shows that the detection LED, **D5**, is controlled by the **IO21** signal coming from the ESP32. But between IO21 and D5, there is a (dual) MOSFET, **U9**. In order to emit the right level of light, the LED requires more current than the ESP32 can accept. The MOSFET is used as an intermediate switch: it can accept the current required by the LED when it is set on (closed), while it requires a low current from IO21 to be switched on. The MOSFET is activated by **G1**.

IO21 controls the input of the MOSFET with the following resistors:

```
              R25
IO21---+---/\/\/\/\/\-----G1
       |
       |      R26
       +---/\/\/\/\/\-----GND
```

**R26** is named a *pull-down resistor*. It ensures that G1 is at 0 V when IO21 is not set (is *floating*). So, if the application running in the ESP32 does not set IO21 (neither to 0 V nor to 3.3 V), the input of the MOSFET, G1, will be set to 0 V. Without this, the LED could blink with a random pattern, depending on electric charges collected by G1, by induction for instance.

All ESP32 GPIO peripherals which allow input and output operations have integrated pull-down and pull-up resistors. IO21 is part of these GPIOs, so it integrates a pull-up resistor and a pull-down resistor. If the internal pull-up resistor were enabled, it could almost annihilate the effect of R26. So it's important to ensure that this internal pull-up resistor is not active.

Let's check what the state of this resistor is right after a reset. This information is provided by the *ESP32 Technical Reference Manual*, available from the same page as above, in section 4.10. The table provided by this section shows that right after reset, IO21 is configured as an input, without pull-down or pull-up resistor. So far, so good.

But we also have to ensure that when the application wants to control the LED, it does not activate the internal resistors. This can easily be ensured, by calling a dedicated configuration function (check the source code).