//
// Created by Thibault PLET on 18/08/2016.
//

#ifndef COM_OSTERES_AUTOMATION_PROXY_RF24_H
#define COM_OSTERES_AUTOMATION_PROXY_RF24_H

// Use RF24 mock
#ifdef RF24_MOCK

    #include <com/osteres/automation/mock/RF24.h>
    using com::osteres::automation::mock::RF24;

// Use real RF24
#else

    #include <RF24/RF24.h>
    #include "RF24/nRF24L01.h"

#endif

#endif //COM_OSTERES_AUTOMATION_PROXY_RF24_H
