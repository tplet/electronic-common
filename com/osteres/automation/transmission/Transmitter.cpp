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
Transmitter::Transmitter()
{
    this->useDefaultTTL();
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