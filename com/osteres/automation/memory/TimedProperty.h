//
// Created by Thibault PLET on 04/10/2016.
//

#ifndef COM_OSTERES_AUTOMATION_MEMORY_TIMEDPROPERTY_H
#define COM_OSTERES_AUTOMATION_MEMORY_TIMEDPROPERTY_H

#include <com/osteres/automation/memory/Property.h>

using com::osteres::automation::memory::Property;

namespace com
{
    namespace osteres
    {
        namespace automation
        {
            namespace memory
            {
                template<typename T>
                class TimedProperty : public Property<T>
                {
                public:
                    /**
                     * Constructor
                     */
                    TimedProperty(unsigned long duration) : Property<T>()
                    {
                        this->setDuration(duration);
                    }

                    /**
                     * Constructor
                     */
                    TimedProperty(unsigned long duration, T initValue) : Property<T>(initValue)
                    {
                        this->setDuration(duration);
                    }

                    /**
                     * Flag to indicate if property is outdated
                     */
                    virtual bool isOutdated()
                    {
                        return false;
                    }

                    /**
                     * Get duration
                     */
                    unsigned long getDuration()
                    {
                        return this->duration;
                    }

                    /**
                     * Set duration
                     */
                    void setDuration(unsigned long duration)
                    {
                        this->duration = duration;
                    }

                protected:
                    /**
                     * Duration validity of property
                     */
                    unsigned long duration;
                };
            }
        }
    }
}

#endif //COM_OSTERES_AUTOMATION_MEMORY_TIMEDPROPERTY_H
