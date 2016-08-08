//
// Created by Thibault PLET on 28/05/2016.
//

#ifndef COM_OSTERES_UTIL_FORMATTER_NUMBER_H
#define COM_OSTERES_UTIL_FORMATTER_NUMBER_H

#include <string>

using std::string;
using std::to_string;

namespace com {
    namespace osteres {
        namespace util {
            namespace formatter {
                class Number {
                public:
                    /**
                     * Generate string from int value and add "0" prefix if value lower than 10
                     *
                     * @param uint8_t value
                     */
                    static string twoDigit(uint8_t value) {
                        return (value < 10 ? "0" : "") + to_string(value);
                    }
                };
            }
        }
    }
}


#endif //COM_OSTERES_UTIL_FORMATTER_NUMBER_H
