#include "Bus.h"

Bus::Bus() {
    // Clear RAM
    for (auto &i : RAM) i = 0x00;

    // Connect CPU to bus
    CPU.connectBus(this);
}

Bus::~Bus() = default;

void Bus::writeByte(uint16_t address, uint8_t data) {
    if (address >= 0x0000 && address <= 0xFFFF)
        RAM[address] = data;
}

uint8_t Bus::readByte(uint16_t address, bool readOnly) {
    if (address >= 0x0000 && address <= 0xFFFF)
        return RAM[address];
    return 0x00;
}
