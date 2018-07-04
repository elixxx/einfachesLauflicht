#ifndef ModiPotiHandler_H
#define ModiPotiHandler_H

#include "PotiHandler.h"


enum Mode {brightness=0, mode=1, frequenz=2, nothing=3};
class ModiPotiHandler: public PotiHandler {
    public:
        
        ModiPotiHandler(uint8_t port, uint16_t startValue, uint8_t nGroupSplits);
        ModiPotiHandler(uint8_t port, uint8_t nGroupSplits);
        Mode getGroup();
        uint8_t getGroupID();

    private:
        uint16_t normalizedModePoti();

        uint8_t port;
        uint16_t startValue;
        uint8_t nGroupSplits;
        uint16_t normalizedMaxValue;
};

#endif