#include <Arduino.h>
#include <stdint.h>

class PotiHandler {
    public:
        PotiHandler(uint8_t port);
        uint16_t getValue();
    private:
        uint8_t port;
};