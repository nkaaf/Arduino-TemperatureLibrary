//
// Created by niklas on 27.12.22.
//

#include "Temperature.hpp"

#include <math.h>

String Temperature::getTemperatureString() {
  // if (isinf(this->value) || isnan(this->value)) {
  //   return "Fehler";
  // }
  return getTemperatureString(this->value, this->unit);
}

String Temperature::getTemperatureString(Temperature::Unit unit) {
  if (this->unit == unit) {
    return this->getTemperatureString();
  }

  return getTemperatureString(this->convertTo(unit), unit);
}

String Temperature::getTemperatureString(float value, Unit unit) {
  String string = String(value);
  string += F(" ");
  string += getUnitString(unit);
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
  return unit == CELSIUS      ? F("°C")
         : unit == FAHRENHEIT ? F("°F")
         : unit == KELVIN     ? F("K")
         : unit == RANKINE    ? F("°R")
         : unit == DELISLE    ? F("°D")
         : unit == REAUMUR    ? F("°R")
         : unit == NEWTON     ? F("°N")
         : unit == ROMER      ? F("°Rø")
                              : F("");
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
