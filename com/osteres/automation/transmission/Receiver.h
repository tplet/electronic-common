//
// Created by Thibault PLET on 06/05/2016.
//

#ifndef COM_OSTERES_AUTOMATION_TRANSMISSION_RECEIVER_H
#define COM_OSTERES_AUTOMATION_TRANSMISSION_RECEIVER_H

#include <cstddef>
#include <com/osteres/automation/proxy/RF24.h>
#include <com/osteres/automation/transmission/packet/Packet.h>
#include <com/osteres/automation/memory/Property.h>

using com::osteres::automation::transmission::packet::Packet;
using com::osteres::automation::memory::Property;

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
                    Receiver(RF24 * radio, unsigned long long readingChannel, unsigned int timeout);

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
                    Packet * getResponse();

                    /**
                     * Flag to indicate if response has been received
                     */
                    bool hasResponse();

                    /**
                     * Clean response in memory
                     */
                    void cleanResponse();

                    /**
                     * Set timeout
                     */
                    void setTimeout(unsigned int timeout);

                    /**
                     * Get timeout
                     */
                    unsigned int getTimeout();

                    /**
                     * Set channel to read
                     */
                    void setReadingChannel(unsigned long long readingChannel);

                    /**
                     * Set sensor type identifier property
                     */
                    void setPropertySensorType(Property<unsigned char> * property);

                    /**
                     * Flag to indicate if sensor type identifier property has been defined
                     */
                    bool hasPropertySensorType();

                    /**
                     * Set sensor type property
                     */
                    void setPropertySensorIdentifier(Property<unsigned char> * property);

                    /**
                     * Flag to indicate if sensor identifier property has been defined
                     */
                    bool hasPropertySensorIdentifier();

                protected:
                    /**
                     * Radio used for transmission
                     */
                    RF24 * radio = NULL;

                    /**
                     * Response packet
                     */
                    Packet * response = NULL;

                    /**
                     * Sensor type identifier property
                     */
                    Property<unsigned char> * propertySensorType = NULL;

                    /**
                     * Sensor identifier property
                     */
                    Property<unsigned char> * propertySensorIdentifier = NULL;

                    /**
                     * Timeout after this waiting for response has been stoped
                     */
                    unsigned int timeout;

                    /**
                     * Channel to read
                     */
                    unsigned long long readingChannel;
                };
            }
        }
    }
}


#endif //COM_OSTERES_AUTOMATION_TRANSMISSION_RECEIVER_H
