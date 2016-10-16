//
// Created by Thibault PLET on 04/05/2016.
//

#ifndef COM_OSTERES_AUTOMATION_TRANSMISSION_TRANSMITTER_H
#define COM_OSTERES_AUTOMATION_TRANSMISSION_TRANSMITTER_H

#include <cstddef>
#include <com/osteres/automation/proxy/RF24.h>
#include <com/osteres/automation/transmission/packet/Packet.h>
#include <com/osteres/automation/action/ActionManagerBase.h>
#include <com/osteres/automation/transmission/Requester.h>
#include <com/osteres/automation/transmission/Receiver.h>
#include <com/osteres/automation/transmission/packet/Command.h>
#include <com/osteres/automation/memory/Property.h>

using com::osteres::automation::transmission::packet::Packet;
using com::osteres::automation::action::ActionManagerBase;
using com::osteres::automation::transmission::Requester;
using com::osteres::automation::transmission::Receiver;
using com::osteres::automation::transmission::packet::Command;
using com::osteres::automation::memory::Property;

namespace com
{
    namespace osteres
    {
        namespace automation
        {
            namespace transmission
            {
                class Transmitter {
                public:
                    /**
                     * Constructor
                     */
                    Transmitter(RF24 * radio, bool isMaster = false);

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
                        if (this->requester == NULL) {
                            this->requester = new Requester(this->radio, this->getWritingChannel());
                        }
                        if (this->receiver == NULL) {
                            this->receiver = new Receiver(this->radio, this->getReadingChannel(), getDefaultTTL());
                            if (this->hasPropertySensorType()) {
                                this->receiver->setPropertySensorType(this->propertySensorType);
                            }
                            if (this->hasPropertySensorIdentifier()) {
                                this->receiver->setPropertySensorIdentifier(this->propertySensorIdentifier);
                            }
                        }

                        //Serial.println(F("Transmitter: Setup done."));
                    }

                    /**
                     * Send packet without checking for response confirmation
                     */
                    bool send(Packet * packet)
                    {
                        return this->getRequester()->send(packet);
                    }

                    /**
                     * Send packet
                     *
                     * Return success state (true if packet successfully transmitted and received, false otherwise)
                     */
                    bool sendAndConfirm(Packet * packet)
                    {
                        // Send with requester and use receiver to check if successful transmitted
                        return this->getRequester()->send(packet, this->getReceiver());
                    }

                    /**
                     * Listen packets and if receive, forward to action manager for process
                     *
                     * @return bool True if packer received during listen process
                     */
                    bool listen()
                    {
                        return this->listen(this->getReceiver()->getTimeout());
                    }

                    /**
                     * Listen packets and if receive, forward to action manager for process
                     * and set timeout time to receive packet in millisecond
                     *
                     * @return bool True if packet received during listen process
                     */
                    bool listen(unsigned int timeout)
                    {
                        //Serial.println(F("Transmitter: Listen packet..."));

                        // Confirm packet
                        Packet * packetOk = new Packet();
                        packetOk->setCommand(Command::OK);
                        if (this->hasPropertySensorIdentifier()) {
                            packetOk->setSourceIdentifier(this->propertySensorIdentifier->get());
                        }
                        if (this->hasPropertySensorType()) {
                            packetOk->setSourceType(this->propertySensorType->get());
                        }

                        Packet * response = NULL;
                        int i = 0;

                        bool last = false;
                        // Waiting for response
                        while (!last && this->getReceiver()->listen(timeout)) {
                            i++;

                            response = this->getReceiver()->getResponse();

                            // Send success receiving response
                            packetOk->setTarget(response->getSourceIdentifier());
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

                        //Serial.print(F("Transmitter: Stop listening. "));
                        //Serial.print(i);
                        //Serial.println(F(" packet received and processed."));

                        // Free memory
                        if (packetOk != NULL) {
                            delete packetOk;
                            packetOk = NULL;
                        }
                        // Clean response (no more used)
                        this->getReceiver()->cleanResponse();

                        return i > 0;
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
                     * Flag to indicate if receiver defined
                     */
                    bool hasReceiver();

                    /**
                     * Set requester object
                     *
                     * When you use this method, ensure that previous requester pointer has been removed!
                     */
                    void setRequester(Requester * requester);

                    /**
                     * Set receiver object
                     *
                     * When you use this method, ensure that previous requester pointer has been removed!
                     */
                    void setReceiver(Receiver * receiver);

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

                    /**
                     * Set sensor type identifier property
                     */
                    void setPropertySensorType(Property<unsigned char> * property)
                    {
                        this->propertySensorType = property;

                        // Forward to receiver if defined
                        if (this->hasReceiver()) {
                            this->getReceiver()->setPropertySensorType(this->propertySensorType);
                        }
                    }

                    /**
                     * Set sensor identifier property
                     */
                    void setPropertySensorIdentifier(Property<unsigned char> * property)
                    {
                        this->propertySensorIdentifier = property;

                        // Forward to receiver if defined
                        if (this->hasReceiver()) {
                            this->getReceiver()->setPropertySensorIdentifier(this->propertySensorIdentifier);
                        }
                    }

                    /**
                     * Flag to indicate if sensor type identifier property is defined
                     */
                    bool hasPropertySensorType()
                    {
                        return this->propertySensorType != NULL;
                    }

                    /**
                     * Flag to indicate if sensor identifier property is defined
                     */
                    bool hasPropertySensorIdentifier()
                    {
                        return this->propertySensorIdentifier != NULL;
                    }

                protected:
                    /**
                     * Constructor
                     */
                    void construct(RF24 * radio, bool isMaster);

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
                     * Sensor type identifier property
                     */
                    Property<unsigned char> * propertySensorType = NULL;

                    /**
                     * Sensor identifier property
                     */
                    Property<unsigned char> * propertySensorIdentifier = NULL;

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
