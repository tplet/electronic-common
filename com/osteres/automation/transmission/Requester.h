//
// Created by Thibault PLET on 06/05/2016.
//

#ifndef COM_OSTERES_AUTOMATION_TRANSMISSION_REQUESTER_H
#define COM_OSTERES_AUTOMATION_TRANSMISSION_REQUESTER_H

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
                    Requester(RF24 &radio);

                    /**
                     * Destructor
                     */
                    ~Requester();

                    /**
                     * Clean data memory
                     */
                    void clean();

                    /**
                     * Send packet
                     */
                    bool send(Packet &packet, Receiver &receiver);

                    /**
                     * Set RTC object
                     */
                    Requester setRTC(RTC_DS1307 &rtc);

                    /**
                     * Flag to indicate if can use rtc
                     */
                    bool useRTC();

                    /**
                     * Flag to indicate if request has succeeded
                     */
                    bool isSuccess();

                protected:
                    /**
                     * Radio transmitter
                     */
                    RF24 * radio;

                    /**
                     * RTC object (optional)
                     */
                    RTC_DS1307 * rtc;

                    /**
                     * Flag to indicate if request has succeeded
                     */
                    bool success;
                };

            }
        }
    }
}

#endif //COM_OSTERES_AUTOMATION_TRANSMISSION_REQUESTER_H
