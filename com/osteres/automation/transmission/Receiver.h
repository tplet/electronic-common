//
// Created by Thibault PLET on 06/05/2016.
//

#ifndef COM_OSTERES_AUTOMATION_TRANSMISSION_RECEIVER_H
#define COM_OSTERES_AUTOMATION_TRANSMISSION_RECEIVER_H

#include <Arduino.h>
#include <SPI.h>
#include <RF24/RF24.h>
#include <com/osteres/automation/transmission/packet/Packet.h>

using com::osteres::automation::transmission::packet::Packet;
typedef uint8_t byte;

namespace com
{
    namespace osteres
    {
        namespace automation
        {
            namespace transmission
            {
                class Receiver {
                public:
                    /**
                     * Constructor
                     */
                    Receiver(RF24 &radio, byte sensor, unsigned int timeout);

                    /**
                     * Destructor
                     */
                    ~Receiver();

                    /**
                     * Listen response for certain time
                     */
                    bool listen();

                    /**
                     * Get packet received
                     */
                    Packet getResponse();

                    /**
                     * Flag to indicate if response has been received
                     */
                    bool hasResponse();

                    /**
                     * Clean memory
                     */
                    void clean();
                protected:
                    /**
                     * Radio used for transmission
                     */
                    RF24 * radio;

                    /**
                     * Response packet
                     */
                    Packet * response;

                    /**
                     * Sensor target which can receive packet
                     */
                    byte sensor;

                    /**
                     * Timeout after this waiting for response has been stoped
                     */
                    unsigned int timeout;
                };
            }
        }
    }
}


#endif //COM_OSTERES_AUTOMATION_TRANSMISSION_RECEIVER_H
