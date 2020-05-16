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

#ifndef DP_CONTROLLER_H
#define DP_CONTROLLER_H

#include "DPSensor.hpp"

/**
   Ventilation controller that only lets dry air in.

   The controller compares measures from an inside and outside dewpoint sensor.
   It switches ventilation on if the outside air is drier, i.e., if it has a lower dewpoint.
*/
class DPController {
  public:
    // enums
    enum class VentingState { VENTING_ON, VENTING_OFF };

  private:
    // private state
    unsigned long previous_timestamp_ms;
    unsigned long time_venting_on_sec = 0;
    unsigned long time_venting_off_sec = 0;
    unsigned long relay_count = 0;
    unsigned long updating_in_ms = 0;
    VentingState state;

    // helper methods
    bool should_be_venting();
    bool should_not_be_venting();
    void start_venting();
    void stop_venting();

  public:
    // settings
    unsigned long interval_sec = 30;
    float venting_threshold_celsius = 1.0f;
    float min_venting_temp_outside_celsius = 15;
    int relay_pin;

    // constructor
    DPController(DPSensor &inside, DPSensor &outside, int relay_pin);

    // public state
    DPSensor &inside, &outside;

    // main methdos
    void setup();
    void loop();
    void print();

    // statistics
    unsigned long get_venting_time_sec();
    unsigned long get_off_time_sec();
    unsigned long get_relay_count();
    unsigned long get_updating_in_sec();
    VentingState get_state();
};

#endif
