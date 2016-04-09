//
// Created by Thibault PLET <thibault.plet@gmail.com> on 01/04/2016.
//
#include "Packet.h"
#include "IDGenerator.h"

typedef unsigned char byte;

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
                    this->data = 0;
                }

                Packet::Packet(byte s, byte i)
                {
                    this->sensor = s;
                    this->id = i;
                    this->date = 0;
                    this->data = 0;
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
                int Packet::getDate()
                {
                    return this->date;
                }

                /**
                 * Set timestamp associated to data
                 */
                void Packet::setDate(int date)
                {
                    this->date = date;
                }

                /**
                 * Get data
                 */
                int Packet::getData()
                {
                    return this->data;
                }

                /**
                 * Set data
                 */
                void Packet::setData(int data)
                {
                    this->data = data;
                }

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