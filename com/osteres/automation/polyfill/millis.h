//
// Created by Thibault PLET on 18/08/2016.
//

#ifndef COM_OSTERES_AUTOMATION_POLYFILL_MILLIS_H
#define COM_OSTERES_AUTOMATION_POLYFILL_MILLIS_H

// Substitute for millis() method
#if (!defined(ARDUINO) && !defined(millis))

    #include <ctime>
    unsigned long millis()
    {
        return clock() / (double)CLOCKS_PER_SEC * 1000;
    }

#endif

#endif //COM_OSTERES_AUTOMATION_POLYFILL_MILLIS_H
