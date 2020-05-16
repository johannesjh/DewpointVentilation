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

#ifndef DP_DISPLAY_H
#define DP_DISPLAY_H

#include <TimeLib.h>
#include <Wire.h>
#include <SSD1306Ascii.h>
#include <SSD1306AsciiWire.h>
#include "DPController.hpp"

#define DP_DISPLAY_I2C_ADDRESS 0x3C

class DPDisplay {
  private:
    // members
    SSD1306AsciiWire display;
    DPController &controller;
    unsigned long previous_timestamp_ms;
    char line[21]; // buffer for sprintf output

    // helper functions
    void formatDuration(char* str, time_t t);
    void padLine();

  public:
    // settings
    int interval_ms = 500;

    // constructor and main methods
    DPDisplay(DPController &controller);
    void setup();
    void loop();
};

#endif
