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
Requester Requester::setRTC(RTC_DS1307 &rtc) {
    this->rtc = &rtc;

    return *this;
}

/**
 * Flag to indicate if can use RTC object
 */
bool Requester::useRTC() {
    return this->rtc != 0;
}

/**
 * Send packet by using RTC
 */
bool Requester::send(Packet &packet, Receiver &receiver) {
    // Init
    this->success = false;

    // Prepare uniq id
    packet.setId(IDGenerator::getNextId());
    // Datetime if possible
    if (this->useRTC()) {
        packet.setDate(this->rtc->now().unixtime());
    }

    // Send
    this->radio->write(&packet, sizeof(packet));

    // Waiting for response
    if (receiver.listen()) {
        // Checking response (command: OK, exclusively for packet id send)
        if (receiver.getResponse().getCommand() == Command::OK &&
            receiver.getResponse().getDataByte1() == packet.getId()) {
            this->success = true;
        }
    }

    // Return success state
    return this->success;
}

/**
 * Flag to indicate if request has succeeded
 */
bool Requester::isSuccess() {
    return this->success;
}