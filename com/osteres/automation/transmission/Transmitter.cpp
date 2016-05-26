//
// Created by Thibault PLET on 04/05/2016.
//

#include "Transmitter.h"

using namespace com::osteres::automation::transmission;

/**
 * Default ttl (in seconds)
 */
unsigned int Transmitter::defaultTtl = 1000;

/**
 * Constructor
 */
Transmitter::Transmitter(RF24 &radio, byte sensor)
{
    this->useDefaultTTL();
    this->radio = &radio;
    this->sensor = sensor;
}

/**
 * Get ttl before timeout (in seconds)
 */
unsigned int Transmitter::getTTL()
{
    return this->ttl;
}

/**
 * Set ttl before timeout (in seconds)
 */
void Transmitter::setTTL(unsigned int ttl)
{
    this->ttl = ttl;
}

/**
 * Restore to default ttl defined (in seconds)
 */
void Transmitter::useDefaultTTL()
{
    this->setTTL(getDefaultTTL());
}

/**
 * Get default ttl before timeout (in seconds)
 */
unsigned int Transmitter::getDefaultTTL()
{
    return defaultTtl;
}

/**
 * Set default ttl before timeout (in seconds)
 */
void Transmitter::setDefaultTTL(unsigned int ttl)
{
    defaultTtl = ttl;
}

/**
 * Action manager setter
 */
Transmitter Transmitter::setActionManager(ActionManagerBase &actionManager) {
    this->actionManager = &actionManager;

    return *this;
}

/**
 * Get requester
 * Initialize it if necessary
 */
Requester Transmitter::getRequester() {
    if (this->requester == 0) {
        this->requester = new Requester(*this->radio);
    }

    return *this->requester;
}

/**
 * Get receiver
 * Initialize if if necessary
 */
Receiver Transmitter::getReceiver() {
    if (this->receiver == 0) {
        this->receiver = new Receiver(*this->radio, this->sensor, this->getTTL());
    }

    return *this->receiver;
}