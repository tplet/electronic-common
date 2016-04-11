//
// Created by Thibault PLET on 09/04/2016.
//

#include <stdint.h>
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
                 * Get next request identifier
                 */
                byte IDGenerator::getNextId()
                {
                    return uniqId++;
                }
            }
        }
    }
}

