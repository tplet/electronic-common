//
// Created by Thibault PLET on 04/05/2016.
//

#include "Transmitter.h"

using namespace com::osteres::automation::transmission;

/**
 * Default ttl (in milliseconds)
 */
unsigned int Transmitter::defaultTtl = 1000;

/**
 * Constructor
 */
Transmitter::Transmitter(RF24 * radio, byte sensor, bool isMaster)
{
    Transmitter::construct(radio, sensor, isMaster);
}

/**
 * Destructor
 */
Transmitter::~Transmitter()
{
    // Remove requester and receiver
    delete this->requester;
    delete this->receiver;
}

/**
 * Constructor
 */
void Transmitter::construct(RF24 * radio, byte sensor, bool isMaster)
{
    this->radio = radio;
    this->sensor = sensor;
    this->master = master;

    // Prepare requester and receiver
    this->requester = new Requester(this->radio);
    this->receiver = new Receiver(this->radio, this->sensor, getDefaultTTL());
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
Transmitter * Transmitter::setActionManager(ActionManagerBase * actionManager) {
    this->actionManager = actionManager;

    return this;
}

/**
 * Get requester
 * Initialize it if necessary
 */
Requester * Transmitter::getRequester() {
    return this->requester;
}

/**
 * Get receiver
 * Initialize if if necessary
 */
Receiver * Transmitter::getReceiver() {
    return this->receiver;
}