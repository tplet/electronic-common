//
// Created by Thibault PLET on 11/04/2016.
//

#ifndef COM_OSTERES_AUTOMATION_TRANSMISSION_PACKET_COMMAND_H
#define COM_OSTERES_AUTOMATION_TRANSMISSION_PACKET_COMMAND_H

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
                    class Command {
                    public:
                        /**
                         * Channel for slave
                         */
                        static unsigned long long const CHANNEL_SLAVE = 0xFF0000000001;
                        /**
                         * Channel for master
                         */
                        static unsigned long long const CHANNEL_MASTER = 0xFF0000000002;

                        /**
                         * Universal OK response to indicate that request correctly received
                         */
                        static unsigned char const OK = 0x01;
                        /**
                         * Ask to get datetime
                         */
                        static unsigned char const DATETIME_REQUEST = 0x02;
                        /**
                         * Response for datetime request
                         */
                        static unsigned char const DATETIME_RESPONSE = 0x03;
                        /**
                         * Send data (depend on main role of each sensor)
                         */
                        static unsigned char const DATA = 0x04;
                        /**
                         * Init phase (depend on main role of each sensor)
                         */
                        static unsigned char const INIT = 0x05;
                        /**
                         * Request to obtain a sensor identifier
                         */
                        static unsigned char const IDENTIFIER_REQUEST = 0x06;
                        /**
                         * Response contains a sensor identifier
                         */
                        static unsigned char const IDENTIFIER_RESPONSE = 0x07;
                        /**
                         * Send battery level
                         */
                        static unsigned char const BATTERY = 0x08;
                    };
                }
            }
        }
    }
}

#endif //COM_OSTERES_AUTOMATION_TRANSMISSION_PACKET_COMMAND_H
