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
                };
            }
        }
    }
}

#endif //COM_OSTERES_AUTOMATION_SENSOR_SENSOR_H
