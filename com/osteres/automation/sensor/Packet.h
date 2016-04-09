//
// Created by Thibault PLET <thibault.plet@gmail.com> on 01/04/2016.
//

#ifndef COM_OSTERES_AUTOMATION_SENSOR_PACKET_H
#define COM_OSTERES_AUTOMATION_SENSOR_PACKET_H

typedef unsigned char byte;

namespace com
{
    namespace osteres
    {
        namespace automation
        {
            namespace sensor
            {
                class Packet
                {
                public:
                    /**
                     * Constructor
                     */
                    Packet();

                    /**
                     * Constructor with sensor and id
                     */
                    Packet(byte sensor, byte id);

                    /**
                     * Destructor
                     */
                    ~Packet();

                    /**
                     * Get packet identifier
                     */
                    byte getId();

                    /**
                     * Set packet identifier
                     */
                    void setId(byte id);

                    /**
                     * Set packet identifier to next value
                     */
                    void nextId();

                    /**
                     * Get sensor identifier
                     */
                    byte getSensor();

                    /**
                     * Set sensor identifier
                     */
                    void setSensor(byte sensor);

                    /**
                     * Get timestamp associated to data
                     */
                    int getDate();

                    /**
                     * Set timestamp associated to data
                     */
                    void setDate(int date);

                    /**
                     * Get data
                     */
                    int getData();

                    /**
                     * Set data
                     */
                    void setData(int data);


                protected:
                    /**
                     * Packet identifier (uniq for each running sensor)
                     */
                    byte id;

                    /**
                     * Sensor identifier (uniq for all automation park)
                     */
                    byte sensor;

                    /**
                     * Timestamp associated to data
                     */
                    int date;

                    /**
                     * Data sended
                     */
                    int data;

                };
            }
        }
    }
}
#endif //COM_OSTERES_AUTOMATION_SENSOR_PACKET_H
