//
// Created by Thibault PLET <thibault.plet@gmail.com> on 01/04/2016.
//

#ifndef COM_OSTERES_AUTOMATION_TRANSMISSION_PACKET_PACKET_H
#define COM_OSTERES_AUTOMATION_TRANSMISSION_PACKET_PACKET_H

#include <inttypes.h>

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
                         * Constructor with sensor type
                         */
                        Packet(uint8_t sourceType);

                        /**
                         * Constructor with sensor type and id
                         */
                        Packet(uint8_t sourceType, uint8_t id);

                        /**
                         * Copy constructor
                         */
                        Packet(Packet * packet);

                        /**
                         * Destructor
                         */
                        ~Packet();

                        /**
                         * Get request identifier
                         */
                        uint8_t getId();

                        /**
                         * Set request identifier
                         */
                        void setId(uint8_t id);

                        /**
                         * Set request identifier to next value
                         */
                        void nextId();

                        /**
                         * Get sensor type identifier
                         */
                        uint8_t getSourceType();

                        /**
                         * Set sensor type identifier
                         */
                        void setSourceType(uint8_t type);

                        /**
                         * Get sensor identifier (uniq for all automation park)
                         */
                        uint8_t getSourceIdentifier();

                        /**
                         * Set sensor identifier (uniq for all automation park)
                         */
                        void setSourceIdentifier(uint8_t identifier);

                        /**
                         * Get command identifier
                         */
                        uint8_t getCommand();

                        /**
                         * Set command identifier
                         */
                        void setCommand(uint8_t command);

                        /**
                         * Get target of request
                         */
                        uint8_t getTarget();

                        /**
                         * Set target of request
                         */
                        void setTarget(uint8_t target);

                        /**
                         * Get timestamp associated to data
                         */
                        uint32_t getDate();

                        /**
                         * Set timestamp associated to data
                         */
                        void setDate(uint32_t date);

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

                        uint8_t getDataUChar1();

                        uint8_t getDataUChar2();

                        uint8_t getDataUChar3();

                        void setDataUChar1(uint8_t data);

                        void setDataUChar2(uint8_t data);

                        void setDataUChar3(uint8_t data);

                        int32_t getDataLong1();

                        int32_t getDataLong2();

                        int32_t getDataLong3();

                        int32_t getDataLong4();

                        void setDataLong1(int32_t data);

                        void setDataLong2(int32_t data);

                        void setDataLong3(int32_t data);

                        void setDataLong4(int32_t data);

                        int8_t getDataChar1();

                        int8_t getDataChar2();

                        int8_t getDataChar3();

                        void setDataChar1(int8_t data);

                        void setDataChar2(int8_t data);

                        void setDataChar3(int8_t data);

                    protected:
                        /**
                         * Constructor
                         */
                        void construct(uint8_t sensor, uint8_t id);

                        /**
                         * Timestamp associated to data
                         *
                         * 4 bytes
                         */
                        uint32_t date;

                        /**
                         * Containers
                         * Be careful to not exceed 32 bytes on total properties size!
                         * Actually: 32 bytes (22 bytes for data)
                         *
                         * Check var type size between arduino and raspberry before declare it
                         * Raspbberry unknow: When 30 bytes declared, sizeof(request) equal to 32... Work with step ?
                         *                   (4, 8, 16, 32 ?)
                         *                   To fix, ensure that exactly one of these step defined
                         *
                         * Size of class also depend of property order!
                         * In this case, all '4 bytes' properties are declared in first, then the small properties
                         * (all the properties use 1 byte in this case)
                         */

                        /**
                         * Data long containers
                         * 4 x 4 bytes = 16 bytes
                         */
                        int32_t dataLong1;
                        int32_t dataLong2;
                        int32_t dataLong3;
                        int32_t dataLong4;

                        /**
                         * Data byte containers
                         * 3 x 1 byte = 3 bytes
                         */
                        uint8_t dataUChar1;
                        uint8_t dataUChar2;
                        uint8_t dataUChar3;

                        /**
                         * Data char containers
                         * 3 x 1 byte = 3 bytes
                         */
                        int8_t dataChart1;
                        int8_t dataChart2;
                        int8_t dataChart3;
                        /**
                         * Packet identifier (uniq for each running sensor)
                         *
                         * 1 byte
                         */
                        uint8_t id;

                        /**
                         * Sensor type identifier
                         *
                         * 1 byte
                         */
                        uint8_t sourceType;

                        /**
                         * Sensor identifier (uniq for all automation park)
                         */
                        uint8_t sourceIdentifier;

                        /**
                         * Command identifier
                         *
                         * 1 byte
                         */
                        uint8_t command;

                        /**
                         * Target of request
                         *
                         * 1 byte
                         */
                        uint8_t target;

                        /**
                         * Flag to indicate that packet is the last.
                         * It's mean that there is no packet to receive after this one (source queue empty)
                         *
                         * 1 byte
                         */
                        bool last = true;
                    };
                }
            }
        }
    }
}
#endif //COM_OSTERES_AUTOMATION_TRANSMISSION_PACKET_PACKET_H
