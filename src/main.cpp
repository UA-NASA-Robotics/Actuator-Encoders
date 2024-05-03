// (c) Michael Schoeffler 2017, http://www.mschoeffler.de

#include <Wire.h> // This library allows you to communicate with I2C devices.
#include "math.h"
#include <Arduino.h>
#include "niceFunctions.h"

const uint8_t MPU_ADDR[] = {0x68, 0x69}; // I2C addresses of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.

// To access the addresses, you can use the index operator, for example:
// MPU_ADDR[0] will give you the address 0x68
// MPU_ADDR[1] will give you the address 0x69

int16_t accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer raw data
int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data
int16_t temperature; // variables for temperature data

char tmp_str[7]; // temporary variable used in convert function

char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
	sprintf(tmp_str, "%6d", i);
	return tmp_str;
}

void setup() {
	Serial.begin(9600);
	Wire.begin();

	for (int i = 0; i < 2; i++) {
		Wire.beginTransmission(MPU_ADDR[i]); // Begins a transmission to the I2C slave (GY-521 board)
		Wire.write(0x6B); // PWR_MGMT_1 register
		Wire.write(0); // set to zero (wakes up the MPU-6050)
		Wire.endTransmission(true);
	}
}

void loop() {
	for (int i = 0; i < 2; i++) {
		Wire.beginTransmission(MPU_ADDR[i]);
		Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
		Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
		Wire.requestFrom(MPU_ADDR[i], 7*2, true); // request a total of 7*2=14 registers
		
		// "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
		accelerometer_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
		accelerometer_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
		accelerometer_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)

		double test = convertToTheta(accelerometer_x, accelerometer_y, accelerometer_z);
		
		// print out data
		// Serial.print("aX = "); Serial.print(convert_int16_to_str(accelerometer_x));
		// Serial.print(" | aY = "); Serial.print(convert_int16_to_str(accelerometer_y));
		// Serial.print(" | aZ = "); Serial.print(convert_int16_to_str(accelerometer_z));
		if (i == 1) {
			Serial.println();
		} else {
			Serial.print('\t');
		}
	}
}
