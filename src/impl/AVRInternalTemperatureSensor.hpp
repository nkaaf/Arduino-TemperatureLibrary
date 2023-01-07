//
// Created by niklas on 27.12.22.
//

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
