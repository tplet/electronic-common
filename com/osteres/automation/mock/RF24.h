//
// Created by Thibault PLET on 18/08/2016.
//

#ifndef COM_OSTERES_AUTOMATION_MOCK_RF24_H
#define COM_OSTERES_AUTOMATION_MOCK_RF24_H

namespace com {
    namespace osteres {
        namespace automation {
            namespace mock {
                class RF24 {
                public:
                    /**
                     * Constructor
                     */
                    RF24(unsigned char cepin, unsigned char csnpin)
                    {
                        // Nothing to do
                    }

                    /**
                     * Begin operation of the chip
                     */
                    bool begin()
                    {
                        return true;
                    }

                    /**
                     * Start listening on the pipes opened for reading
                     */
                    void startListening()
                    {
                        // Nothing to do
                    }

                    /**
                     * Stop listening for incoming messages, and switch to transmit mode.
                     */
                    void stopListening()
                    {
                        // Nothing to do
                    }

                    /**
                     * Check whether there are bytes available to be read
                     */
                    bool available()
                    {
                        return false;
                    }

                    /**
                     * Test whether there are bytes available to be read in the
                     * FIFO buffers
                     */
                    bool available(unsigned char * pipe_num)
                    {
                        return false;
                    }

                    /**
                     * Read the available payload
                     */
                    void read(void* buf, unsigned char len)
                    {
                        // Nothing to do
                    }

                    /**
                     * Write
                     */
                    bool write(const void* buf, unsigned char len)
                    {
                        return true;
                    }

                    /**
                     * Open a pipe for writing via byte array
                     */
                    void openWritingPipe(const unsigned char * address)
                    {
                        // Nothing to do
                    }

                    /**
                     * Open a pipe for writing via byte array
                     */
                    void openWritingPipe(unsigned long long address)
                    {
                        // Nothing to do
                    }

                    /**
                     * Open a pipe for reading
                     */
                    void openReadingPipe(unsigned char number, unsigned long long address)
                    {
                        // Nothing to do
                    }

                    /**
                     * Open a pipe for reading
                     */
                    void openReadingPipe(unsigned char number, const unsigned char * address)
                    {
                        // Nothing to do
                    }

                    /**
                     * Enable or disable auto-acknowledge packets
                     */
                    void setAutoAck(bool enable)
                    {
                        // Nothing to do
                    }

                    /**
                     * Enable or disable auto-acknowledge packets on a per pipeline basis
                     */
                    void setAutoAck(unsigned char pipe, bool enable)
                    {
                        // Nothing to do
                    }

                    /**
                     * Set the number and delay of retries upon failed submit
                     */
                    void setRetries(unsigned char delay, unsigned char count)
                    {
                        // Nothing to do
                    }

                    /**
                     * Enable dynamically-sized payloads
                     */
                    void enableDynamicPayloads()
                    {
                        // Nothing to do
                    }

                protected:

                };
            }
        }
    }
}


#endif //COM_OSTERES_AUTOMATION_MOCK_RF24_H
