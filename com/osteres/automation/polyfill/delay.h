//
// Created by Thibault PLET on 18/08/2016.
//

#ifndef COM_OSTERES_AUTOMATION_POLYFILL_MILLIS_H
#define COM_OSTERES_AUTOMATION_POLYFILL_MILLIS_H

// Substitute for millis() method
#if (!defined(ARDUINO) && !defined(delay))

    #include <unistd.h>
    inline void delay( unsigned long ms )
    {
        usleep( ms * 1000 );
    }

#endif

#endif //COM_OSTERES_AUTOMATION_POLYFILL_MILLIS_H
