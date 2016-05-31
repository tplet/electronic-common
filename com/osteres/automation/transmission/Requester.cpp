//
// Created by Thibault PLET on 06/05/2016.
//

#include "Requester.h"
#include <com/osteres/util/IDGenerator.h>
#include <com/osteres/automation/transmission/packet/Command.h>

using com::osteres::util::IDGenerator;
using com::osteres::automation::transmission::packet::Command;
using namespace com::osteres::automation::transmission;

/**
 * Constructor
 */
Requester::Requester(RF24 &radio) {
    this->radio = &radio;
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
 * RTC object setter
 */
Requester * Requester::setRTC(RTC_DS1307 &rtc) {
    this->rtc = &rtc;

    return this;
}

/**
 * Flag to indicate if can use RTC object
 */
bool Requester::useRTC() {
    return this->rtc != 0;
}

/**
 * Send packet and check if it has been successfully received (send by using RF24)
 */
bool Requester::send(Packet &packet, Receiver &receiver) {
    // Send
    this->doSend(packet);

    // Waiting for response
    this->success = this->doListenSuccessSent(packet, receiver);

    // Return success state
    return this->success;
}

/**
 * Send packet without checking success receiving
 */
bool Requester::send(Packet &packet) {
    // Send
    this->doSend(packet);

    return true;
}

/**
 * Prepare packet and send it only (no response attempted)
 */
void Requester::doSend(Packet &packet) {
    // Prepare uniq id
    packet.setId(IDGenerator::getNextId());
    // Datetime if possible
    // @TODO: Remove RTC, not responsability of requester to to that
    if (this->useRTC()) {
        packet.setDate(this->rtc->now().unixtime());
    }

    // Send
    this->radio->write(&packet, sizeof(packet));
}

/**
 * Waiting for success response
 */
bool Requester::doListenSuccessSent(Packet &packet, Receiver &receiver) {
    bool success = false;

    if (receiver.listen()) {
        // Checking response (command: OK, exclusively for packet id send)
        if (receiver.getResponse()->getCommand() == Command::OK &&
            receiver.getResponse()->getDataByte1() == packet.getId()) {
            success = true;
        }
    }

    return success;
}

/**
 * Flag to indicate if request has succeeded
 */
bool Requester::isSuccess() {
    return this->success;
}