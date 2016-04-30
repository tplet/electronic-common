//
// Created by Thibault PLET on 30/04/2016.
//

#ifndef COM_OSTERES_AUTOMATION_SENSOR_HALL_READER_H
#define COM_OSTERES_AUTOMATION_SENSOR_HALL_READER_H


namespace com {
    namespace osteres {
        namespace automation {
            namespace sensor {
                namespace hall {
                    class Reader {
                    public:
                        /**
                         * Constructor with pin definition
                         */
                        Reader(uint8_t pin);

                        /**
                         * Constructor with pin and threshold definition
                         */
                        Reader(uint8_t pin, unsigned int threshold);

                        /**
                         * Set pin to read value
                         */
                        Reader setPin(uint8_t pin);

                        /**
                         * Get pin to read read value
                         */
                        uint8_t getPin();

                        /**
                         * Set threshold value
                         */
                        Reader setThreshold(unsigned int threshold);

                        /**
                         * Get threshold value
                         */
                        unsigned int getThreshold();

                        /**
                         * Set hall value
                         */
                        Reader setValue(unsigned int value);

                        /**
                         * Get hall value
                         */
                        unsigned int getValue();

                        /**
                         * Read value from pin
                         */
                        unsigned int readValue();

                        /**
                         * Is high state (stable state)
                         */
                        bool isHigh(bool refresh = false);

                        /**
                         * Is low state (event state)
                         */
                        bool isLow(bool refresh = false);

                        /**
                         * Get state
                         */
                        bool getState(bool refresh = false);

                        /**
                         * Flag to indicate if state has changed since last read
                         */
                        bool isStateChanged();

                        /**
                         * Default threshold value
                         */
                        static const unsigned int DEFAULT_THRESHOLD = 300;
                    protected:
                        /**
                         * Pin to read value
                         */
                        uint8_t pin;

                        /**
                         * Threshold when hall value is DOWN state
                         */
                        unsigned int threshold;

                        /**
                         * Current hall value
                         */
                        unsigned int value;

                        /**
                         * State (high or low)
                         * high: normal state
                         * low: event state
                         */
                        bool state;

                        /**
                         * Flag to indicate if state has changed since last read
                         */
                        bool stateChanged;

                        /**
                         * Update state value
                         */
                        bool updateState();

                    };
                }
            }
        }
    }
}

#endif //COM_OSTERES_AUTOMATION_SENSOR_HALL_READER_H
