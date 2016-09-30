//
// Created by Thibault PLET on 28/05/2016.
//

#ifndef COM_OSTERES_AUTOMATION_MEMORY_PROPERTY_H
#define COM_OSTERES_AUTOMATION_MEMORY_PROPERTY_H


namespace com
{
    namespace osteres
    {
        namespace automation
        {
            namespace memory
            {
                template<typename T>
                class Property {
                protected:
                    /**
                     * Value stored
                     */
                    T value;

                    /**
                     * Flag to indicate if value has been changed during last assignment
                     */
                    bool changed;
                public:
                    /**
                     * Constructor
                     */
                    Property()
                    {
                        this->changed = true;
                    }

                    /**
                     * Constructor
                     *
                     * @param T initValue Init value to affect on init
                     */
                    Property(T initValue)
                    {
                        this->set(initValue);
                        this->changed = true;
                    }

                    /**
                     * Set value
                     *
                     * @param T value Value to store
                     */
                    T set(T value)
                    {
                        if (this->value != value) {
                            this->changed = true;
                            this->value = value;
                        } else {
                            this->changed = false;
                        }

                        return this->value;
                    }

                    /**
                     * Get value
                     */
                    T get()
                    {
                        return this->value;
                    }

                    /**
                     * Flag to indicate if value has been changed during last assignment
                     */
                    bool isChanged()
                    {
                        return this->changed;
                    }

                };
            }
        }
    }
}


#endif //COM_OSTERES_AUTOMATION_MEMORY_PROPERTY_H
