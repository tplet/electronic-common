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
                     * Constructor
                     */
                    Action()
                    {
                        this->success = false;
                        this->executed = false;
                    }

                    /**
                     * Execute business action
                     * Return success state
                     */
                    virtual bool execute() {
                        this->executed = true;

                        return true;
                    }

                    /**
                     * Get success state
                     */
                    bool isSuccess()
                    {
                        return this->success;
                    }

                    /**
                     * Declare action as successfully executed
                     */
                    void setSuccess()
                    {
                        this->success = true;
                    }

                    /**
                     * Declare action as not successfully executed
                     */
                    void setError()
                    {
                        this->success = false;
                    }

                    /**
                     * Get executed flag
                     */
                    bool isExecuted()
                    {
                        return this->executed;
                    }

                protected:
                    /**
                     * Success flag
                     */
                    bool success;

                    /**
                     * Execution flag
                     */
                    bool executed;
                };
            }
        }
    }
}


#endif //COM_OSTERES_AUTOMATION_ACTION_ACTION_H
