//
// Created by Thibault PLET on 02/10/2016.
//

#ifndef COM_OSTERES_AUTOMATION_ACTION_IMPLEMENT_RESPONSEOKACTION_H
#define COM_OSTERES_AUTOMATION_ACTION_IMPLEMENT_RESPONSEOKACTION_H

#include <com/osteres/automation/action/Action.h>
#include <com/osteres/automation/transmission/packet/Packet.h>
#include <com/osteres/automation/transmission/Transmitter.h>
#include <com/osteres/automation/transmission/packet/Command.h>

using com::osteres::automation::action::Action;
using com::osteres::automation::transmission::packet::Packet;
using com::osteres::automation::transmission::Transmitter;
using com::osteres::automation::transmission::packet::Command;


namespace com {
    namespace osteres {
        namespace automation {
            namespace action {
                namespace implement {
                    namespace packet {
                        class ResponseOkAction : public Action {
                        public:

                            /**
                             * Constructor
                             */
                            ResponseOkAction(Transmitter *transmitter) : Action() {
                                this->transmitter = transmitter;
                            }

                            /**
                             * Execute action
                             *
                             * Save packet to database
                             */
                            bool execute(Packet *packet, unsigned char type) {
                                // Send OK packet containing id of packet source
                                Packet *p = new Packet();
                                p->setTarget(packet->getSourceIdentifier());
                                p->setSourceType(type);
                                p->setSourceIdentifier(packet->getTarget());
                                p->setCommand(Command::OK);
                                p->setDataUChar1(packet->getId());
                                p->setLast(true);
                                this->transmitter->send(p);

                                // Free memory
                                delete p;

                                this->executed = true;
                                return true;
                            }

                        protected:

                            /**
                             * Transmitter
                             */
                            Transmitter *transmitter = NULL;
                        };
                    }
                }
            }
        }
    }
}

#endif //COM_OSTERES_AUTOMATION_ACTION_IMPLEMENT_RESPONSEOKACTION_H
