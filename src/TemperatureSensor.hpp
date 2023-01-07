//
// Created by niklas on 27.12.22.
//

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
