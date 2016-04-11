//
// Created by Thibault PLET on 11/04/2016.
//

#ifndef COM_OSTERES_AUTOMATION_SENSOR_SENSOR_H
#define COM_OSTERES_AUTOMATION_SENSOR_SENSOR_H

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
                 * All sensors available
                 */
                class Sensor
                {
                public:
                    /**
                     * Master server
                     *
                     * @used by master server
                     */
                    static byte const MASTER = 0x00;
                    /**
                     * All sensor
                     * Special sensor id to indicate that the target is all sensors which
                     * receive the request
                     */
                    static byte const ALL = 0x01;
                    /**
                     * Hall sensor
                     *
                     * @used by Gas meter reader
                     */
                    static byte const HALL = 0x02;
                };
            }
        }
    }
}

#endif //COM_OSTERES_AUTOMATION_SENSOR_SENSOR_H
