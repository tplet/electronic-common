//
// Created by Thibault PLET on 11/04/2016.
//

#ifndef COM_OSTERES_AUTOMATION_TRANSMISSION_PACKET_COMMANDSTRING_H
#define COM_OSTERES_AUTOMATION_TRANSMISSION_PACKET_COMMANDSTRING_H

#include <string>
#include <com/osteres/automation/transmission/packet/Command.h>

using com::osteres::automation::transmission::packet::Command;
using namespace std;

namespace com
{
    namespace osteres
    {
        namespace automation
        {
            namespace transmission
            {
                namespace packet
                {
                    /**
                     * All command available
                     */
                    class CommandString {
                    public:

                        /**
                         * Transpose command code to string representation
                         */
                        static string toString(unsigned char command)
                        {
                            string s;
                            switch (command) {
                                case Command::OK:
                                    s = "OK";
                                    break;
                                case Command::DATETIME_REQUEST:
                                    s = "DATETIME_REQUEST";
                                    break;
                                case Command::DATETIME_RESPONSE:
                                    s = "DATETIME_RESPONSE";
                                    break;
                                case Command::DATA:
                                    s = "DATA";
                                    break;
                                case Command::INIT:
                                    s = "INIT";
                                    break;
                                case Command::IDENTIFIER_REQUEST:
                                    s = "IDENTIFIER_REQUEST";
                                    break;
                                case Command::IDENTIFIER_RESPONSE:
                                    s = "IDENTIFIER_RESPONSE";
                                    break;
                                case Command::BATTERY:
                                    s = "BATTERY";
                                    break;
                                default:
                                    s = "";
                                    break;
                            }

                            return s;
                        }

                        /**
                         * Transpose channel code to string representation
                         */
                        static string toString(unsigned long long channel)
                        {
                            string s;
                            switch (channel) {
                                case Command::CHANNEL_MASTER:
                                    s = "CHANNEL_MASTER";
                                    break;
                                case Command::CHANNEL_SLAVE:
                                    s = "CHANNEL_SLAVE";
                                    break;
                                default:
                                    s = "";
                                    break;
                            }

                            return s;
                        }
                    };
                }
            }
        }
    }
}

#endif //COM_OSTERES_AUTOMATION_TRANSMISSION_PACKET_COMMANDSTRING_H
