/*!
 * @file Temperature.cpp
 *
 * The library can be used to compute temperatures into different units, to
 * retrieve temperatures from different sensors and to write own implementation
 * of temperature sensors.
 *
 * Copyright (C) 2023  Niklas Kaaf
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
 * USA
 */

#include "Temperature.hpp"

#if defined(CHAR_PTR_STRING)
#include "avr/pgmspace.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#endif

String Temperature::getTemperatureString() {
  return getTemperatureString(this->value, this->unit);
}

String Temperature::getTemperatureString(Temperature::Unit unit) {
  if (this->unit == unit) {
    return this->getTemperatureString();
  }

  return getTemperatureString(this->convertTo(unit), unit);
}

String Temperature::getTemperatureString(float value, Unit unit) {
#if defined(CHAR_PTR_STRING)
  int len = snprintf(nullptr, 0, "%f", value);
  String unitString = getUnitString(unit);

  auto string = (String)malloc(
      sizeof(unsigned char) * strlen((char *)unitString) + 1 + len + 1);
  sprintf((char *)string, "%f %s", value, (char *)&unitString);
#else
  String string = String(value);
  string += F(" ");
  string += getUnitString(unit);
#endif
  return string;
}

void Temperature::setTemperature(float value, Temperature::Unit unit) {
  if (this->unit == unit) {
    this->setTemperature(value);
  } else {
    this->setTemperature(convertTo(value, this->unit, unit));
  }
}

void Temperature::setUnit(Temperature::Unit unit) {
  this->setTemperature(this->convertTo(unit));
  this->unit = unit;
}

String Temperature::getUnitString(Unit unit) {
#if defined(ARDUINO)
  return unit == CELSIUS      ? F("°C")
         : unit == FAHRENHEIT ? F("°F")
         : unit == KELVIN     ? F("K")
         : unit == RANKINE    ? F("°R")
         : unit == DELISLE    ? F("°D")
         : unit == REAUMUR    ? F("°R")
         : unit == NEWTON     ? F("°N")
         : unit == ROMER      ? F("°Rø")
                              : F("");
#else
  return (String)(unit == CELSIUS      ? PSTR("°C")
                  : unit == FAHRENHEIT ? PSTR("°F")
                  : unit == KELVIN     ? PSTR("K")
                  : unit == RANKINE    ? PSTR("°R")
                  : unit == DELISLE    ? PSTR("°D")
                  : unit == REAUMUR    ? PSTR("°R")
                  : unit == NEWTON     ? PSTR("°N")
                  : unit == ROMER      ? PSTR("°Rø")
                                       : PSTR(""));
#endif
}

float Temperature::convertTo(Unit unit) {
  return convertTo(this->value, this->unit, unit);
}

