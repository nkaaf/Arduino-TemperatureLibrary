//
// Created by niklas on 27.12.22.
//

#include "AVRInternalTemperatureSensor.hpp"

Linear2DRegression *AVRInternalTemperatureSensor::linearRegression =
    new Linear2DRegression();

AVRInternalTemperatureSensor::~AVRInternalTemperatureSensor() {
  free(this->stateStorage);
}

void AVRInternalTemperatureSensor::init() {
  initRegression();

#if defined(__AVR_HAVE_PRR_PRADC)
  /// Shut down the Power Reduction ADC bit
  PRR |= (0 << PRADC);
#endif

#if defined(__AVR_ATmega48A__) || defined(__AVR_ATmega48PA__) ||               \
    defined(__AVR_ATmega88A__) || defined(__AVR_ATmega88PA__) ||               \
    defined(__AVR_ATmega168A__) || defined(__AVR_ATmega168PA__) ||             \
    defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
  /// Use internal 1.1V reference and select temperature measurement
  ADMUX = (1 << REFS1) | (1 << REFS0) | (1 << MUX3);
#elif defined(__AVR_ATtiny828__)
  /// Select temperature measurement
  ADMUXA = (1 << MUX4) | (1 << MUX3) | (1 << MUX2) | (1 << MUX1);
  /// Use internal 1.1V reference
  ADMUXB = (1 << REFS);
#endif

  /// Activate and enable ADC
  ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADPS2) | (1 << ADPS1);

  /// Wait until one conversion is finished (= initialization of the ADC)
  while ((ADCSRA & (1 << ADSC)) != 0) {
  }
}

void AVRInternalTemperatureSensor::initRegression() {
#if defined(__AVR_ATmega48A__) || defined(__AVR_ATmega48PA__) ||               \
    defined(__AVR_ATmega88A__) || defined(__AVR_ATmega88PA__) ||               \
    defined(__AVR_ATmega168A__) || defined(__AVR_ATmega168PA__) ||             \
    defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
  /// Typical values according to datasheet
  linearRegression->addPoint(242, -45);
  linearRegression->addPoint(314, 25);
  linearRegression->addPoint(380, 85);
#elif defined(__AVR_ATtiny828__)
  /// Typical values according to datasheet
  linearRegression->addPoint(235, -40);
  linearRegression->addPoint(300, 25);
  linearRegression->addPoint(360, 85);
#endif
}

float AVRInternalTemperatureSensor::getTemperature() {
  /// Activate ADC
  ADCSRA |= (1 << ADSC);

  /// Wait until conversion is finished
  while ((ADCSRA & (1 << ADSC)) != 0) {
  }

  return (float)linearRegression->calculate(ADC);
}

void AVRInternalTemperatureSensor::saveState() {
#if defined(__AVR_ATmega48A__) || defined(__AVR_ATmega48PA__) ||               \
    defined(__AVR_ATmega88A__) || defined(__AVR_ATmega88PA__) ||               \
    defined(__AVR_ATmega168A__) || defined(__AVR_ATmega168PA__) ||             \
    defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
  this->stateStorage =
      (int *)malloc(sizeof(ADMUX) + sizeof(ADCSRA) + sizeof(PRR));
  this->stateStorage[0] = ADMUX;
  this->stateStorage[1] = ADCSRA;
  this->stateStorage[2] = PRR;
#elif defined(__AVR_ATtiny828__)
  this->stateStorage = (int *)malloc(sizeof(ADMUXA) + sizeof(ADMUXB) +
                                     sizeof(ADCSRA) + sizeof(PRR));
  this->stateStorage[0] = ADMUXA;
  this->stateStorage[1] = ADMUXB;
  this->stateStorage[2] = ADCSRA;
  this->stateStorage[3] = PRR;
#endif
}

void AVRInternalTemperatureSensor::restoreState() {
  if (this->stateStorage == nullptr) {
    return;
  }

#if defined(__AVR_ATmega48A__) || defined(__AVR_ATmega48PA__) ||               \
    defined(__AVR_ATmega88A__) || defined(__AVR_ATmega88PA__) ||               \
    defined(__AVR_ATmega168A__) || defined(__AVR_ATmega168PA__) ||             \
    defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
  ADMUX = this->stateStorage[0];
  ADCSRA = this->stateStorage[1];
  PRR = this->stateStorage[2];
#elif defined(__AVR_ATtiny828__)
  ADMUXA = this->stateStorage[0];
  ADMUXB = this->stateStorage[1];
  ADCSRA = this->stateStorage[2];
  PRR = this->stateStorage[3];
#endif

  free(this->stateStorage);
  this->stateStorage = nullptr;
}
