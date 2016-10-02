//
// Created by Thibault PLET on 06/05/2016.
//

#include "Receiver.h"
#include <com/osteres/automation/polyfill/millis.h>

using namespace com::osteres::automation::transmission;
/**
 * Constructor
 */
Receiver::Receiver(RF24 * radio, unsigned long long readingChannel, unsigned int timeout = 1000) {
    this->radio = radio;
    this->setReadingChannel(readingChannel);
    this->timeout = timeout;
}

/**
 * Destructor
 */
Receiver::~Receiver() {
    this->cleanResponse();
}

/**
 * Clean class
 */
void Receiver::cleanResponse() {
    if (this->hasResponse()) {
        delete this->response;
        this->response = NULL;
    }
}

/**
 * Listen response
 */
bool Receiver::listen() {
    // Ensure that no previous response (for memory security)
    this->cleanResponse();

    // Reading channel
    this->radio->openReadingPipe(1, this->readingChannel);

    // Start listening
    this->radio->startListening();

    // Prepare timeout
    unsigned long start = millis();
    bool toReceive = true;
    bool noResponse = false;
    bool available = false;
    Packet * response = NULL;

    // Try to read data
    while (toReceive) {
        // Waiting for reading data
        do {
            available = this->radio->available();
            if (millis() - start > this->timeout) {
                noResponse = true;
                toReceive = false;
            }
        } while (!available && !noResponse);

        // Read response if available
        if (available) {
            // Clean previous response and prepare another
            this->cleanResponse();
            response = new Packet();

            // Read response
            while (this->radio->available()) {
                this->radio->read(response, sizeof(Packet));
            }

            // Check if packet are right destined to this (false positive),
            // if not, try again until packet received is for this sensor (can take a long time if many packet exchanged)
            if (response != NULL && this->hasPropertySensorType() && response->getTarget() != this->propertySensorType->get()) {
                delete response;
                response = NULL;
                // Then, listen again response
            } // Response successfully received
            else {
                toReceive = false;
                this->response = response;
            }
        }
    }

    // Stop listening
    this->radio->stopListening();

    // Return flag to indicate if response has been received
    return !noResponse;
}

/**
 * Flag to indicate if response has been received
 */
bool Receiver::hasResponse() {
    return this->response != NULL;
}

/**
 * Get response received
 */
Packet * Receiver::getResponse() {
    return this->response;
}

/**
 * Set timeout
 */
void Receiver::setTimeout(unsigned int timeout)
{
    this->timeout = timeout;
}

/**
 * Get timeout
 */
unsigned int Receiver::getTimeout()
{
    return this->timeout;
}


/**
 * Set channel to read
 */
void Receiver::setReadingChannel(unsigned long long readingChannel)
{
    this->readingChannel = readingChannel;
}

/**
 * Set sensor type identifier property
 */
void Receiver::setPropertySensorType(Property<unsigned char> * property)
{
    this->propertySensorType = property;
}

/**
 * Flag to indicate if sensor type identifier propery has been defined
 */
bool Receiver::hasPropertySensorType()
{
    return this->propertySensorType != NULL;
}

/**
 * Set sensor identifier property
 */
void Receiver::setPropertySensorIdentifier(Property<unsigned char> * property)
{
    this->propertySensorIdentifier = property;
}

/**
 * Flag to indicate if sensor identifier propery has been defined
 */
bool Receiver::hasPropertySensorIdentifier()
{
    return this->propertySensorIdentifier != NULL;
}