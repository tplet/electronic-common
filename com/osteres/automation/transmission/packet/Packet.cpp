//
// Created by Thibault PLET <thibault.plet@gmail.com> on 01/04/2016.
//
#include "Packet.h"
#include <com/osteres/util/IDGenerator.h>

using namespace com::osteres::automation::transmission::packet;
namespace util = com::osteres::util;

/**
 * Constructor
 */
Packet::Packet()
{
    this->construct(0, 0);
}

/**
 * Constructor with sensor type
 */
Packet::Packet(uint8_t sourceType)
{
    this->construct(sourceType, 0);
}

/**
 * Constructor with sensor type and packet id
 */
Packet::Packet(uint8_t sourceType, uint8_t id)
{
    this->construct(sourceType, id);
}

/**
 * Destructor
 */
Packet::~Packet()
{
    // Nothing to do
}

/**
 * Constructor
 */
void Packet::construct(uint8_t sourceType, uint8_t id)
{
    this->resetData();
    this->sourceType = sourceType;
    // Sensor identifier defined optionaly in second time
    this->sourceIdentifier = 0;
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
uint8_t Packet::getId()
{
    return this->id;
}

/**
 * Set identifier
 */
void Packet::setId(uint8_t i)
{
    this->id = i;
}

/**
 * Get sensor type identifier
 */
uint8_t Packet::getSourceType()
{
    return this->sourceType;
}

/**
 * Set sensor type identifier
 */
void Packet::setSourceType(uint8_t type)
{
    this->sourceType = type;
}

/**
 * Get sensor identifier (uniq for all automation park)
 */
uint8_t Packet::getSourceIdentifier()
{
    return this->sourceIdentifier;
}

/**
 * Set sensor identifier (uniq for all automation park)
 */
void Packet::setSourceIdentifier(uint8_t identifier)
{
    this->sourceIdentifier = identifier;
}

/**
 * Get command identifier
 */
uint8_t Packet::getCommand()
{
    return this->command;
}

/**
 * Set command identifier
 */
void Packet::setCommand(uint8_t command)
{
    this->command = command;
}

/**
 * Get target of request
 */
uint8_t Packet::getTarget()
{
    return this->target;
}

/**
 * Set target of request
 */
void Packet::setTarget(uint8_t target)
{
    this->target = target;
}

/**
 * Get timestamp associated to data
 */
uint32_t Packet::getDate()
{
    return this->date;
}

/**
 * Set timestamp associated to data
 */
void Packet::setDate(uint32_t date)
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

uint8_t Packet::getDataUChar1()
{ return this->dataUChar1; }

uint8_t Packet::getDataUChar2()
{ return this->dataUChar2; }

uint8_t Packet::getDataUChar3()
{ return this->dataUChar3; }

void Packet::setDataUChar1(uint8_t data)
{ this->dataUChar1 = data; }

void Packet::setDataUChar2(uint8_t data)
{ this->dataUChar2 = data; }

void Packet::setDataUChar3(uint8_t data)
{ this->dataUChar3 = data; }

int32_t Packet::getDataLong1()
{ return this->dataLong1; }

int32_t Packet::getDataLong2()
{ return this->dataLong2; }

int32_t Packet::getDataLong3()
{ return this->dataLong3; }

int32_t Packet::getDataLong4()
{ return this->dataLong4; }

void Packet::setDataLong1(int32_t data)
{ this->dataLong1 = data; }

void Packet::setDataLong2(int32_t data)
{ this->dataLong2 = data; }

void Packet::setDataLong3(int32_t data)
{ this->dataLong3 = data; }

void Packet::setDataLong4(int32_t data)
{ this->dataLong4 = data; }

int8_t Packet::getDataChar1()
{ return this->dataChart1; }

int8_t Packet::getDataChar2()
{ return this->dataChart2; }

int8_t Packet::getDataChar3()
{ return this->dataChart3; }

void Packet::setDataChar1(int8_t data)
{ this->dataChart1 = data; }

void Packet::setDataChar2(int8_t data)
{ this->dataChart2 = data; }

void Packet::setDataChar3(int8_t data)
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
    // unsigned char
    this->setDataUChar1(0);
    this->setDataUChar2(0);
    this->setDataUChar3(0);

    // long
    this->setDataLong1(0);
    this->setDataLong2(0);
    this->setDataLong3(0);
    this->setDataLong4(0);

    // char
    this->setDataChar1(0);
    this->setDataChar2(0);
    this->setDataChar3(0);
}
