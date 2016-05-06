//
// Created by Thibault PLET on 11/04/2016.
//

#ifndef COM_OSTERES_AUTOMATION_TRANSMISSION_PACKET_COMMAND_H
#define COM_OSTERES_AUTOMATION_TRANSMISSION_PACKET_COMMAND_H

typedef uint8_t byte;

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
                        static uint64_t const CHANNEL_SLAVE = 0xFF0000000001;
                        /**
                         * Channel for slave
                         */
                        static uint64_t const CHANNEL_MASTER = 0xFF0000000002;

                        /**
                         * Universal OK response to indicate that request correctly received
                         */
                        static byte const OK = 0x01;
                        /**
                         * Ask to get datetime
                         */
                        static byte const DATETIME_REQUEST = 0x02;
                        /**
                         * Response for datetime request
                         */
                        static byte const DATETIME_RESPONSE = 0x03;
                        /**
                         * Send data (depend on main role of each sensor)
                         */
                        static byte const DATA = 0x04;
                        /**
                         * Init phase (depend on main role of each sensor)
                         */
                        static byte const INIT = 0x05;
                    };
                }
            }
        }
    }
}

#endif //COM_OSTERES_AUTOMATION_TRANSMISSION_PACKET_COMMAND_H
