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

#ifndef DP_SENSOR_H
#define DP_SENSOR_H

#include <Wire.h>
#include <SparkFunBME280.h>

/**
   Controls a BME280 sensor to take repeated measures of temperature, humidity and dewpoint.
*/
class DPSensor
{
  private:
    int i2c_addr;
    BME280 sensor;
    unsigned long previous_timestamp_ms;

  public:
    // settings
    int interval_ms = 1000;

    // constructor and main methods
    DPSensor(int i2c_addr = 0x76, int interval_ms = 1000);
    void setup();
    void loop();
    void print();

    // measures
    float temperature_celsius;
    float humidity_percent;
    float dewpoint_celsius;
};

#endif
