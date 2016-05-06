//
// Created by Thibault PLET on 04/05/2016.
//

#ifndef COM_OSTERES_AUTOMATION_TRANSMISSION_TRANSMITTER_H
#define COM_OSTERES_AUTOMATION_TRANSMISSION_TRANSMITTER_H

#include <com/osteres/automation/transmission/packet/Packet.h>

using com::osteres::automation::transmission::packet::Packet;

namespace com {
    namespace osteres {
        namespace automation {
            namespace transmission {
                class Transmitter {
                public:
                    /**
                     * Constructor
                     */
                    Transmitter();

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
                     */
                    void send(Packet &packet);

                    void listen();

                    /**
                     * Get default ttl before timeout (in seconds)
                     */
                    static unsigned int getDefaultTTL();

                    /**
                     * Set default ttl before timeout (in seconds)
                     */
                    static void setDefaultTTL(unsigned int ttl);

                protected:
                    static unsigned int defaultTtl;
                    /**
                     * Ttl before timeout (in seconds)
                     * Ttl = time to live
                     */
                    unsigned int ttl;
                };
            }
        }
    }
}

#endif //COM_OSTERES_AUTOMATION_TRANSMISSION_TRANSMITTER_H
