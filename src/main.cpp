#include "Arduino.h"

#include "Temperature.hpp"

#include "impl/AVRInternalTemperatureSensor.hpp"

// Creating reference to the sensor
AVRInternalTemperatureSensor *sensor = new AVRInternalTemperatureSensor();
// Creating a temperature object which should be continuously updated
Temperature *temperature = new Temperature(sensor->getDefaultUnit());

void setup() {
  Serial.begin(9600);

  // Init the sensor
  sensor->init();
}

void loop() {
  // Save the state of the registers because after the reading, another
  // operation is done, in this example an ADC conversion via analogRead
  sensor->saveState();

  // Update the temperature
  temperature->setTemperature(sensor->getTemperature());

  // Print out the temperature
  Serial.println("Temp in °C: " + temperature->getTemperatureString());
  // Print out the temperature in Fahrenheit
  Serial.println("Temp in °F: " +
                 temperature->getTemperatureString(Temperature::FAHRENHEIT));
  Serial.println();
  delay(500);

  // Restore the state like before
  sensor->restoreState();

  Serial.println("Reading of analog value on A0: " + String(analogRead(A0)));
}