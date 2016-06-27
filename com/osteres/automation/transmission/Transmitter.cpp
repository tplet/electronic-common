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
 * Constructor
 */
Transmitter::Transmitter(RF24 * radio, byte sensor)
{
    Transmitter::construct(radio, sensor, false);
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

    // Channels
    uint64_t writingChannel = Command::CHANNEL_SLAVE;
    uint64_t readingChannel = Command::CHANNEL_MASTER;
    if (this->isMaster()) {
        writingChannel = Command::CHANNEL_MASTER;
        readingChannel = Command::CHANNEL_SLAVE;
    }
    this->setReadingChannel(readingChannel);
    this->setWritingChannel(writingChannel);
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