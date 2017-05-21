//
// Created by Thibault PLET on 21/08/2016.
//

#ifndef COM_OSTERES_AUTOMATION_ACTION_IMPLEMENT_CONSOLEDISPLAYPACKET_H
#define COM_OSTERES_AUTOMATION_ACTION_IMPLEMENT_CONSOLEDISPLAYPACKET_H

#include <iostream>
#include <com/osteres/automation/action/Action.h>
#include <com/osteres/automation/transmission/packet/Packet.h>
#include <com/osteres/automation/transmission/packet/CommandString.h>
#include <inttypes.h>

using com::osteres::automation::action::Action;
using com::osteres::automation::transmission::packet::CommandString;
using com::osteres::automation::transmission::packet::Packet;

namespace com
{
    namespace osteres {
        namespace automation {
            namespace action {
                namespace implement {
                    class ConsoleDisplayPacket : public Action {
                    public:

                        /**
                         * Execute action
                         *
                         * Output packet to console
                         * (not works on arduino)
                         */
                        bool execute(Packet * packet, bool receive = true)
                        {
                            cout << endl;
                            cout << "Packet " << (receive ? "received" : "sended") << "! (size: " << sizeof(*packet) << ")" << endl;
                            cout << "-- Packet content --" << endl;
                            cout << "Id: " << (int)packet->getId() << " Last: " << (packet->isLast() ? "yes" : "no")
                            << " date: " << packet->getDate() << endl;
                            cout << "From type: " << (int)packet->getSourceType() << " id: " << (int)packet->getSourceIdentifier()
                            << " To: " << (int)packet->getTarget() << endl;
                            cout << "Command: " << CommandString::commandToString(packet->getCommand()) << endl;
                            cout << "UC1: " << (unsigned int)packet->getDataUChar1() << " UC2: " << (unsigned int)packet->getDataUChar2()
                            << " UC3: " << (unsigned int)packet->getDataUChar3() << endl;
                            cout << "L1: " << packet->getDataLong1() << " L2: " << packet->getDataLong2()
                            << "L3: " << packet->getDataLong3() << " L4: " << packet->getDataLong4() << endl;
                            cout << "C1: " << (int)packet->getDataChar1() << " C2: " << (int)packet->getDataChar2()
                            << "C3: " << (int)packet->getDataChar3() << endl;
                            cout << "-- End packet content --" << endl;

                            return true;
                        }

                    protected:
                    };
                }
            }
        }
    }
}

#endif //COM_OSTERES_AUTOMATION_ACTION_IMPLEMENT_CONSOLEDISPLAYPACKET_H
