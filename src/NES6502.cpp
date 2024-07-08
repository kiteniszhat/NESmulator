//
// Created by Emanuel on 05.07.2024.
//

#include <lmerrlog.h>
#include "NES6502.h"

NES6502::NES6502() {

}

NES6502::~NES6502() {

}

uint8_t NES6502::readByte(uint16_t address) {
    return bus -> readByte(address);
}

void NES6502::writeByte(uint16_t address, uint8_t data) {
    bus -> writeByte(address, data);
}
