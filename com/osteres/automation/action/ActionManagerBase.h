//
// Created by Thibault PLET on 06/05/2016.
//

#ifndef COM_OSTERES_AUTOMATION_ACTION_ACTIONMANAGERBASE_H
#define COM_OSTERES_AUTOMATION_ACTION_ACTIONMANAGERBASE_H

#include <com/osteres/automation/transmission/packet/Packet.h>

using com::osteres::automation::transmission::packet::Packet;

namespace com
{
    namespace osteres
    {
        namespace automation
        {
            namespace action
            {
                class ActionManagerBase
                {
                public:
                    /**
                     * Process packet
                     * Execute right action associated to this packet
                     */
                    virtual void processPacket(Packet * packet) = 0;
                };
            }
        }
    }
}

#endif //COM_OSTERES_AUTOMATION_ACTION_ACTIONMANAGERBASE_H
