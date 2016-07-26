//
// Created by Thibault PLET on 04/05/2016.
//

#ifndef COM_OSTERES_AUTOMATION_TRANSMISSION_TRANSMITTER_H
#define COM_OSTERES_AUTOMATION_TRANSMISSION_TRANSMITTER_H

#include <SPI.h>
#include <RF24.h>
#include "nRF24L01.h"
#include <com/osteres/automation/transmission/packet/Packet.h>
#include <com/osteres/automation/action/ActionManagerBase.h>
#include <com/osteres/automation/transmission/Requester.h>
#include <com/osteres/automation/transmission/Receiver.h>
#include <com/osteres/automation/transmission/packet/Command.h>

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
                    Transmitter(RF24 * radio, unsigned char sensor, bool isMaster = false);

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
                        //this->radio->enableDynamicPayloads();

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
                        Packet * packetOk = new Packet(this->sensor);
                        packetOk->setCommand(Command::OK);

                        Packet * response = NULL;
                        int i = 0;

                        bool last = false;
                        // Waiting for response
                        while (!last && this->getReceiver()->listen()) {
                            i++;

                            response = this->getReceiver()->getResponse();

                            // Send success receiving response
                            packetOk->setTarget(response->getSensor());
                            packetOk->setDataUChar1(response->getId());
                            packetOk->setDate(0);
                            this->getRequester()->send(packetOk);

                            // Processing
                            if (this->hasActionManager()) {
                                this->actionManager->processPacket(response);
                            }

                            // Check flag last. If true, waiting for another response
                            last = response->isLast();

                            // Clean receiver response (no need this instance anymore)
                            this->getReceiver()->cleanResponse();
                        }

                        Serial.print(F("Transmitter: Stop listening. "));
                        Serial.print(i);
                        Serial.println(F(" packet received and processed."));

                        // Free memory
                        if (packetOk != NULL) {
                            delete packetOk;
                            packetOk = NULL;
                        }
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
                    void setActionManager(ActionManagerBase * actionManager);

                    /**
                     * Check if action manager has been defined
                     */
                    bool hasActionManager()
                    {
                        return this->actionManager != NULL;
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
                    void setReadingChannel(unsigned long long channel)
                    {
                        this->readingChannel = channel;

                        if (this->receiver != NULL) {
                            this->receiver->setReadingChannel(this->readingChannel);
                        }
                    }

                    /**
                     * Set channel to write
                     */
                    void setWritingChannel(unsigned long long channel)
                    {
                        this->writingChannel = channel;

                        if (this->requester != NULL) {
                            this->requester->setWritingChannel(this->writingChannel);
                        }
                    }

                    /**
                     * Get writing channel
                     */
                    unsigned long long getWritingChannel()
                    {
                        return this->writingChannel;
                    }

                    /**
                     * Get reading channel
                     */
                    unsigned long long getReadingChannel()
                    {
                        return this->readingChannel;
                    }

                protected:
                    /**
                     * Constructor
                     */
                    void construct(RF24 * radio, unsigned char sensor, bool isMaster);

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
                    unsigned char sensor;

                    /**
                     * Master flag
                     * If false, slave mode
                     */
                    bool master;

                    /**
                     * Channel to read
                     */
                    unsigned long long readingChannel;

                    /**
                     * Channel to write
                     */
                    unsigned long long writingChannel;
                };
            }
        }
    }
}

#endif //COM_OSTERES_AUTOMATION_TRANSMISSION_TRANSMITTER_H
