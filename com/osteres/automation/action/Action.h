//
// Created by Thibault PLET on 06/05/2016.
//

#ifndef COM_OSTERES_AUTOMATION_ACTION_ACTION_H
#define COM_OSTERES_AUTOMATION_ACTION_ACTION_H


namespace com
{
    namespace osteres
    {
        namespace automation
        {
            namespace action
            {
                class Action
                {
                public:
                    /**
                     * Execute business action
                     */
                    virtual void execute();
                };
            }
        }
    }
}


#endif //COM_OSTERES_AUTOMATION_ACTION_ACTION_H
