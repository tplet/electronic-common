//
// Created by Thibault PLET on 06/05/2016.
//

#include "Requester.h"
#include <com/osteres/util/IDGenerator.h>
#include <com/osteres/automation/transmission/packet/Command.h>
#include <com/osteres/automation/polyfill/delay.h>
#include <iostream>
#include <inttypes.h>

using namespace std;
using com::osteres::util::IDGenerator;
using com::osteres::automation::transmission::packet::Command;
using namespace com::osteres::automation::transmission;

/**
 * Constructor
 */
Requester::Requester(RF24 * radio, unsigned long long writingChannel) {
    this->radio = radio;
    this->setWritingChannel(writingChannel);
}

/**
 * Destructor
 */
Requester::~Requester() {
    this->clean();
}

/**
 * Clean data memory
 */
void Requester::clean() {
}

/**
 * Send packet without checking success receiving
 */
bool Requester::send(Packing * packing)
{
    cout << "Requester: send" << endl;
    // Send
    this->doSend(packing->getPacket());

    this->success = true;

    return true;
}

/**
 * Prepare packet and send it only (no response attempted)
 */
void Requester::doSend(Packet * packet)
{
    // Prepare unique id
    packet->setId(IDGenerator::getNextId());

    // Ensure that radio not currently listening
    this->radio->stopListening();

    // Writing channel
    this->radio->openWritingPipe(this->writingChannel);

    // Send
    this->radio->write(packet, sizeof(Packet));
    delay(10);
}

/**
 * Flag to indicate if request has succeeded
 */
bool Requester::isSuccess() {
    return this->success;
}

/**
 * Set channel to write
 */
void Requester::setWritingChannel(unsigned long long writingChannel)
{
    this->writingChannel = writingChannel;
}