#include <lmerrlog.h>
#include "NES6502.h"

NES6502::NES6502()
{
    instructions =
    {
            { "BRK", &NES6502::BRK, &NES6502::IMM, 7 },{ "ORA", &NES6502::ORA, &NES6502::IZX, 6 },{ "???", &NES6502::ILL, &NES6502::IMP, 2 },{ "???", &NES6502::ILL, &NES6502::IMP, 8 },{ "???", &NES6502::NOP, &NES6502::IMP, 3 },{ "ORA", &NES6502::ORA, &NES6502::ZP0, 3 },{ "ASL", &NES6502::ASL, &NES6502::ZP0, 5 },{ "???", &NES6502::ILL, &NES6502::IMP, 5 },{ "PHP", &NES6502::PHP, &NES6502::IMP, 3 },{ "ORA", &NES6502::ORA, &NES6502::IMM, 2 },{ "ASL", &NES6502::ASL, &NES6502::IMP, 2 },{ "???", &NES6502::ILL, &NES6502::IMP, 2 },{ "???", &NES6502::NOP, &NES6502::IMP, 4 },{ "ORA", &NES6502::ORA, &NES6502::ABS, 4 },{ "ASL", &NES6502::ASL, &NES6502::ABS, 6 },{ "???", &NES6502::ILL, &NES6502::IMP, 6 },
            { "BPL", &NES6502::BPL, &NES6502::REL, 2 },{ "ORA", &NES6502::ORA, &NES6502::IZY, 5 },{ "???", &NES6502::ILL, &NES6502::IMP, 2 },{ "???", &NES6502::ILL, &NES6502::IMP, 8 },{ "???", &NES6502::NOP, &NES6502::IMP, 4 },{ "ORA", &NES6502::ORA, &NES6502::ZPX, 4 },{ "ASL", &NES6502::ASL, &NES6502::ZPX, 6 },{ "???", &NES6502::ILL, &NES6502::IMP, 6 },{ "CLC", &NES6502::CLC, &NES6502::IMP, 2 },{ "ORA", &NES6502::ORA, &NES6502::ABY, 4 },{ "???", &NES6502::NOP, &NES6502::IMP, 2 },{ "???", &NES6502::ILL, &NES6502::IMP, 7 },{ "???", &NES6502::NOP, &NES6502::IMP, 4 },{ "ORA", &NES6502::ORA, &NES6502::ABX, 4 },{ "ASL", &NES6502::ASL, &NES6502::ABX, 7 },{ "???", &NES6502::ILL, &NES6502::IMP, 7 },
            { "JSR", &NES6502::JSR, &NES6502::ABS, 6 },{ "AND", &NES6502::AND, &NES6502::IZX, 6 },{ "???", &NES6502::ILL, &NES6502::IMP, 2 },{ "???", &NES6502::ILL, &NES6502::IMP, 8 },{ "BIT", &NES6502::BIT, &NES6502::ZP0, 3 },{ "AND", &NES6502::AND, &NES6502::ZP0, 3 },{ "ROL", &NES6502::ROL, &NES6502::ZP0, 5 },{ "???", &NES6502::ILL, &NES6502::IMP, 5 },{ "PLP", &NES6502::PLP, &NES6502::IMP, 4 },{ "AND", &NES6502::AND, &NES6502::IMM, 2 },{ "ROL", &NES6502::ROL, &NES6502::IMP, 2 },{ "???", &NES6502::ILL, &NES6502::IMP, 2 },{ "BIT", &NES6502::BIT, &NES6502::ABS, 4 },{ "AND", &NES6502::AND, &NES6502::ABS, 4 },{ "ROL", &NES6502::ROL, &NES6502::ABS, 6 },{ "???", &NES6502::ILL, &NES6502::IMP, 6 },
            { "BMI", &NES6502::BMI, &NES6502::REL, 2 },{ "AND", &NES6502::AND, &NES6502::IZY, 5 },{ "???", &NES6502::ILL, &NES6502::IMP, 2 },{ "???", &NES6502::ILL, &NES6502::IMP, 8 },{ "???", &NES6502::NOP, &NES6502::IMP, 4 },{ "AND", &NES6502::AND, &NES6502::ZPX, 4 },{ "ROL", &NES6502::ROL, &NES6502::ZPX, 6 },{ "???", &NES6502::ILL, &NES6502::IMP, 6 },{ "SEC", &NES6502::SEC, &NES6502::IMP, 2 },{ "AND", &NES6502::AND, &NES6502::ABY, 4 },{ "???", &NES6502::NOP, &NES6502::IMP, 2 },{ "???", &NES6502::ILL, &NES6502::IMP, 7 },{ "???", &NES6502::NOP, &NES6502::IMP, 4 },{ "AND", &NES6502::AND, &NES6502::ABX, 4 },{ "ROL", &NES6502::ROL, &NES6502::ABX, 7 },{ "???", &NES6502::ILL, &NES6502::IMP, 7 },
            { "RTI", &NES6502::RTI, &NES6502::IMP, 6 },{ "EOR", &NES6502::EOR, &NES6502::IZX, 6 },{ "???", &NES6502::ILL, &NES6502::IMP, 2 },{ "???", &NES6502::ILL, &NES6502::IMP, 8 },{ "???", &NES6502::NOP, &NES6502::IMP, 3 },{ "EOR", &NES6502::EOR, &NES6502::ZP0, 3 },{ "LSR", &NES6502::LSR, &NES6502::ZP0, 5 },{ "???", &NES6502::ILL, &NES6502::IMP, 5 },{ "PHA", &NES6502::PHA, &NES6502::IMP, 3 },{ "EOR", &NES6502::EOR, &NES6502::IMM, 2 },{ "LSR", &NES6502::LSR, &NES6502::IMP, 2 },{ "???", &NES6502::ILL, &NES6502::IMP, 2 },{ "JMP", &NES6502::JMP, &NES6502::ABS, 3 },{ "EOR", &NES6502::EOR, &NES6502::ABS, 4 },{ "LSR", &NES6502::LSR, &NES6502::ABS, 6 },{ "???", &NES6502::ILL, &NES6502::IMP, 6 },
            { "BVC", &NES6502::BVC, &NES6502::REL, 2 },{ "EOR", &NES6502::EOR, &NES6502::IZY, 5 },{ "???", &NES6502::ILL, &NES6502::IMP, 2 },{ "???", &NES6502::ILL, &NES6502::IMP, 8 },{ "???", &NES6502::NOP, &NES6502::IMP, 4 },{ "EOR", &NES6502::EOR, &NES6502::ZPX, 4 },{ "LSR", &NES6502::LSR, &NES6502::ZPX, 6 },{ "???", &NES6502::ILL, &NES6502::IMP, 6 },{ "CLI", &NES6502::CLI, &NES6502::IMP, 2 },{ "EOR", &NES6502::EOR, &NES6502::ABY, 4 },{ "???", &NES6502::NOP, &NES6502::IMP, 2 },{ "???", &NES6502::ILL, &NES6502::IMP, 7 },{ "???", &NES6502::NOP, &NES6502::IMP, 4 },{ "EOR", &NES6502::EOR, &NES6502::ABX, 4 },{ "LSR", &NES6502::LSR, &NES6502::ABX, 7 },{ "???", &NES6502::ILL, &NES6502::IMP, 7 },
            { "RTS", &NES6502::RTS, &NES6502::IMP, 6 },{ "ADC", &NES6502::ADC, &NES6502::IZX, 6 },{ "???", &NES6502::ILL, &NES6502::IMP, 2 },{ "???", &NES6502::ILL, &NES6502::IMP, 8 },{ "???", &NES6502::NOP, &NES6502::IMP, 3 },{ "ADC", &NES6502::ADC, &NES6502::ZP0, 3 },{ "ROR", &NES6502::ROR, &NES6502::ZP0, 5 },{ "???", &NES6502::ILL, &NES6502::IMP, 5 },{ "PLA", &NES6502::PLA, &NES6502::IMP, 4 },{ "ADC", &NES6502::ADC, &NES6502::IMM, 2 },{ "ROR", &NES6502::ROR, &NES6502::IMP, 2 },{ "???", &NES6502::ILL, &NES6502::IMP, 2 },{ "JMP", &NES6502::JMP, &NES6502::IND, 5 },{ "ADC", &NES6502::ADC, &NES6502::ABS, 4 },{ "ROR", &NES6502::ROR, &NES6502::ABS, 6 },{ "???", &NES6502::ILL, &NES6502::IMP, 6 },
            { "BVS", &NES6502::BVS, &NES6502::REL, 2 },{ "ADC", &NES6502::ADC, &NES6502::IZY, 5 },{ "???", &NES6502::ILL, &NES6502::IMP, 2 },{ "???", &NES6502::ILL, &NES6502::IMP, 8 },{ "???", &NES6502::NOP, &NES6502::IMP, 4 },{ "ADC", &NES6502::ADC, &NES6502::ZPX, 4 },{ "ROR", &NES6502::ROR, &NES6502::ZPX, 6 },{ "???", &NES6502::ILL, &NES6502::IMP, 6 },{ "SEI", &NES6502::SEI, &NES6502::IMP, 2 },{ "ADC", &NES6502::ADC, &NES6502::ABY, 4 },{ "???", &NES6502::NOP, &NES6502::IMP, 2 },{ "???", &NES6502::ILL, &NES6502::IMP, 7 },{ "???", &NES6502::NOP, &NES6502::IMP, 4 },{ "ADC", &NES6502::ADC, &NES6502::ABX, 4 },{ "ROR", &NES6502::ROR, &NES6502::ABX, 7 },{ "???", &NES6502::ILL, &NES6502::IMP, 7 },
            { "???", &NES6502::NOP, &NES6502::IMP, 2 },{ "STA", &NES6502::STA, &NES6502::IZX, 6 },{ "???", &NES6502::ILL, &NES6502::IMP, 2 },{ "???", &NES6502::ILL, &NES6502::IMP, 6 },{ "STY", &NES6502::STY, &NES6502::ZP0, 3 },{ "STA", &NES6502::STA, &NES6502::ZP0, 3 },{ "STX", &NES6502::STX, &NES6502::ZP0, 3 },{ "???", &NES6502::ILL, &NES6502::IMP, 3 },{ "DEY", &NES6502::DEY, &NES6502::IMP, 2 },{ "???", &NES6502::NOP, &NES6502::IMP, 2 },{ "TXA", &NES6502::TXA, &NES6502::IMP, 2 },{ "???", &NES6502::ILL, &NES6502::IMP, 2 },{ "STY", &NES6502::STY, &NES6502::ABS, 4 },{ "STA", &NES6502::STA, &NES6502::ABS, 4 },{ "STX", &NES6502::STX, &NES6502::ABS, 4 },{ "???", &NES6502::ILL, &NES6502::IMP, 4 },
            { "BCC", &NES6502::BCC, &NES6502::REL, 2 },{ "STA", &NES6502::STA, &NES6502::IZY, 6 },{ "???", &NES6502::ILL, &NES6502::IMP, 2 },{ "???", &NES6502::ILL, &NES6502::IMP, 6 },{ "STY", &NES6502::STY, &NES6502::ZPX, 4 },{ "STA", &NES6502::STA, &NES6502::ZPX, 4 },{ "STX", &NES6502::STX, &NES6502::ZPY, 4 },{ "???", &NES6502::ILL, &NES6502::IMP, 4 },{ "TYA", &NES6502::TYA, &NES6502::IMP, 2 },{ "STA", &NES6502::STA, &NES6502::ABY, 5 },{ "TXS", &NES6502::TXS, &NES6502::IMP, 2 },{ "???", &NES6502::ILL, &NES6502::IMP, 5 },{ "???", &NES6502::NOP, &NES6502::IMP, 5 },{ "STA", &NES6502::STA, &NES6502::ABX, 5 },{ "???", &NES6502::ILL, &NES6502::IMP, 5 },{ "???", &NES6502::ILL, &NES6502::IMP, 5 },
            { "LDY", &NES6502::LDY, &NES6502::IMM, 2 },{ "LDA", &NES6502::LDA, &NES6502::IZX, 6 },{ "LDX", &NES6502::LDX, &NES6502::IMM, 2 },{ "???", &NES6502::ILL, &NES6502::IMP, 6 },{ "LDY", &NES6502::LDY, &NES6502::ZP0, 3 },{ "LDA", &NES6502::LDA, &NES6502::ZP0, 3 },{ "LDX", &NES6502::LDX, &NES6502::ZP0, 3 },{ "???", &NES6502::ILL, &NES6502::IMP, 3 },{ "TAY", &NES6502::TAY, &NES6502::IMP, 2 },{ "LDA", &NES6502::LDA, &NES6502::IMM, 2 },{ "TAX", &NES6502::TAX, &NES6502::IMP, 2 },{ "???", &NES6502::ILL, &NES6502::IMP, 2 },{ "LDY", &NES6502::LDY, &NES6502::ABS, 4 },{ "LDA", &NES6502::LDA, &NES6502::ABS, 4 },{ "LDX", &NES6502::LDX, &NES6502::ABS, 4 },{ "???", &NES6502::ILL, &NES6502::IMP, 4 },
            { "BCS", &NES6502::BCS, &NES6502::REL, 2 },{ "LDA", &NES6502::LDA, &NES6502::IZY, 5 },{ "???", &NES6502::ILL, &NES6502::IMP, 2 },{ "???", &NES6502::ILL, &NES6502::IMP, 5 },{ "LDY", &NES6502::LDY, &NES6502::ZPX, 4 },{ "LDA", &NES6502::LDA, &NES6502::ZPX, 4 },{ "LDX", &NES6502::LDX, &NES6502::ZPY, 4 },{ "???", &NES6502::ILL, &NES6502::IMP, 4 },{ "CLV", &NES6502::CLV, &NES6502::IMP, 2 },{ "LDA", &NES6502::LDA, &NES6502::ABY, 4 },{ "TSX", &NES6502::TSX, &NES6502::IMP, 2 },{ "???", &NES6502::ILL, &NES6502::IMP, 4 },{ "LDY", &NES6502::LDY, &NES6502::ABX, 4 },{ "LDA", &NES6502::LDA, &NES6502::ABX, 4 },{ "LDX", &NES6502::LDX, &NES6502::ABY, 4 },{ "???", &NES6502::ILL, &NES6502::IMP, 4 },
            { "CPY", &NES6502::CPY, &NES6502::IMM, 2 },{ "CMP", &NES6502::CMP, &NES6502::IZX, 6 },{ "???", &NES6502::NOP, &NES6502::IMP, 2 },{ "???", &NES6502::ILL, &NES6502::IMP, 8 },{ "CPY", &NES6502::CPY, &NES6502::ZP0, 3 },{ "CMP", &NES6502::CMP, &NES6502::ZP0, 3 },{ "DEC", &NES6502::DEC, &NES6502::ZP0, 5 },{ "???", &NES6502::ILL, &NES6502::IMP, 5 },{ "INY", &NES6502::INY, &NES6502::IMP, 2 },{ "CMP", &NES6502::CMP, &NES6502::IMM, 2 },{ "DEX", &NES6502::DEX, &NES6502::IMP, 2 },{ "???", &NES6502::ILL, &NES6502::IMP, 2 },{ "CPY", &NES6502::CPY, &NES6502::ABS, 4 },{ "CMP", &NES6502::CMP, &NES6502::ABS, 4 },{ "DEC", &NES6502::DEC, &NES6502::ABS, 6 },{ "???", &NES6502::ILL, &NES6502::IMP, 6 },
            { "BNE", &NES6502::BNE, &NES6502::REL, 2 },{ "CMP", &NES6502::CMP, &NES6502::IZY, 5 },{ "???", &NES6502::ILL, &NES6502::IMP, 2 },{ "???", &NES6502::ILL, &NES6502::IMP, 8 },{ "???", &NES6502::NOP, &NES6502::IMP, 4 },{ "CMP", &NES6502::CMP, &NES6502::ZPX, 4 },{ "DEC", &NES6502::DEC, &NES6502::ZPX, 6 },{ "???", &NES6502::ILL, &NES6502::IMP, 6 },{ "CLD", &NES6502::CLD, &NES6502::IMP, 2 },{ "CMP", &NES6502::CMP, &NES6502::ABY, 4 },{ "NOP", &NES6502::NOP, &NES6502::IMP, 2 },{ "???", &NES6502::ILL, &NES6502::IMP, 7 },{ "???", &NES6502::NOP, &NES6502::IMP, 4 },{ "CMP", &NES6502::CMP, &NES6502::ABX, 4 },{ "DEC", &NES6502::DEC, &NES6502::ABX, 7 },{ "???", &NES6502::ILL, &NES6502::IMP, 7 },
            { "CPX", &NES6502::CPX, &NES6502::IMM, 2 },{ "SBC", &NES6502::SBC, &NES6502::IZX, 6 },{ "???", &NES6502::NOP, &NES6502::IMP, 2 },{ "???", &NES6502::ILL, &NES6502::IMP, 8 },{ "CPX", &NES6502::CPX, &NES6502::ZP0, 3 },{ "SBC", &NES6502::SBC, &NES6502::ZP0, 3 },{ "INC", &NES6502::INC, &NES6502::ZP0, 5 },{ "???", &NES6502::ILL, &NES6502::IMP, 5 },{ "INX", &NES6502::INX, &NES6502::IMP, 2 },{ "SBC", &NES6502::SBC, &NES6502::IMM, 2 },{ "NOP", &NES6502::NOP, &NES6502::IMP, 2 },{ "???", &NES6502::SBC, &NES6502::IMP, 2 },{ "CPX", &NES6502::CPX, &NES6502::ABS, 4 },{ "SBC", &NES6502::SBC, &NES6502::ABS, 4 },{ "INC", &NES6502::INC, &NES6502::ABS, 6 },{ "???", &NES6502::ILL, &NES6502::IMP, 6 },
            { "BEQ", &NES6502::BEQ, &NES6502::REL, 2 },{ "SBC", &NES6502::SBC, &NES6502::IZY, 5 },{ "???", &NES6502::ILL, &NES6502::IMP, 2 },{ "???", &NES6502::ILL, &NES6502::IMP, 8 },{ "???", &NES6502::NOP, &NES6502::IMP, 4 },{ "SBC", &NES6502::SBC, &NES6502::ZPX, 4 },{ "INC", &NES6502::INC, &NES6502::ZPX, 6 },{ "???", &NES6502::ILL, &NES6502::IMP, 6 },{ "SED", &NES6502::SED, &NES6502::IMP, 2 },{ "SBC", &NES6502::SBC, &NES6502::ABY, 4 },{ "???", &NES6502::NOP, &NES6502::IMP, 2 },{ "???", &NES6502::ILL, &NES6502::IMP, 7 },{ "???", &NES6502::NOP, &NES6502::IMP, 4 },{ "SBC", &NES6502::SBC, &NES6502::ABX, 4 },{ "INC", &NES6502::INC, &NES6502::ABX, 7 },{ "???", &NES6502::ILL, &NES6502::IMP, 7 }
    };
}

