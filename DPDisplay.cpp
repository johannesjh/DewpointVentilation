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

#include "DPDisplay.hpp"

DPDisplay::DPDisplay(DPController &controller)
  : controller(controller)
{}

void DPDisplay::setup() {
  Wire.begin();
  Wire.setClock(400000L);
  display.begin(&Adafruit128x64, DP_DISPLAY_I2C_ADDRESS);
  display.setFont(System5x7);
  display.clear();
  display.setCursor(0, 15);
  display.println(F("Dewpoint Ventilation"));
  display.println(F("starting..."));
  delay(1000);
  display.clear();
}

void DPDisplay::loop() {
  if ((unsigned long)(millis() - previous_timestamp_ms) < interval_ms) return;
  previous_timestamp_ms = millis();

  //display.clear();
  display.setCursor(0, 0);

  display.print(F("In  T:"));
  display.print(controller.inside.temperature_celsius, 0);
  display.print(F(" DP:"));
  display.print(controller.inside.dewpoint_celsius, 0);
  display.print(F(" H:"));
  display.print(controller.inside.humidity_percent, 0);
  padLine();

  display.print(F("Out T:"));
  display.print(controller.outside.temperature_celsius, 0);
  display.print(F(" DP:"));
  display.print(controller.outside.dewpoint_celsius, 0);
  display.print(F(" H:"));
  display.print(controller.outside.humidity_percent, 0);
  padLine();

  if (controller.get_state() == DPController::VentingState::VENTING_ON) {
    display.print(F("Venting"));
  }
  else {
    display.print(F("Not Venting"));
  }
  padLine();

  display.print(F("- Relay Cycle: "));
  display.print(controller.get_relay_count());
  padLine();

  display.print(F("- Alive: "));
  formatDuration(line, millis() / 1000);
  display.print(line);
  padLine();

  display.print(F("- Venting: "));
  formatDuration(line, controller.get_venting_time_sec());
  display.print(line);
  padLine();

  display.print(F("- Off: "));
  formatDuration(line, controller.get_off_time_sec());
  display.print(line);
  padLine();

  display.print(F("Updating in: "));
  display.print((float)controller.get_updating_in_sec(), 0);
  display.print("s");
  padLine();
}


void DPDisplay::formatDuration(char* str, time_t t) {
  // fills the string buffer with a 16 char duration in days, hours, minutes and seconds
  tmElements_t tm;
  breakTime(t, tm);
  if (t >= SECS_PER_DAY) sprintf(str, "%ud %02uh %02um %02us", tm.Day - 1, tm.Hour, tm.Minute, tm.Second);
  else if (t >= SECS_PER_HOUR) sprintf(str, "%uh %02um %02us", hour(t), minute(t), second(t));
  else sprintf(str, "%um %02us", minute(t), second(t));
}

void DPDisplay::padLine() {
  // fills a display line with spaces to make sure lines completely overwrite each other
  display.println(F("                      "));
}
