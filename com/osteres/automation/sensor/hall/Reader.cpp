//
// Created by Thibault PLET on 30/04/2016.
//

#include <stdint.h>
#include "Reader.h"
#include <Arduino.h>

using namespace com::osteres::automation::sensor::hall;


/**
 * Constructor with pin definition
 */
Reader::Reader(uint8_t pin) {
    this->setPin(pin);
    this->setThreshold(DEFAULT_THRESHOLD);
    this->state = true;
    this->stateChanged = true;
}

/**
 * Constructor with pin and threshold definition
 */
Reader::Reader(uint8_t pin, unsigned int threshold) {
    this->setPin(pin);
    this->setThreshold(threshold);
    this->state = true;
    this->stateChanged = true;
}

/**
 * Set pin
 */
Reader Reader::setPin(uint8_t pin) {
    this->pin = pin;

    return *this;
}

/**
 * Get pin
 */
uint8_t Reader::getPin() {
    return this->pin;
}

/**
 * Set threshold
 */
Reader Reader::setThreshold(unsigned int threshold) {
    this->threshold = threshold;

    return *this;
}

/**
 * Get Threshold
 */
unsigned int Reader::getThreshold() {
    return this->threshold;
}

/**
 * Get value
 */
unsigned int Reader::getValue() {
    return this->value;
}

/**
 * Set value
 */
Reader Reader::setValue(unsigned int value) {
    this->value = value;

    return *this;
}

/**
 * Read value from pin
 */
unsigned int Reader::readValue() {
    // Read
    unsigned int v = analogRead(this->getPin());

    // Save
    this->setValue(v);

    // Update state
    this->updateState();

    return v;
}

/**
 * Update state
 */
bool Reader::updateState() {

    bool previousState = this->getState();

    // Compare value and threshold
    bool state = this->getValue() < this->getThreshold();

    if (state != previousState) {
        this->stateChanged = true;
        this->state = state;
    } else {
        this->stateChanged = false;
    }

    return state;
}

/**
 * Is high state (stable state)
 */
bool Reader::isHigh(bool refresh) {
    return this->getState(refresh);
}

/**
 * Is low state (event state)
 */
bool Reader::isLow(bool refresh) {
    return !this->getState(refresh);
}

/**
 * Get state
 */
bool Reader::getState(bool refresh) {
    if (refresh) {
        this->readValue();
    }

    return this->state;
}

/**
 * Flag to indicate if state has changed since last read
 */
bool Reader::isStateChanged() {
    return this->stateChanged;
}

