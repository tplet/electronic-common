//
// Created by Thibault PLET on 28/05/2016.
//

#ifndef COM_OSTERES_AUTOMATION_MEMORY_VALUEBASE_H
#define COM_OSTERES_AUTOMATION_MEMORY_VALUEBASE_H


namespace com {
    namespace osteres {
        namespace automation {
            namespace memory {
                class ValueBase {
                protected:
                    /**
                     * Flag to indicate if value has changed
                     */
                    bool changed;

                    /**
                     * Address to where contained data in EEProm
                     */
                    int address;
                public:
                    /**
                     * Constructor
                     *
                     * @param int address Address to stored data in EEProm. Be sure that this address not already used!
                     */
                    ValueBase(int address) {
                        this->address = address;
                        this->changed = true; // Set to true to force first reading
                    }

                    /**
                     * Flag to indicate if value has been changed since last memory writing
                     */
                    bool isChanged() {
                        return this->changed;
                    }

                    /**
                     * Get address
                     */
                    int getAddress() {
                        return this->address;
                    }
                };
            }
        }
    }
}


#endif //COM_OSTERES_AUTOMATION_MEMORY_VALUEBASE_H
