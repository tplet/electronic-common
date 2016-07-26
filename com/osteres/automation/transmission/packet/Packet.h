//
// Created by Thibault PLET <thibault.plet@gmail.com> on 01/04/2016.
//

#ifndef COM_OSTERES_AUTOMATION_TRANSMISSION_PACKET_PACKET_H
#define COM_OSTERES_AUTOMATION_TRANSMISSION_PACKET_PACKET_H

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
                    class Packet {
                    public:
                        /**
                         * Constructor
                         */
                        Packet();

                        /**
                         * Constructor with sensor
                         */
                        Packet(unsigned char sensor);

                        /**
                         * Constructor with sensor and id
                         */
                        Packet(unsigned char sensor, unsigned char id);

                        /**
                         * Destructor
                         */
                        ~Packet();

                        /**
                         * Get request identifier
                         */
                        unsigned char getId();

                        /**
                         * Set request identifier
                         */
                        void setId(unsigned char id);

                        /**
                         * Set request identifier to next value
                         */
                        void nextId();

                        /**
                         * Get sensor identifier
                         */
                        unsigned char getSensor();

                        /**
                         * Set sensor identifier
                         */
                        void setSensor(unsigned char sensor);

                        /**
                         * Get command identifier
                         */
                        unsigned char getCommand();

                        /**
                         * Set command identifier
                         */
                        void setCommand(unsigned char command);

                        /**
                         * Get target of request
                         */
                        unsigned char getTarget();

                        /**
                         * Set target of request
                         */
                        void setTarget(unsigned char target);

                        /**
                         * Get timestamp associated to data
                         */
                        unsigned long int getDate();

                        /**
                         * Set timestamp associated to data
                         */
                        void setDate(unsigned long int date);

                        /**
                         * Flag to indicate that packet is the last.
                         * It's mean that there is no packet to receive after this one (source queue empty)
                         */
                        bool isLast();

                        /**
                         * Set flag to indicate that packet is the last.
                         * It's mean that there is no packet to receive after this one (source queue empty)
                         */
                        void setLast(bool last);

                        /**
                         * Reset all data contained in request
                         */
                        void resetData();

                        unsigned char getDataUChar1();

                        unsigned char getDataUChar2();

                        unsigned char getDataUChar3();

                        unsigned char getDataUChar4();

                        void setDataUChar1(unsigned char data);

                        void setDataUChar2(unsigned char data);

                        void setDataUChar3(unsigned char data);

                        void setDataUChar4(unsigned char data);

                        long getDataLong1();

                        long getDataLong2();

                        long getDataLong3();

                        long getDataLong4();

                        void setDataLong1(long data);

                        void setDataLong2(long data);

                        void setDataLong3(long data);

                        void setDataLong4(long data);

                        char getDataChar1();

                        char getDataChar2();

                        char getDataChar3();

                        void setDataChar1(char data);

                        void setDataChar2(char data);

                        void setDataChar3(char data);

                    protected:
                        /**
                         * Constructor
                         */
                        void construct(unsigned char sensor, unsigned char id);

                        /**
                         * Packet identifier (uniq for each running sensor)
                         *
                         * 1 byte
                         */
                        unsigned char id;

                        /**
                         * Sensor identifier (uniq for all automation park)
                         *
                         * 1 byte
                         */
                        unsigned char sensor;

                        /**
                         * Command identifier
                         *
                         * 1 byte
                         */
                        unsigned char command;

                        /**
                         * Target of request
                         *
                         * 1 byte
                         */
                        unsigned char target;

                        /**
                         * Flag to indicate that packet is the last.
                         * It's mean that there is no packet to receive after this one (source queue empty)
                         *
                         * 1 byte
                         */
                        bool last = true;

                        /**
                         * Timestamp associated to data
                         *
                         * 4 byte
                         */
                        unsigned long int date;

                        /**
                         * Containers
                         * Be careful to not exceed 32 bytes on total properties size!
                         * Actually: 32 bytes (23 bytes for data)
                         *
                         * Check var type size between arduino and raspberry before declare it
                         * Raspbberry unknow: When 30 bytes declared, sizeof(request) equal to 32... Work with step ?
                         *                   (4, 8, 16, 32 ?)
                         *                   To fix, ensure that exactly one of these step defined
                         */

                        /**
                         * Data byte containers
                         * 4 x 1 byte = 4 bytes
                         */
                        unsigned char dataUChar1;
                        unsigned char dataUChar2;
                        unsigned char dataUChar3;
                        unsigned char dataUChar4;

                        /**
                         * Data long containers
                         * 4 x 4 bytes = 16 bytes
                         */
                        long dataLong1;
                        long dataLong2;
                        long dataLong3;
                        long dataLong4;

                        /**
                         * Data chart containers
                         * 3 x 1 byte = 3 bytes
                         */
                        char dataChart1;
                        char dataChart2;
                        char dataChart3;

                    };
                }
            }
        }
    }
}
#endif //COM_OSTERES_AUTOMATION_TRANSMISSION_PACKET_PACKET_H
