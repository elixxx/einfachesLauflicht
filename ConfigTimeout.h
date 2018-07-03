#ifndef CONFIGTIMEOUT_H
#define CONFIGTIMEOUT_H

#include "ModiPotiHandler.h"
#include <stdint.h>



class ConfigTimeout {
    public:
        ConfigTimeout(uint16_t timeoutMs, Mode startupMode);
        void setActualConfigMode(Mode configMode);
        bool isTimeoutOver();
    
    private:
        uint16_t configTimeoutMs;
        uint32_t msState;
        Mode configLastMode;
};
#endif