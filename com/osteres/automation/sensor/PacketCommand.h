//
// Created by Thibault PLET on 11/04/2016.
//

#ifndef COM_OSTERES_AUTOMATION_SENSOR_PACKETCOMMAND_H
#define COM_OSTERES_AUTOMATION_SENSOR_PACKETCOMMAND_H

typedef uint8_t byte;

namespace com
{
    namespace osteres
    {
        namespace automation
        {
            namespace sensor
            {
                /**
                 * All command available
                 */
                class PacketCommand
                {
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
                     * Ask to get datetime
                     */
                    static byte const DATETIME_REQUEST = 0x01;
                    /**
                     * Response for datetime request
                     */
                    static byte const DATETIME_RESPONSE = 0x02;
                    /**
                     * Send data (depend on main role of each sensor)
                     */
                    static byte const DATA = 0x03;
                };
            }
        }
    }
}

#endif //COM_OSTERES_AUTOMATION_SENSOR_PACKETCOMMAND_H
