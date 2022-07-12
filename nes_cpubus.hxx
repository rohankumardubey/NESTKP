#pragma once
#ifndef TKP_NES_CPUBUS_H
#define TKP_NES_CPUBUS_H
#include <vector>
#include <cstdint>
#include <string>
#include <array>

namespace TKPEmu::NES::Devices {
    enum {
        MAPPER_NROM,

    };
    class CPU;
    struct Header {
        char id[4];
        uint8_t prg_lsb;
        uint8_t chr_lsb;
        uint8_t flags_6;
        uint8_t flags_7;
        uint8_t mapper_msb;
        uint8_t prg_chr_msb;
        uint8_t prgram_eeprom_sz;
        uint8_t chrram_sz;
        uint8_t cpu_ppu_timing;
        uint8_t byte_13;
        uint8_t misc_roms;
        uint8_t default_expansion;
    };
    class Bus {
    public:
        bool LoadCartridge(std::string path);
        void Reset();
    private:
        uint8_t read(uint16_t addr);
        void write(uint16_t addr, uint8_t data);
        void refill_prg_map();

        std::array<uint8_t, 512> trainer_;
        std::vector<uint8_t> prg_rom_;
        std::vector<uint8_t> chr_rom_;
        uint16_t mapper_ = 0;
        Header header_;
        std::array<uint8_t*, 0x100> fast_map_;
        std::array<uint8_t, 0x800> ram_;
        friend class CPU;
    };
}
#endif