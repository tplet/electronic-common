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
                    Transmitter(RF24 * radio, byte sensor, bool isMaster = false);

                    /**
                     * Destructor
                     */
                    ~Transmitter();

                    /**
                     * Setup transmitter
                     * Initialize radio associated
                     */
                    void setup()
                    {
                        // Init and configure radio transmitter
                        this->radio->begin();
                        this->radio->setAutoAck(true);
                        this->radio->setRetries(15, 15);
                        this->radio->enableDynamicPayloads();
                        this->radio->openWritingPipe(this->getWritingChannel());
                        this->radio->openReadingPipe(1, this->getReadingChannel());
                        this->radio->startListening(); // TODO: Remove ?

                        // Prepare requester and receiver
                        this->requester = new Requester(this->radio, this->getWritingChannel());
                        this->receiver = new Receiver(this->radio, this->getReadingChannel(), this->sensor, getDefaultTTL());

                        Serial.println(F("Transmitter: Setup done."));
                    }

                    /**
                     * Send packet
                     *
                     * Return success state (true if packet successfully transmitted and received, false otherwise)
                     */
                    bool send(Packet * packet)
                    {
                        // Send with requester and use receiver to check if successful transmitted
                        return this->getRequester()->send(packet, this->getReceiver());
                    }

                    /**
                     * Listen packets and if receive, forward to action manager for process
                     */
                    void listen()
                    {
                        Serial.println(F("Transmitter: Listen packet..."));

                        // Confirm packet
                        Packet * packet = new Packet(this->sensor);
                        packet->setCommand(Command::OK);

                        Packet * response = NULL;
                        int i = 0;

                        bool last = false;
                        // Waiting for response
                        while (this->getReceiver()->listen() && !last) {
                            i++;

                            response = this->getReceiver()->getResponse();

                            // Send success receiving response
                            packet->setTarget(response->getSensor());
                            packet->setDataByte1(response->getId());
                            packet->setDate(0);
                            this->getRequester()->send(packet);

                            // Processing
                            if (this->hasActionManager()) {
                                this->actionManager->processPacket(response);
                            }

                            // Check flag last. If true, waiting for another response
                            last = response->isLast();
                        }

                        Serial.println(String(F("Transmitter: Stop listening. ")) + String(i) + F(" packet received and processed."));

                        // Free memory
                        delete packet;
                        delete response;

                        // Clean response (no more used)
                        this->getReceiver()->cleanResponse();
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
                    Transmitter * setActionManager(ActionManagerBase * actionManager);

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

                    /**
                     * Master flag
                     */
                    bool isMaster()
                    {
                        return this->master;
                    }

                    /**
                     * Set channel to read
                     */
                    void setReadingChannel(uint64_t channel)
                    {
                        this->readingChannel = channel;

                        if (this->receiver != NULL) {
                            this->receiver->setReadingChannel(this->readingChannel);
                        }
                    }

                    /**
                     * Set channel to write
                     */
                    void setWritingChannel(uint64_t channel)
                    {
                        this->writingChannel = channel;

                        if (this->requester != NULL) {
                            this->requester->setWritingChannel(this->writingChannel);
                        }
                    }

                    /**
                     * Get writing channel
                     */
                    uint64_t getWritingChannel()
                    {
                        return this->writingChannel;
                    }

                    /**
                     * Get reading channel
                     */
                    uint64_t getReadingChannel()
                    {
                        return this->readingChannel;
                    }

                protected:
                    /**
                     * Constructor
                     */
                    void construct(RF24 * radio, byte sensor, bool isMaster);

                    /**
                     * Default ttl
                     */
                    static unsigned int defaultTtl;

                    /**
                     * Action manager to forward response received
                     */
                    ActionManagerBase * actionManager = NULL;

                    /**
                     * Requester object
                     */
                    Requester * requester = NULL;

                    /**
                     * Received object
                     */
                    Receiver * receiver = NULL;

                    /**
                     * Radio for transmission
                     */
                    RF24 * radio = NULL;

                    /**
                     * Sensor identifier
                     */
                    byte sensor;

                    /**
                     * Master flag
                     * If false, slave mode
                     */
                    bool master;

                    /**
                     * Channel to read
                     */
                    uint64_t readingChannel;

                    /**
                     * Channel to write
                     */
                    uint64_t writingChannel;
                };
            }
        }
    }
}

#endif //COM_OSTERES_AUTOMATION_TRANSMISSION_TRANSMITTER_H
