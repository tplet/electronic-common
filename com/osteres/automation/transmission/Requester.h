//
// Created by Thibault PLET on 06/05/2016.
//

#ifndef COM_OSTERES_AUTOMATION_TRANSMISSION_REQUESTER_H
#define COM_OSTERES_AUTOMATION_TRANSMISSION_REQUESTER_H

#include <RF24.h>
#include <com/osteres/automation/transmission/packet/Packet.h>
#include <com/osteres/automation/transmission/Receiver.h>

using com::osteres::automation::transmission::packet::Packet;

namespace com
{
    namespace osteres
    {
        namespace automation
        {
            namespace transmission
            {
                class Requester {
                public:
                    /**
                     * Constructor
                     */
                    Requester(RF24 * radio, unsigned long long writingChannel);

                    /**
                     * Destructor
                     */
                    ~Requester();

                    /**
                     * Clean data memory
                     */
                    void clean();

                    /**
                     * Send packet and check if it has been successfully received
                     */
                    bool send(Packet * packet, Receiver * receiver);

                    /**
                     * Send packet without checking success receiving
                     */
                    bool send(Packet * packet);

                    /**
                     * Flag to indicate if request has succeeded
                     */
                    bool isSuccess();

                    /**
                     * Set channel to write
                     */
                    void setWritingChannel(unsigned long long writingChannel);

                protected:
                    /**
                     * Prepare packet and send it only (no response attempted)
                     */
                    void doSend(Packet * packet);

                    /**
                     * Waiting for success response
                     */
                    bool doListenSuccessSent(Packet * packet, Receiver * receiver);

                    /**
                     * Radio transmitter
                     */
                    RF24 * radio = NULL;

                    /**
                     * Flag to indicate if request has succeeded
                     */
                    bool success;

                    /**
                     * Channel to write
                     */
                    unsigned long long writingChannel;
                };

            }
        }
    }
}

#endif //COM_OSTERES_AUTOMATION_TRANSMISSION_REQUESTER_H