/** Conversions from: http://www.alcula.com/conversion/temperature */
float Temperature::convertTo(float value, Unit unitFrom, Unit unitTo) {
  if (unitFrom == CELSIUS) {
    if (unitTo == FAHRENHEIT) {
      return value * 9 / 5 + 32;
    } else if (unitTo == KELVIN) {
      return value + (float)273.15;
    } else if (unitTo == RANKINE) {
      return (value + (float)273.15) * 9 / 5;
    } else if (unitTo == DELISLE) {
      return (100 - value) * 3 / 2;
    } else if (unitTo == REAUMUR) {
      return value * 4 / 5;
    } else if (unitTo == NEWTON) {
      return value * 33 / 100;
    } else if (unitTo == ROMER) {
      return value * 21 / 40 + (float)7.5;
    }
  } else if (unitFrom == FAHRENHEIT) {
    if (unitTo == CELSIUS) {
      return (value - 32) * 5 / 9;
    } else if (unitTo == KELVIN) {
      return (value + (float)459.67) * 5 / 9;
    } else if (unitTo == RANKINE) {
      return value + (float)459.67;
    } else if (unitTo == DELISLE) {
      return (212 - value) * 5 / 6;
    } else if (unitTo == REAUMUR) {
      return (value - 32) * 4 / 9;
    } else if (unitTo == NEWTON) {
      return (value - 32) * 11 / 60;
    } else if (unitTo == ROMER) {
      return (value - 32) * 7 / 24 + (float)7.5;
    }
  } else if (unitFrom == KELVIN) {
    if (unitTo == CELSIUS) {
      return value - (float)273.15;
    } else if (unitTo == FAHRENHEIT) {
      return (value * 9 / 5) - (float)459.67;
    } else if (unitTo == RANKINE) {
      return value * 9 / 5;
    } else if (unitTo == DELISLE) {
      return ((float)373.15 - value) * 3 / 2;
    } else if (unitTo == REAUMUR) {
      return (value - (float)273.15) * 4 / 5;
    } else if (unitTo == NEWTON) {
      return (value - (float)273.15) * 33 / 100;
    } else if (unitTo == ROMER) {
      return (value - (float)273.15) * 21 / 40 + (float)7.5;
    }
  } else if (unitFrom == RANKINE) {
    if (unitTo == CELSIUS) {
      return (value - (float)491.67) * 5 / 9;
    } else if (unitTo == FAHRENHEIT) {
      return value - (float)459.67;
    } else if (unitTo == KELVIN) {
      return value * 5 / 9;
    } else if (unitTo == DELISLE) {
      return ((float)671.67 - value) * 5 / 6;
    } else if (unitTo == REAUMUR) {
      return (value - (float)491.67) * 4 / 9;
    } else if (unitTo == NEWTON) {
      return (value - (float)491.67) * 11 / 60;
    } else if (unitTo == ROMER) {
      return (value - (float)491.67) * 7 / 24 + (float)7.5;
    }
  } else if (unitFrom == DELISLE) {
    if (unitTo == CELSIUS) {
      return 100 - value * 2 / 3;
    } else if (unitTo == FAHRENHEIT) {
      return 212 - value * 6 / 5;
    } else if (unitTo == KELVIN) {
      return (float)373.15 - (value * 2 / 3);
    } else if (unitTo == RANKINE) {
      return (float)671.76 - value * 6 / 5;
    } else if (unitTo == REAUMUR) {
      return 80 - value * 8 / 15;
    } else if (unitTo == NEWTON) {
      return 33 - value * 11 / 50;
    } else if (unitTo == ROMER) {
      return 60 - value * 7 / 20;
    }
  } else if (unitFrom == REAUMUR) {
    if (unitTo == CELSIUS) {
      return value * 5 / 4;
    } else if (unitTo == FAHRENHEIT) {
      return value * 9 / 4 + 32;
    } else if (unitTo == KELVIN) {
      return value * 5 / 4 + (float)273.15;
    } else if (unitTo == RANKINE) {
      return value * 9 / 4 + (float)491.67;
    } else if (unitTo == DELISLE) {
      return (80 - value) * 15 / 4;
    } else if (unitTo == NEWTON) {
      return value * 33 / 80;
    } else if (unitTo == ROMER) {
      return value * 21 / 32 + (float)7.5;
    }
  } else if (unitFrom == NEWTON) {
    if (unitTo == CELSIUS) {
      return value * 100 / 33;
    } else if (unitTo == FAHRENHEIT) {
      return value * 60 / 11 + 32;
    } else if (unitTo == KELVIN) {
      return value * 100 / 33 + (float)273.15;
    } else if (unitTo == RANKINE) {
      return value * 60 / 11 + (float)491.67;
    } else if (unitTo == DELISLE) {
      return (33 - value) * 50 / 11;
    } else if (unitTo == REAUMUR) {
      return value * 80 / 33;
    } else if (unitTo == ROMER) {
      return value * 35 / 22 + (float)7.5;
    }
  } else if (unitFrom == ROMER) {
    if (unitTo == CELSIUS) {
      return (value - (float)7.5) * 40 / 21;
    } else if (unitTo == FAHRENHEIT) {
      return (value - (float)7.5) * 24 / 7 + 32;
    } else if (unitTo == KELVIN) {
      return (value - (float)7.5) * 40 / 21 + (float)273.15;
    } else if (unitTo == RANKINE) {
      return (value - (float)7.5) * 24 / 7 + (float)491.67;
    } else if (unitTo == DELISLE) {
      return (60 - value) * 20 / 7;
    } else if (unitTo == REAUMUR) {
      return (value - (float)7.5) * 32 / 21;
    } else if (unitTo == NEWTON) {
      return (value - (float)7.5) * 22 / 35;
    }
  }
  return value;
}
