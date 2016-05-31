//
// Created by Thibault PLET on 04/05/2016.
//

#ifndef COM_OSTERES_AUTOMATION_TRANSMISSION_TRANSMITTER_H
#define COM_OSTERES_AUTOMATION_TRANSMISSION_TRANSMITTER_H

#include <Arduino.h>
#include "RF24/nRF24L01.h"
#include <SPI.h>
#include <RF24/RF24.h>
#include <com/osteres/automation/transmission/packet/Packet.h>
#include <com/osteres/automation/action/ActionManagerBase.h>
#include <com/osteres/automation/transmission/Requester.h>
#include <com/osteres/automation/transmission/Receiver.h>
#include <com/osteres/automation/transmission/packet/Command.h>

typedef uint8_t byte;

using com::osteres::automation::transmission::packet::Packet;
using com::osteres::automation::action::ActionManagerBase;
using com::osteres::automation::transmission::Requester;
using com::osteres::automation::transmission::Receiver;
using com::osteres::automation::transmission::packet::Command;

namespace com {
    namespace osteres {
        namespace automation {
            namespace transmission {
                class Transmitter {
                public:
                    /**
                     * Constructor
                     */
                    Transmitter(RF24 &radio, byte sensor);

                    /**
                     * Get ttl before timeout (in seconds)
                     */
                    unsigned int getTTL();

                    /**
                     * Set ttl before timeout (in seconds)
                     */
                    void setTTL(unsigned int ttl);

                    /**
                     * Restore to default ttl defined (in seconds)
                     */
                    void useDefaultTTL();

                    /**
                     * Send packet
                     *
                     * Return success state (true if packet successfully transmitted and received, false otherwise)
                     */
                    bool send(Packet &packet)
                    {
                        // Send with requester and use receiver to check if successfull transmited
                        return this->getRequester()->send(packet, *this->getReceiver());
                    }

                    /**
                     * Listen packets and if receive, forward to action manager for process
                     */
                    void listen()
                    {
                        // Confirm packet
                        Packet packet;
                        packet.setSensor(this->sensor);
                        packet.setCommand(Command::OK);

                        Packet * response;

                        bool last = false;
                        // Waiting for response
                        while (this->getReceiver()->listen() && !last) {

                            response = this->getReceiver()->getResponse();

                            // Send success receiving response
                            packet.setTarget(response->getSensor());
                            packet.setDataByte1(response->getId());
                            this->getRequester()->send(packet);

                            // Processing
                            if (this->hasActionManager()) {
                                this->actionManager->processPacket(*response);
                            }

                            // Check flag last. If true, waiting for another response
                            last = response->isLast();
                        }

                        // Free memory
                        free(&packet);
                    }

                    /**
                     * Get default ttl before timeout (in seconds)
                     */
                    static unsigned int getDefaultTTL();

                    /**
                     * Set default ttl before timeout (in seconds)
                     */
                    static void setDefaultTTL(unsigned int ttl);

                    /**
                     * Action manager setter
                     */
                    Transmitter * setActionManager(ActionManagerBase &actionManager);

                    /**
                     * Check if action manager has been defined
                     */
                    bool hasActionManager()
                    {
                        return this->actionManager != 0;
                    }

                    /**
                     * Get requester object
                     */
                    Requester * getRequester();

                    /**
                     * Get receiver object
                     */
                    Receiver * getReceiver();

                    /**
                     * Get RF24 (radio)
                     */
                    RF24 * getRadio()
                    {
                        return this->radio;
                    }

                protected:
                    static unsigned int defaultTtl;
                    /**
                     * Ttl before timeout (in seconds)
                     * Ttl = time to live
                     */
                    unsigned int ttl;

                    /**
                     * Action manager to forward response received
                     */
                    ActionManagerBase * actionManager;

                    /**
                     * Requester object
                     */
                    Requester * requester;

                    /**
                     * Received object
                     */
                    Receiver * receiver;

                    /**
                     * Radio for transmission
                     */
                    RF24 * radio;

                    /**
                     * Sensor identifier
                     */
                    byte sensor;
                };
            }
        }
    }
}

#endif //COM_OSTERES_AUTOMATION_TRANSMISSION_TRANSMITTER_H
