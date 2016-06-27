//
// Created by Thibault PLET on 06/05/2016.
//

#ifndef COM_OSTERES_AUTOMATION_TRANSMISSION_REQUESTER_H
#define COM_OSTERES_AUTOMATION_TRANSMISSION_REQUESTER_H

#include <SPI.h>
#include <RF24/RF24.h>
#include <RTClib/RTClib.h>
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
                    Requester(RF24 * radio, uint64_t writingChannel);

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
                     * Set RTC object
                     */
                    Requester * setRTC(RTC_DS1307 * rtc);

                    /**
                     * Flag to indicate if can use rtc
                     */
                    bool useRTC();

                    /**
                     * Flag to indicate if request has succeeded
                     */
                    bool isSuccess();

                    /**
                     * Set channel to write
                     */
                    void setWritingChannel(uint64_t writingChannel);

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
                     * RTC object (optional)
                     */
                    RTC_DS1307 * rtc = NULL;

                    /**
                     * Flag to indicate if request has succeeded
                     */
                    bool success;

                    /**
                     * Channel to write
                     */
                    uint64_t writingChannel;
                };

            }
        }
    }
}

#endif //COM_OSTERES_AUTOMATION_TRANSMISSION_REQUESTER_H
