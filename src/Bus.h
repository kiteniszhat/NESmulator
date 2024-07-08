#ifndef NESMULATOR_BUS_H
#define NESMULATOR_BUS_H

#include <cstdint>
#include <array>
#include "NES6502.h"

class Bus
{
public:
    Bus();
    ~Bus();

    // Devices on bus
    NES6502 CPU;
    std::array<uint8_t, 64 * 1024> RAM; // Fake RAM for a moment

    // Bus read and write
    void writeByte(uint16_t address, uint8_t data);
    uint8_t readByte(uint16_t address, bool readOnly = false);
};


#endif //NESMULATOR_BUS_H
