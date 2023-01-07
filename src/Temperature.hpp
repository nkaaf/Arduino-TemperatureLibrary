//
// Created by niklas on 27.12.22.
//

#ifndef TEMPERATURE_LIBRARY_TEMPERATURE_HPP
#define TEMPERATURE_LIBRARY_TEMPERATURE_HPP

#include <WString.h>

/*!
 * @brief   Class representing a temperature, but this also includes some static
 * methods for handling temperatures (for example convert temperatures into
 * other units).
 */
class Temperature {
public:
  enum Unit {
    CELSIUS,
    FAHRENHEIT,
    KELVIN,
    RANKINE,
    DELISLE,
    REAUMUR,
    NEWTON,
    ROMER
  }; /// Existing units

  /*!
   * @brief Constructor of a temperature before it is set.
   *
   * @param unit Unit of the temperature
   */
  Temperature(Unit unit) : value(), unit(unit){};

  /*!
   * @brief Constructor of a temperature including the actual temperature value
   * and the unit.
   *
   * @param value   Actual temperature value
   * @param unit    Unit of the temperature
   */
  Temperature(float value, Unit unit) : value(value), unit(unit){};

  /*!
   * @brief Get the temperature value.
   *
   * @return The temperature in the configured unit (getUnit())
   */
  float getTemperature() { return this->value; }

  /*!
   * @brief Get the temperature as a string including the unit.
   *
   * @return The temperature as a string with the unit.
   */
  String getTemperatureString();

  /*!
   * @brief Get the temperature as a string including the same or an other unit.
   *
   * @param unit    The unit that the output string should have.
   * @return The temperature as a string with the unit.
   */
  String getTemperatureString(Unit unit);

  /*!
   * @brief Get a string representation of the temperature including the unit.
   *
   * @param value   Value of the desired temperature string.
   * @param unit    Unit of the desired temperature string.
   * @return    The temperature including the unit as a string.
   */
  static String getTemperatureString(float value, Unit unit);

  /*!
   * @brief Set the temperature value in the current unit.
   *
   * @param value   Temperature
   */
  void setTemperature(float value) { this->value = value; };

  /*!
   * @brief Set the temperature value in the current or an other unit.
   *
   * @param value   Temperature
   * @param unit    Unit of the temperature value
   */
  void setTemperature(float value, Unit unit);

  /*!
   * @brief Get the unit of the temperature.
   *
   * @return Unit of temperature
   */
  Unit getUnit() { return unit; };

  /*!
   * @brief Get a string representation of a unit.
   *
   * @param unit    Unit
   * @return    A string representation of a unit.
   */
  static String getUnitString(Unit unit);

  /*!
   * @brief Set the unit and convert the current saved temperature.
   *
   * @param unit    New unit that should be set.
   */
  void setUnit(Unit unit);

  /*!
   * @brief Convert a temperature from an unit into an other unit.
   *
   * @param value       Temperature value
   * @param unitFrom    Unit from that the value should be converted
   * @param unitTo      Unit in that the value should be converted
   * @return    Value of the converted temperature.
   */
  static float convertTo(float value, Unit unitFrom, Unit unitTo);

  /*!
   * @brief Convert the current temperature from the current unit into an other
   * unit.
   *
   * @param unit    Unit in that the temperature should be converted.
   * @return    Value of the converted temperature.
   */
  float convertTo(Unit unit);

private:
  float value; /// Temperature value
  Unit unit;   /// Temperature unit
};

#endif // TEMPERATURE_LIBRARY_TEMPERATURE_HPP
