#include "PotiHandler.h"

PotiHandler::PotiHandler(uint8_t port): port(port) {}

uint16_t PotiHandler::getValue() {
    return analogRead(this->port);
}