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
                     * Hall sensor
                     *
                     * @used by Gas meter reader
                     */
                    static byte const HALL = 0x01;
                };
            }
        }
    }
}

#endif //COM_OSTERES_AUTOMATION_SENSOR_SENSOR_H
