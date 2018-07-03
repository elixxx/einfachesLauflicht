#ifndef BASETIMEEVENT_H
#define BASETIMEEVENT_H
#include <Arduino.h>
#include <stdint.h>
#include "Imode.h"
class BaseTimedEvent: public IMode {
    public:
        BaseTimedEvent(uint8_t* steps,uint8_t nled, uint16_t& brightness, uint16_t delayMs, bool isDim);
        void step();
        virtual void validRun();
        virtual void setDelayMs(uint16_t delayMs);
        uint16_t getDelayMS();
        bool isFinished();
        void setDurationMs(uint16_t durationMs);

    protected:
        uint8_t* steps;
        uint16_t& brightness;
        uint16_t delayMs;
        uint16_t stepId;
        unsigned long msState;
        uint8_t nled;
        uint8_t old;
        bool isDim;
        unsigned long finishTime;
};
#endif