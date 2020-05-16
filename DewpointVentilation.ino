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
#include "DPController.hpp"
#include "DPDisplay.hpp"

DPSensor inside = DPSensor(0x77);
DPSensor outside = DPSensor(0x76);
DPController controller = DPController(inside, outside, 8);
DPDisplay display = DPDisplay(controller);

void setup() {
  Serial.begin(9600);
  inside.setup();
  outside.setup();
  controller.setup();
  display.setup();
  delay(1000); // sensors need some time to start
}

void loop() {
  inside.loop();
  outside.loop();
  controller.loop();
  display.loop();
}
