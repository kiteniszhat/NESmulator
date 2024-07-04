//
// Created by Emanuel on 05.07.2024.
//

#include <lmerrlog.h>
#include "olc6502.h"

olc6502::olc6502() {

}

olc6502::~olc6502() {

}

uint8_t olc6502::readByte(uint16_t address) {
    return bus -> readByte(address);
}

void olc6502::writeByte(uint16_t address, uint8_t data) {
    bus -> writeByte(address, data);
}
