//
// Created by Thibault PLET <thibault.plet@gmail.com> on 01/04/2016.
//
#include <stdint.h>
#include "Packet.h"
#include "IDGenerator.h"
#include <string.h>

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
                 * Constructor
                 */
                Packet::Packet()
                {
                    this->id = 0x0;
                    this->sensor = 0x0;
                    this->date = 0;
                }

                Packet::Packet(byte s, byte i)
                {
                    this->sensor = s;
                    this->id = i;
                    this->date = 0;
                }

                /**
                 * Destructor
                 */
                Packet::~Packet()
                {
                    // Nothing to do
                }

                /**
                 * Get identifier
                 */
                byte Packet::getId()
                {
                    return this->id;
                }

                /**
                 * Set identifier
                 */
                void Packet::setId(byte i)
                {
                    this->id = i;
                }

                /**
                 * Get sensor identifier
                 */
                byte Packet::getSensor()
                {
                    return this->sensor;
                }

                /**
                 * Set sensor identifier
                 */
                void Packet::setSensor(byte sensor)
                {
                    this->sensor = sensor;
                }

                /**
                 * Get timestamp associated to data
                 */
                unsigned long int Packet::getDate()
                {
                    return this->date;
                }

                /**
                 * Set timestamp associated to data
                 */
                void Packet::setDate(unsigned long int date)
                {
                    this->date = date;
                }

                byte Packet::getDataByte1()
                { return this->dataByte1; }

                byte Packet::getDataByte2()
                { return this->dataByte2; }

                byte Packet::getDataByte3()
                { return this->dataByte3; }

                byte Packet::getDataByte4()
                { return this->dataByte4; }

                byte Packet::getDataByte5()
                { return this->dataByte5; }

                byte Packet::getDataByte6()
                { return this->dataByte6; }

                void Packet::setDataByte1(byte data)
                { this->dataByte1 = data; }

                void Packet::setDataByte2(byte data)
                { this->dataByte2 = data; }

                void Packet::setDataByte3(byte data)
                { this->dataByte3 = data; }

                void Packet::setDataByte4(byte data)
                { this->dataByte4 = data; }

                void Packet::setDataByte5(byte data)
                { this->dataByte5 = data; }

                void Packet::setDataByte6(byte data)
                { this->dataByte6 = data; }

                long Packet::getDataLong1()
                { return this->dataLong1; }

                long Packet::getDataLong2()
                { return this->dataLong2; }

                long Packet::getDataLong3()
                { return this->dataLong3; }

                long Packet::getDataLong4()
                { return this->dataLong4; }

                void Packet::setDataLong1(long data)
                { this->dataLong1 = data; }

                void Packet::setDataLong2(long data)
                { this->dataLong2 = data; }

                void Packet::setDataLong3(long data)
                { this->dataLong3 = data; }

                void Packet::setDataLong4(long data)
                { this->dataLong4 = data; }

                char Packet::getDataChar1()
                { return this->dataChart1; }

                char Packet::getDataChar2()
                { return this->dataChart2; }

                char Packet::getDataChar3()
                { return this->dataChart3; }

                char Packet::getDataChar4()
                { return this->dataChart4; }

                void Packet::setDataChar1(char data)
                { this->dataChart1 = data; }

                void Packet::setDataChar2(char data)
                { this->dataChart2 = data; }

                void Packet::setDataChar3(char data)
                { this->dataChart3 = data; }

                void Packet::setDataChar4(char data)
                { this->dataChart4 = data; }

                /**
                 * Set packet identifier by using next uniq identifier
                 */
                void Packet::nextId()
                {
                    this->setId(com::osteres::automation::sensor::IDGenerator::getNextId());
                }
            }
        }
    }
}