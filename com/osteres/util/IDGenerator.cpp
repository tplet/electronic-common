//
// Created by Thibault PLET on 09/04/2016.
//

#include "IDGenerator.h"

using namespace com::osteres::util;

/**
 * Init uniq id value
 */
unsigned char IDGenerator::uniqId = 1;

/**
 * @static
 *
 * Get next request identifier
 */
unsigned char IDGenerator::getNextId()
{
    return uniqId++;
}

