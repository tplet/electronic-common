//
// Created by Thibault PLET on 11/04/2016.
//

#ifndef COM_OSTERES_AUTOMATION_SENSOR_SENSOR_H
#define COM_OSTERES_AUTOMATION_SENSOR_SENSOR_H

namespace com
{
    namespace osteres
    {
        namespace automation
        {
            namespace sensor
            {
                /**
                 * All sensors available
                 */
                class Identity
                {
                public:
                    /**
                     * Master server
                     *
                     * @used by master server
                     */
                    static unsigned char const MASTER = 0x00;
                    /**
                     * All sensor
                     * Special sensor id to indicate that the target is all sensors which
                     * receive the request
                     */
                    static unsigned char const ALL = 0x01;
                    /**
                     * Hall sensor
                     *
                     * @used by Gas meter reader
                     */
                    static unsigned char const HALL = 0x02;
                    /**
                     * Weather sensor
                     * Read ambiant temperature and humidity
                     *
                     * @used by Weather sensor
                     */
                    static unsigned char const WEATHER = 0x03;
                    /**
                     * Movement sensor
                     * Detect movement in room
                     *
                     * @used by Movement sensor
                     */
                    static unsigned char const MOVEMENT = 0x04;
                    /**
                     * Controlled switch
                     * Open and close switch from remote control
                     *
                     * @used by Controlled time switch actuator
                     */
                    static unsigned char const SWITCH = 0x05;
                };
            }
        }
    }
}

#endif //COM_OSTERES_AUTOMATION_SENSOR_SENSOR_H
