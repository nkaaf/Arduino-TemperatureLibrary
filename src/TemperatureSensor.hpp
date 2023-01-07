/*!
 * @file TemperatureSensor.hpp
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

#ifndef TEMPERATURE_LIBRARY_TEMPERATURESENSOR_HPP
#define TEMPERATURE_LIBRARY_TEMPERATURESENSOR_HPP

#include "Temperature.hpp"

/*!
 * @brief   Abstract class from which all temperature sensors can be derived.
 */
class TemperatureSensor {
protected:
  int *stateStorage = nullptr; /// Storage for register states.

public:
  /*!
   * @brief Initialise the temperature sensor.
   */
  virtual void init() = 0;

  /*!
   * @brief Get the default unit of the sensor.
   *
   * @return Default unit of the temperature sensor.
   */
  virtual Temperature::Unit getDefaultUnit() = 0;

  /*!
   * @brief Get the temperature, that the sensor is sensing.
   *
   * @return Temperature value
   */
  virtual float getTemperature() = 0;

  /*!
   * @brief Save the state of the MCU registers. This is important, if the MCU
   * is not only reading from the sensor, but also doing other tasks. If the
   * saving of the state is required, see the examples of the correct sensor.
   */
  virtual void saveState() = 0;

  /*!
   * @brief  Restoring the state that is saved before. If no state is saved,
   * nothing happens.
   */
  virtual void restoreState() = 0;
};

#endif // TEMPERATURE_LIBRARY_TEMPERATURESENSOR_HPP
