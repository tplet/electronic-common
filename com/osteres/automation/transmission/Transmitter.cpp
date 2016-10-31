//
// Created by Thibault PLET on 04/05/2016.
//

#include "Transmitter.h"

using namespace com::osteres::automation::transmission;

/**
 * Default ttl (in milliseconds)
 */
unsigned int Transmitter::defaultTtl = 1000;

/**
 * Max packet allowed in queue
 */
unsigned int Transmitter::maxPacketQueue = 10;

/**
 * Constructor
 */
Transmitter::Transmitter(RF24 * radio, bool isMaster)
{
    Transmitter::construct(radio, isMaster);
}

/**
 * Destructor
 */
Transmitter::~Transmitter()
{
    // Remove requester and receiver
    if (this->requester != NULL) {
        delete this->requester;
        this->requester = NULL;
    }
    if (this->receiver != NULL) {
        delete this->receiver;
        this->receiver = NULL;
    }

    // Remove queue
    if (this->queue != NULL) {
        delete this->queue;
        this->queue = NULL;
    }
    if (this->queueSended != NULL) {
        delete this->queueSended;
        this->queueSended = NULL;
    }
}

/**
 * Constructor
 */
void Transmitter::construct(RF24 * radio, bool isMaster)
{
    this->radio = radio;
    this->master = isMaster;

    // Channels
    unsigned long long writingChannel = Command::CHANNEL_SLAVE;
    unsigned long long readingChannel = Command::CHANNEL_MASTER;
    if (this->isMaster()) {
        writingChannel = Command::CHANNEL_MASTER;
        readingChannel = Command::CHANNEL_SLAVE;
    }
    this->setReadingChannel(readingChannel);
    this->setWritingChannel(writingChannel);

    // Queue
    this->queue = new std::queue<Packing *>();
    this->queueSended= new std::queue<Packing *>();
}

/**
 * Init step
 */
void Transmitter::stepInit()
{
    Packing * packing = NULL;

    // Move sended queue to normal queue (= resend packet!)
    while (!this->getQueueSended()->empty()) {
        packing = this->getQueueSended()->front();
        this->getQueueSended()->pop();
        this->getQueue()->push(packing);
    }
}

/**
 * Send step
 */
void Transmitter::stepSend()
{
    Packing * packing = NULL;

    // For each packing in queue
    while (!this->getQueue()->empty()) {
        // Set last property
        packing = this->getQueue()->front();
        this->getQueue()->pop();
        packing->getPacket()->setLast(this->getQueue()->empty());

        // Send
        this->send(packing);

        // If confirm asked, move to other queue
        if (packing->isNeedConfirm()) {
            this->getQueueSended()->push(packing);
        } else {
            // Free memory
            delete packing;
            packing = NULL;
        }
    }
}

/**
 * Receive step
 */
void Transmitter::stepReceive(unsigned int timeout)
{
    this->listen(timeout);
}

/**
 * Receive step
 */
void Transmitter::stepReceive()
{
    this->listen(this->getReceiver()->getTimeout());
}

/**
 * Add packing directly to queue
 */
void Transmitter::add(Packing * packing)
{
    this->getQueue()->push(packing);
}

/**
 * Add packet to queue
 */
void Transmitter::add(Packet * packet, bool withConfirm)
{
    Packing * packing = new Packing(packet, withConfirm);

    this->getQueue()->push(packing);
}

/**
 * Add packet to queue (without confirm)
 */
void Transmitter::add(Packet * packet)
{
    this->add(packet, false);
}

/**
 * Listen packets and if receive, forward to action manager for process
 * and set timeout time to receive packet in millisecond
 *
 * @return bool True if packet received during listen process
 */
bool Transmitter::listen(unsigned int timeout)
{
    //Serial.println(F("Transmitter: Listen packet..."));

    // Confirm packet
    Packet * packetOk = NULL;

    Packet * response = NULL;
    int i = 0;

    bool last = false;
    // Waiting for response
    while (!last && this->getReceiver()->listen(timeout)) {
        i++;

        response = this->getReceiver()->getResponse();

        // Prepare success receiving response (not send yet)
        packetOk = this->generatePacketOK();
        packetOk->setTarget(response->getSourceIdentifier());
        packetOk->setDataUChar1(response->getId());
        packetOk->setDate(0);
        this->add(packetOk);

        // Confirm packet in sended queue
        this->confirm(response);

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

    // Clean response (no more used)
    this->getReceiver()->cleanResponse();

    return i > 0;
}

/**
 * Confirm packet if possible
 */
void Transmitter::confirm(Packet * response)
{
    if (response->getCommand() == Command::OK) {
        Packing *packing = NULL;
        // Search packet in sended queue
        unsigned int size = this->getQueueSended()->size();
        for (int i = 0; i < size; i++) {
            packing = this->getQueueSended()->front();
            this->getQueueSended()->pop();

            // Remove packing if id match (confirmed)
            if (packing->isNeedConfirm() && packing->getPacket()->getId() == response->getDataUChar1()) {
                packing->setConfirmed(true);
                delete packing;
                packing = NULL;
            } // Else, append packing to sended queue
            else {
                this->getQueueSended()->push(packing);
            }
        }
    }
}

/**
 * Generate OK packet for confirm response
 */
Packet * Transmitter::generatePacketOK()
{
    Packet *packet = new Packet();
    packet->setCommand(Command::OK);

    if (this->hasPropertySensorIdentifier()) {
        packet->setSourceIdentifier(this->propertySensorIdentifier->get());
    }
    if (this->hasPropertySensorType()) {
        packet->setSourceType(this->propertySensorType->get());
    }

    return packet;
}

/**
 * Send packet without checking for response confirmation
 */
bool Transmitter::send(Packing * packing)
{
    return this->getRequester()->send(packing);
}

/**
 * Get default ttl before timeout (in seconds)
 */
unsigned int Transmitter::getDefaultTTL()
{
    return defaultTtl;
}

/**
 * Set default ttl before timeout (in seconds)
 */
void Transmitter::setDefaultTTL(unsigned int ttl)
{
    defaultTtl = ttl;
}

/**
 * Get max packet allowed in queue
 */
unsigned int Transmitter::getMaxPacketQueue()
{
    return maxPacketQueue;
}

/**
 * Set max packet allowed in queue
 */
void Transmitter::setMaxPacketQueue(unsigned int max)
{
    maxPacketQueue = max;
}

/**
 * Action manager setter
 */
void Transmitter::setActionManager(ActionManagerBase * actionManager) {
    this->actionManager = actionManager;
}

/**
 * Get requester
 * Initialize it if necessary
 */
Requester * Transmitter::getRequester() {
    return this->requester;
}

/**
 * Get receiver
 * Initialize if if necessary
 */
Receiver * Transmitter::getReceiver() {
    return this->receiver;
}

/**
 * Flag to indicate if receiver is defined
 */
bool Transmitter::hasReceiver()
{
    return this->receiver != NULL;
}

/**
 * Set requester
 */
void Transmitter::setRequester(Requester * requester)
{
    this->requester = requester;
}

/**
 * Set receiver
 */
void Transmitter::setReceiver(Receiver * receiver)
{
    this->receiver = receiver;

    // Apply properties if available
    if (this->hasPropertySensorType()) {
        this->receiver->setPropertySensorType(this->propertySensorType);
    }
    if (this->hasPropertySensorIdentifier()) {
        this->receiver->setPropertySensorIdentifier(this->propertySensorIdentifier);
    }
}
