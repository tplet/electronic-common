//
// Created by Thibault PLET on 28/05/2016.
//

#ifndef COM_OSTERES_UTIL_FORMATTER_NUMBER_H
#define COM_OSTERES_UTIL_FORMATTER_NUMBER_H

#include <string>
#include <sstream>

using std::string;
using std::stringstream;

namespace com {
    namespace osteres {
        namespace util {
            namespace formatter {
                class Number {
                public:
                    /**
                     * Generate string from int value and add "0" prefix if value lower than 10
                     *
                     * @param unsigned char value
                     */
                    static string twoDigit(unsigned char value) {
                        stringstream ss;
                        ss << (value < 10 ? "0" : "") << (int)value;
                        return ss.str();
                    }
                };
            }
        }
    }
}


#endif //COM_OSTERES_UTIL_FORMATTER_NUMBER_H
