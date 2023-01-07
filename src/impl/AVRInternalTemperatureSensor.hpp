/*!
 * @file impl/AVRInternalTemperatureSensor.hpp
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

#ifndef ARDUINO_TEMPERATURE_AVRINTERNALTEMPERATURESENSOR_HPP
#define ARDUINO_TEMPERATURE_AVRINTERNALTEMPERATURESENSOR_HPP

#include "TemperatureSensor.hpp"

#include <Linear2DRegression.hpp>

/*!
 * @brief   Class representing the Internal Temperature Sensor of
 * microprocessors from Microchip (formerly: Atmel) with AVR Platform.
 */
class AVRInternalTemperatureSensor : public TemperatureSensor {
private:
  static Linear2DRegression
      *linearRegression; /// Regression needed for calculating the temperature
                         /// of the voltage

  /*!
   * @brief Destructor, freeing allocated memory
   */
  ~AVRInternalTemperatureSensor();

  /*!
   * @brief Init the regression with points from the datasheet
   */
  static void initRegression();

public:
  /*!
   * @copydoc TemperatureSensor::init()
   */
  void init() override;

  /*!
   * @copydoc TemperatureSensor::getDefaultUnit()
   */
  Temperature::Unit getDefaultUnit() override { return Temperature::CELSIUS; }

  /*!
   * @copydoc TemperatureSensor::getTemperature()
   */
  float getTemperature() override;

  /*!
   * @copydoc TemperatureSensor::saveState()
   */
  void saveState() override;

  /*!
   * @copydoc TemperatureSensor::restoreState()
   */
  void restoreState() override;
};

#endif // ARDUINO_TEMPERATURE_AVRINTERNALTEMPERATURESENSOR_HPP
