# Dewpoint Ventilation

A ventilation controller powered by Arduino that compares inside and outside dewpoints in order to control a relay and fan.


## Project Status

Prototypical implementation. Not actively maintained.

I sought to refactor and improve the [ArDewpoint](https://github.com/mvniemi/arDewpoint) code using an object-oriented programming style. This worked out nice in theory. When put in practice however, i.e., when running on a physical arduino device, the program crashes every other day, possibly due to memory leaks, but I am not sure. I currently don't have time to further debug, actively maintain or improve this project.


## Working Principle

Outside air with a lower dewpoint won't condense if let inside. The ventilation controller works based on this principle. The controller compares the inside and outside dewpoints in order to turn ventilation on or off using a relay.


## Credits

This project was inspired by the [ArDewpoint](https://github.com/mvniemi/arDewpoint) project by Michael Niemi, also see his excellent [ArDewpoint tutorial and project description](http://www.instructables.com/id/ArDewpoint-Dew-Point-Based-Ventilation-Controller/) and the according [ArDewpoint sourcecode](https://github.com/mvniemi/arDewpoin) on github. All code in this project has been written freshly from scratch using an object-oriented programming principles.

One further source of inspiration is this valuable tutorial about object-oriented programming for Arduino https://paulmurraycbr.github.io/ArduinoTheOOWay.html


## Dependencies

This project makes use of the following dependencies that can be installed as libraries in the Arduino IDE:

- [Arduino Wire](https://github.com/arduino/ArduinoCore-avr/tree/master/libraries/Wire) library under LGPL

- [SparkFunBME280](https://github.com/sparkfun/SparkFun_BME280_Arduino_Library) under MIT License

- [SSD1306Ascii](https://github.com/greiman/SSD1306Ascii) under GPL

- [TimeLib](https://github.com/PaulStoffregen/Time) under LGPL


## License

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
