//
// Created by Thibault PLET <thibault.plet@gmail.com> on 01/04/2016.
//
#include "Arduino.h"
#include "Packet.h"


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
    id = 0x0;
    sensor = 0x0;
    date = 0;
    data = 0;
}

/*Packet::Packet(byte s, byte i)
{
    sensor = s;
    id = i;
}*/

/**
 * Get identifier
 */
byte Packet::getId()
{
    return id;
}

/**
 * Set identifier
 */
void Packet::setId(byte i)
{
    id = i;
}
            }
        }
    }
}