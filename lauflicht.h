#ifndef LAUFLICHT_H
#define LAUFLICHT_H
#include <stdint.h>
#include "Imode.h"
//#include "analogroute.h"
//typedef unsigned char uint8_t;



class Lauflicht: public IMode {
    public:
        Lauflicht(uint8_t* steps,uint8_t led, uint16_t& brightness, uint16_t delayMs, bool isDim);
        void step();
        bool isFinished();
        void backward(bool backward);
        void setDelayMs(uint16_t delayMs);
        uint16_t getDelayMS();
    private:
        char direction;
        int8_t step_id;
        uint8_t* steps;
        uint16_t& brightness;
        uint16_t delayMs;
        unsigned long msState;
        uint8_t nled;
        bool isDim;
};
#endif