NES6502::~NES6502() {}

uint8_t NES6502::readByte(uint16_t address) {
    return bus -> readByte(address);
}

void NES6502::writeByte(uint16_t address, uint8_t data) {
    bus -> writeByte(address, data);
}

void NES6502::clk()
{
    if (cycles == 0) {
        opcode = readByte(pc);
        pc ++;
        cycles = instructions[opcode].cycles;
        uint8_t additional_cycle1 = (this -> *instructions[opcode].addressing_mode)();
        uint8_t additional_cycle2 = (this -> *instructions[opcode].operate)();
        cycles += additional_cycle1 & additional_cycle2;
    }
    cycles --;
}

uint8_t NES6502::getFlag(NES6502::FLAGS6502 flag)
{
    if ((status & flag) > 0) return 1;
    else return 0;
}

void NES6502::setFlag(NES6502::FLAGS6502 flag, bool value)
{
    if (value) status |= flag;
    else status &= ~flag;
}

uint8_t NES6502::IMP() // Implied
{
    fetched = A;
    return 0;
}

uint8_t NES6502::IMM() // Immediate
{
    address_abs = pc ++;
    return 0;
}

uint8_t NES6502::ZP0() // Zero Page
{
    address_abs = readByte(pc);
    pc ++;
    address_abs &= 0x00FF;
    return 0;
}

