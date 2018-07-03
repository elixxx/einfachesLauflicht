#ifndef IMODE_H
#define IMODE_H
#include <stdint.h>

class IMode {
    public: 
        virtual void step() = 0;
        virtual bool isFinished() = 0;
        virtual void setDurationMs(uint16_t durationMs) = 0;
        virtual void setDelayMs(uint16_t delayMs) = 0;
        virtual uint16_t getDelayMS() = 0;
        virtual ~IMode() {}
};
#endif