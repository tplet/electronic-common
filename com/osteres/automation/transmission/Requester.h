//
// Created by Thibault PLET on 06/05/2016.
//

#ifndef COM_OSTERES_AUTOMATION_TRANSMISSION_REQUESTER_H
#define COM_OSTERES_AUTOMATION_TRANSMISSION_REQUESTER_H

#include <com/osteres/automation/proxy/RF24.h>
#include <com/osteres/automation/transmission/packet/Packet.h>
#include <com/osteres/automation/transmission/Receiver.h>
#include <com/osteres/automation/transmission/Packing.h>

using com::osteres::automation::transmission::packet::Packet;
using com::osteres::automation::transmission::Packing;

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
                     * Send packet without checking success receiving
                     */
                    bool send(Packing * packing);

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
                    virtual void doSend(Packet * packet);

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
