#ifndef NESMULATOR_NES6502_H
#define NESMULATOR_NES6502_H


#include <string>
#include <vector>
#include "Bus.h"

class NES6502
{
public:
    NES6502();
    ~NES6502();

    enum FLAGS6502
    {
        C = (1 << 0), // Carry Bit
        Z = (1 << 1), // Zero
        I = (1 << 2), // Disable Interrupts
        D = (1 << 3), // Decimal Mode
        B = (1 << 4), // Break
        U = (1 << 5), // Unused :c (originally described as 1)
        V = (1 << 6), // Overflow
        N = (1 << 7), // Negative
    };

    uint8_t A = 0x00;       // Accumulator
    uint8_t X = 0x00;       // X register
    uint8_t Y = 0x00;       // Y register
    uint8_t stkp = 0x00;    // Stack pointer
    uint8_t pc = 0x0000;    // Program counter
    uint8_t status = 0x0000;// Status Register

    void connectBus(Bus *_bus) {
        bus = _bus;
    }

private:
    // Addressing modes
    uint8_t IMP(); uint8_t IMM();
    uint8_t ZP0(); uint8_t ZPX();
    uint8_t ZPY(); uint8_t REL();
    uint8_t ABS(); uint8_t ABX();
    uint8_t ABY(); uint8_t IND();
    uint8_t IZX(); uint8_t IZY();

    // Opcodes
    uint8_t ADC(); uint8_t AND(); uint8_t ASL(); uint8_t BCC();
    uint8_t BCS(); uint8_t BEQ(); uint8_t BIT(); uint8_t BMI();
    uint8_t BNE(); uint8_t BPL(); uint8_t BRK(); uint8_t BVC();
    uint8_t BVS(); uint8_t CLC(); uint8_t CLD(); uint8_t CLI();
    uint8_t CLV(); uint8_t CMP(); uint8_t CPX(); uint8_t CPY();
    uint8_t DEC(); uint8_t DEX(); uint8_t DEY(); uint8_t EOR();
    uint8_t INC(); uint8_t INX(); uint8_t INY(); uint8_t JMP();
    uint8_t JSR(); uint8_t LDA(); uint8_t LDX(); uint8_t LDY();
    uint8_t LSR(); uint8_t NOP(); uint8_t ORA(); uint8_t PHA();
    uint8_t PHP(); uint8_t PLA(); uint8_t PLP(); uint8_t ROL();
    uint8_t ROR(); uint8_t RTI(); uint8_t RTS(); uint8_t SBC();
    uint8_t SEC(); uint8_t SED(); uint8_t SEI(); uint8_t STA();
    uint8_t STX(); uint8_t STY(); uint8_t TAX(); uint8_t TAY();
    uint8_t TSX(); uint8_t TXA(); uint8_t TXS(); uint8_t TYA();

    // Illegal opcode
    uint8_t ILL();

    void clk();
    void rst();
    void irq(); // Interrupt request - executes an instruction at a specific location
    void nmi(); // Non-maskable interrupt - as above, but cannot be disabled

    uint8_t fetch();
    uint8_t fetched = 0x00;
    uint16_t temp = 0x0000; // A convenience variable used everywhere
    uint16_t address_abs = 0x0000; // All used memory addresses end up in here
    uint16_t address_rel = 0x0000; // Represents absolute address following a branch
    uint8_t opcode = 0x00; // Is the instruction byte
    uint8_t cycles = 0;
    uint32_t clock_count = 0;

private:
    Bus *bus = nullptr;
    uint8_t readByte(uint16_t address);
    void writeByte(uint16_t address, uint8_t data);

    uint8_t getFlag(FLAGS6502 flag);
    void setFlag(FLAGS6502 flag, bool value);

    struct INSTRUCTION
    {
        std::string name;
        uint8_t(NES6502::*operate)() = nullptr;
        uint8_t(NES6502::*addressing_mode)() = nullptr;
        uint8_t cycles = 0;
    };

    std::vector<INSTRUCTION> instructions;
};


#endif //NESMULATOR_NES6502_H
