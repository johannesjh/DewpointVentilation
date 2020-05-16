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

#include "DPController.hpp"

DPController::DPController(DPSensor &inside, DPSensor &outside, int relay_pin) :
  inside(inside), outside(outside), relay_pin(relay_pin)
{}

void DPController::setup() {
  previous_timestamp_ms = millis();
  pinMode(relay_pin, OUTPUT);
  stop_venting();
}

void DPController::loop() {
  updating_in_ms = ((unsigned long)(interval_sec)) * 1000 - (unsigned long)(millis() - previous_timestamp_ms);
  if ((unsigned long)(millis() - previous_timestamp_ms) < interval_sec * 1000) return;
  previous_timestamp_ms = millis();

  if (state == VentingState::VENTING_ON) {
    time_venting_on_sec += interval_sec;
    if (should_not_be_venting()) stop_venting();
  }
  else if (state == VentingState::VENTING_OFF) {
    time_venting_off_sec += interval_sec;
    if (should_be_venting()) start_venting();
  }
}

void DPController::print() {
  Serial.print(F("Inside "));
  inside.print();
  Serial.print(F("Outside"));
  outside.print();
}

bool DPController::should_be_venting() {
  if (outside.temperature_celsius < min_venting_temp_outside_celsius) return false;
  return outside.dewpoint_celsius + venting_threshold_celsius < inside.dewpoint_celsius;
}

bool DPController::should_not_be_venting() {
  if (outside.temperature_celsius < min_venting_temp_outside_celsius) return true;
  return outside.dewpoint_celsius > inside.dewpoint_celsius;
}

void DPController::start_venting() {
  state = VentingState::VENTING_ON;
  digitalWrite(relay_pin, LOW);
  relay_count++;
}

void DPController::stop_venting() {
  state = VentingState::VENTING_OFF;
  digitalWrite(relay_pin, HIGH);
  relay_count++;
}

unsigned long DPController::get_venting_time_sec() {
  unsigned long t = time_venting_on_sec;
  if (state == VentingState::VENTING_ON) t += (millis() - previous_timestamp_ms) / 1000;
  return t;
}

unsigned long DPController::get_off_time_sec() {
  unsigned long t = time_venting_off_sec;
  if (state == VentingState::VENTING_OFF) t += (millis() - previous_timestamp_ms) / 1000;
  return t;
}

unsigned long DPController::get_relay_count() {
  return relay_count;
}

unsigned long DPController::get_updating_in_sec() {
  return updating_in_ms / 1000;
}

DPController::VentingState DPController::get_state() {
  return state;
}