uint8_t NES6502::ZPX() // Zero Page with X Offset
{
    address_abs = readByte(pc ) + X;
    pc ++;
    address_abs &= 0x00FF;
    return 0;
}

uint8_t NES6502::ZPY() // Zero Page with Y Offset
{
    address_abs = readByte(pc ) + Y;
    pc ++;
    address_abs &= 0x00FF;
    return 0;
}

uint8_t NES6502::REL() // Relative
{
    address_rel = readByte(pc);
    pc ++;
    if (address_rel & 0x80) address_rel |= 0xFF00;
    return 0;
}

uint8_t NES6502::ABS() // Absolute
{
    uint16_t lowByte = readByte(pc);
    pc ++;
    uint16_t highByte = readByte(pc );
    pc ++;
    address_abs = (highByte << 8) | lowByte;
    return 0;
}

uint8_t NES6502::ABX() // Absolute with X Offset
{
    uint16_t lowByte = readByte(pc);
    pc ++;
    uint16_t highByte = readByte(pc);
    pc ++;
    address_abs = (highByte << 8) | lowByte;
    address_abs += X;
    if ((address_abs & 0xFF00) != (highByte << 8)) return 1;
    else return 0;
}

uint8_t NES6502::ABY() // Absolute with Y Offset
{
    uint16_t lowByte = readByte(pc);
    pc ++;
    uint16_t highByte = readByte(pc);
    pc ++;
    address_abs = (highByte << 8) | lowByte;
    address_abs += Y;
    if ((address_abs & 0xFF00) != (highByte << 8)) return 1;
    else return 0;
}

