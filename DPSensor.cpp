/*
DewpointVentilation - A ventilation controller powered by Arduino
Copyright (c) 2020 johannesjh.  All rights reserved.

This file is part of DewpointVentilation.

DewpointVentilation is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

DewpointVentilation is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with DewpointVentilation.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "DPSensor.hpp"

DPSensor::DPSensor(int i2c_addr, int interval_ms) :
  i2c_addr(i2c_addr), interval_ms(interval_ms)
{}

void DPSensor::setup() {
  previous_timestamp_ms = 0;
  sensor.settings.commInterface = I2C_MODE;
  sensor.settings.I2CAddress = i2c_addr;
  sensor.settings.runMode = 3;
  sensor.settings.tStandby = 0;
  sensor.settings.filter = 4;
  sensor.settings.tempOverSample = 4;
  sensor.settings.pressOverSample = 0; // disabled
  sensor.settings.humidOverSample = 4;
  sensor.begin();
}

void DPSensor::loop() {
  if ((unsigned long)(millis() - previous_timestamp_ms) < interval_ms) return;
  previous_timestamp_ms = millis();

  temperature_celsius = sensor.readTempC();
  humidity_percent = sensor.readFloatHumidity();
  dewpoint_celsius = (float) sensor.dewPointC();
}

void DPSensor::print() {
  Serial.print(F("Sensor at address 0x"));
  Serial.print(i2c_addr, HEX);
  Serial.print(F(" Dewpoint "));
  Serial.print(dewpoint_celsius);
  Serial.println(F("C"));
}
