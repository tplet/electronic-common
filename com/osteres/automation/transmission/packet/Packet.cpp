//
// Created by Thibault PLET <thibault.plet@gmail.com> on 01/04/2016.
//
#include <stdint.h>
#include "Packet.h"
#include <com/osteres/util/IDGenerator.h>

typedef uint8_t byte;

using namespace com::osteres::automation::transmission::packet;
namespace util = com::osteres::util;

/**
 * Constructor
 */
Packet::Packet()
{
    this->resetData();
    this->sensor = 0;
    this->id = 0;
    this->date = 0;
    this->target = 0;
    this->command = 0;
    this->last = false;
    this->date = 0;
}

/**
 * Constructor with sensor
 */
Packet::Packet(byte sensor)
{
    this->resetData();
    this->sensor = sensor;
    this->id = 0;
    this->date = 0;
    this->target = 0;
    this->command = 0;
    this->last = false;
    this->date = 0;
}

/**
 * Constructor with sensor and packet id
 */
Packet::Packet(byte sensor, byte id)
{
    this->resetData();
    this->sensor = sensor;
    this->id = id;
    this->date = 0;
    this->target = 0;
    this->command = 0;
    this->last = false;
    this->date = 0;
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
 * Get command identifier
 */
byte Packet::getCommand()
{
    return this->command;
}

/**
 * Set command identifier
 */
void Packet::setCommand(byte command)
{
    this->command = command;
}

/**
 * Get target of request
 */
byte Packet::getTarget()
{
    return this->target;
}

/**
 * Set target of request
 */
void Packet::setTarget(byte target)
{
    this->target = target;
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

/**
 * Flag to indicate that packet is the last.
 * It's mean that there is no packet to receive after this one (source queue empty)
 */
bool Packet::isLast() {
    return this->last;
}

/**
 * Set flag to indicate that packet is the last.
 * It's mean that there is no packet to receive after this one (source queue empty)
 */
void Packet::setLast(bool last) {
    this->last = last;
}

byte Packet::getDataByte1()
{ return this->dataByte1; }

byte Packet::getDataByte2()
{ return this->dataByte2; }

byte Packet::getDataByte3()
{ return this->dataByte3; }

byte Packet::getDataByte4()
{ return this->dataByte4; }

void Packet::setDataByte1(byte data)
{ this->dataByte1 = data; }

void Packet::setDataByte2(byte data)
{ this->dataByte2 = data; }

void Packet::setDataByte3(byte data)
{ this->dataByte3 = data; }

void Packet::setDataByte4(byte data)
{ this->dataByte4 = data; }

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

void Packet::setDataChar1(char data)
{ this->dataChart1 = data; }

void Packet::setDataChar2(char data)
{ this->dataChart2 = data; }

void Packet::setDataChar3(char data)
{ this->dataChart3 = data; }

/**
 * Set request identifier by using next uniq identifier
 */
void Packet::nextId()
{
    this->setId(util::IDGenerator::getNextId());
}

/**
 * Reset all data contained into request
 */
void Packet::resetData()
{
    // Byte
    this->setDataByte1(0);
    this->setDataByte2(0);
    this->setDataByte3(0);
    this->setDataByte4(0);

    // Long
    this->setDataLong1(0);
    this->setDataLong2(0);
    this->setDataLong3(0);
    this->setDataLong4(0);

    // Char
    this->setDataChar1(0);
    this->setDataChar2(0);
    this->setDataChar3(0);
}
