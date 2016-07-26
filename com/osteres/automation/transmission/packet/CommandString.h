//
// Created by Thibault PLET on 11/04/2016.
//

#ifndef COM_OSTERES_AUTOMATION_TRANSMISSION_PACKET_COMMANDSTRING_H
#define COM_OSTERES_AUTOMATION_TRANSMISSION_PACKET_COMMANDSTRING_H

#include <com/osteres/automation/transmission/packet/Command.h>

using com::osteres::automation::transmission::packet::Command;

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
                        static String toString(unsigned char command)
                        {
                            String s;
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
                                default:
                                    s = "";
                                    break;
                            }

                            return s;
                        }

                        /**
                         * Transpose channel code to string representation
                         */
                        static String toString(unsigned long long channel)
                        {
                            String s;
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
