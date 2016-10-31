//
// Created by Thibault PLET on 31/10/2016.
//

#ifndef COM_OSTERES_AUTOMATION_TRANSMISSION_PACKING_H
#define COM_OSTERES_AUTOMATION_TRANSMISSION_PACKING_H

#include <com/osteres/automation/transmission/packet/Packet.h>

using com::osteres::automation::transmission::packet::Packet;

namespace com
{
    namespace osteres
    {
        namespace automation
        {
            namespace transmission
            {
                class Packing
                {
                public:
                    /**
                     * Constructor
                     */
                    Packing(Packet * packet)
                    {
                        this->setPacket(packet);
                        this->setConfirmDuration(Packing::defaultConfirmDuration);
                    }

                    /**
                     * Constructor
                     */
                    Packing(Packet * packet, bool withConfirm)
                    {
                        this->setPacket(packet);
                        this->setNeedConfirm(withConfirm);
                        this->setConfirmDuration(Packing::defaultConfirmDuration);
                    }

                    /**
                     * Destructor
                     */
                    ~Packing()
                    {
                        if (this->packet != NULL) {
                            delete this->packet;
                            this->packet = NULL;
                        }
                    }


                    /**
                     * Get packet
                     */
                    Packet * getPacket()
                    {
                        return this->packet;
                    }

                    /**
                     * Set packet
                     */
                    void setPacket(Packet * packet)
                    {
                        this->packet = packet;
                    }


                    /**
                     * Get date
                     */
                    unsigned long getDate()
                    {
                        return this->date;
                    }

                    /**
                     * Set date
                     */
                    void setDate(unsigned long date)
                    {
                        this->date = date;
                    }

                    /**
                     * Flag to indicate if packet has been successfully received
                     */
                    bool isConfirmed()
                    {
                        return this->confirmed;
                    }

                    /**
                     * Indicate if packet has been successfully received
                     */
                    void setConfirmed(bool flag)
                    {
                        this->confirmed = flag;
                    }

                    /**
                     * Flag to indicate if packet need to be confirmed by target
                     */
                    bool isNeedConfirm()
                    {
                        return this->needConfirm;
                    }

                    /**
                     * Indicate if packet need to be confirmed by target
                     */
                    void setNeedConfirm(bool flag)
                    {
                        this->needConfirm = flag;
                    }

                    /**
                     * Flag to indicate if waiting for confirm is outdated
                     */
                    virtual bool isConfirmOutdated(unsigned long now)
                    {
                        return now - this->getDate() > this->getConfirmDuration();
                    }

                    /**
                     * Get duration
                     */
                    unsigned long getConfirmDuration()
                    {
                        return this->confirmDuration;
                    }

                    /**
                     * Set duration
                     */
                    void setConfirmDuration(unsigned long duration)
                    {
                        this->confirmDuration = duration;
                    }

                    /**
                     * Flag to indicate if packet has been sended
                     */
                    bool isSended()
                    {
                        return this->sended;
                    }

                    /**
                     * Indicate if packet has been sended
                     */
                    void setSended(bool flag)
                    {
                        this->sended = flag;
                    }

                protected:

                    /**
                     * Default confirm duration
                     */
                    static unsigned long const defaultConfirmDuration = 3000;

                    /**
                     * Packet
                     */
                    Packet * packet = NULL;

                    /**
                     * Date sended/received
                     */
                    unsigned long date;

                    /**
                     * Flag to indicate if packet has been successfully received
                     */
                    bool confirmed;

                    /**
                     * Flag to indicate if packet has been sended
                     */
                    bool sended;

                    /**
                     * Flag to indicate if packet need to be confirmed by target
                     */
                    bool needConfirm;

                    /**
                     * Duration validity of packet when asking confirm (in ms)
                     */
                    unsigned long confirmDuration;

                };
            }
        }
    }
}

#endif //COM_OSTERES_AUTOMATION_TRANSMISSION_PACKING_H
