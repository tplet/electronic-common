//
// Created by Thibault PLET on 09/04/2016.
//

#include "IDGenerator.h"

typedef unsigned char byte;

namespace com
{
    namespace osteres
    {
        namespace automation
        {
            namespace sensor
            {
                /**
                 * Init uniq id value
                 */
                byte IDGenerator::uniqId = 1;

                /**
                 * @static
                 *
                 * Get next packet identifier
                 */
                byte IDGenerator::getNextId()
                {
                    return uniqId++;
                }
            }
        }
    }
}