uint8_t NES6502::IND() // Indirect
{
    uint8_t ptr_lowByte = readByte(pc);
    pc ++;
    uint8_t ptr_highByte = readByte(pc);
    pc ++;
    uint8_t ptr = (ptr_highByte << 8) | ptr_lowByte;
    if (ptr_lowByte == 0x00FF) // Hardware bug
        address_abs = (readByte(ptr & 0xFF00) << 8) | readByte(ptr + 0);
    else
        address_abs = (readByte(ptr + 1) << 8) | readByte(ptr + 0);
    return 0;
}

uint8_t NES6502::IZX() // Indirect X
{
    uint16_t tmp = readByte(pc);
    pc ++;
    uint16_t zero_page_addr = (tmp + X) & 0x00FF;
    uint16_t lo = readByte(zero_page_addr);
    uint16_t hi = readByte((zero_page_addr + 1) & 0x00FF);
    address_abs = (hi << 8) | lo;
    return 0;
}

uint8_t NES6502::IZY() // Indirect Y
{
    uint16_t tmp = readByte(pc);
    pc ++;
    uint16_t lowByte = readByte(tmp & 0x00FF);
    uint16_t highByte = readByte((tmp + 1) & 0x00FF);
    address_abs = (highByte << 8) | lowByte;
    address_abs += Y;
    if ((address_abs & 0xFF00) != (highByte << 8)) return 1;
    else return 0;
}

uint8_t NES6502::fetch()
{
    if (instructions[opcode].addressing_mode != &NES6502::IMP)
        fetched = readByte(address_abs);
    return fetched;
}

uint8_t NES6502::AND()
{
    fetch();
    A &= fetched;
    setFlag(Z, A == 0x00);
    setFlag(N, A & 0x00);
    return 1;
}
