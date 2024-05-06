# Actuator-Encoders

For the 2024 season, we are using two accelerometers (MPU-6050), this will communicate with an Arduino UNO over the $\text{I}^2\text{C}$ bus.

Example code was taken from [this website](http://www.mschoeffler.de)

# How to use

This code should be uploaded to a microcontroller that is able to use/access the $\text{I}^2\text{C}$ bus, not all boards will be able to have the same performance. This will explain how to use with an Arduino UNO, you should be able to modify specific instructions to work with whatever microcontroller that you want to use

## Hardware

What you will need:
- Arduino UNO
- USB type B cable
- 2 x MPU-6050
- Jumper wires
- (Bread Board)

With these parts, you will be able to create a table test for the program and you can adapt to whatever your use case is

## Set-Up

Because $\text{I}^2\text{C}$ is a Bus, the SDA pins are all able to be connected together on the A4 pin of the Arduino UNO, SCL will be connected to pin A5 and the other SCL pins. Because we are using two of the same devies, we need to change the address; this can be done by tying the pin AD0 high, or bridging the AD0 pads (if present). Last thing to do is provide 3.3V to VCC and ground to GND.

## Usage

If you followed everything correctly, this should result in the angles being output from the serial bus. You can modify which axis is being output from changing the funciton being called for inside of the if statement of the loop function.

# Explainations

Similar code was experimented with the Raspberry Pi Pico, but it appeared to have not as great performance as the Arduino UNO

If you want to change the axis from one to the other, change the function being called. In this example, you would change angleXY / angleZY to whatever you want
```cpp
void loop() {
    for (int i = 0; i < 2; i++) {
        ...

        if (i == 0)
            test = angleXY(accelerometer_x, accelerometer_y);
        else if (i == 1)
            test = angleZY(accelerometer_z, accelerometer_y);

        ...
    }
}
```