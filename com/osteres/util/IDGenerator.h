//
// Created by Thibault PLET on 09/04/2016.
//

#ifndef COM_OSTERES_UTIL_IDGENERATOR_H
#define COM_OSTERES_UTIL_IDGENERATOR_H

namespace com
{
    namespace osteres
    {
        namespace util
        {
            class IDGenerator
            {

            protected:
                /**
                 * @static
                 *
                 * Uniq identifier
                 */
                static unsigned char uniqId;

            public:
                /**
                 * @static
                 *
                 * Get next request identifier
                 */
                static unsigned char getNextId();
            };
        }
    }
}

#endif //COM_OSTERES_UTIL_IDGENERATOR_H
