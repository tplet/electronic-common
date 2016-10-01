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
Transmitter::Transmitter(RF24 * radio, bool isMaster)
{
    Transmitter::construct(radio, isMaster);
}

/**
 * Destructor
 */
Transmitter::~Transmitter()
{
    // Remove requester and receiver
    if (this->requester != NULL) {
        delete this->requester;
        this->requester = NULL;
    }
    if (this->receiver != NULL) {
        delete this->receiver;
        this->receiver = NULL;
    }
}

/**
 * Constructor
 */
void Transmitter::construct(RF24 * radio, bool isMaster)
{
    this->radio = radio;
    this->master = isMaster;

    // Channels
    unsigned long long writingChannel = Command::CHANNEL_SLAVE;
    unsigned long long readingChannel = Command::CHANNEL_MASTER;
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
void Transmitter::setActionManager(ActionManagerBase * actionManager) {
    this->actionManager = actionManager;
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

/**
 * Flag to indicate if receiver is defined
 */
bool Transmitter::hasReceiver()
{
    return this->receiver != NULL;
}

/**
 * Set requester
 */
void Transmitter::setRequester(Requester * requester)
{
    this->requester = requester;
}

/**
 * Set receiver
 */
void Transmitter::setReceiver(Receiver * receiver)
{
    this->receiver = receiver;

    // Apply properties if available
    if (this->hasPropertySensorType()) {
        this->receiver->setPropertySensorType(this->propertySensorType);
    }
    if (this->hasPropertySensorIdentifier()) {
        this->receiver->setPropertySensorIdentifier(this->propertySensorIdentifier);
    }
}
