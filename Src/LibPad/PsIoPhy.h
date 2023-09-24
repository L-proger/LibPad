#pragma once

#include <cstdint>

struct PsIoPhy {
    virtual ~PsIoPhy() = default;
    virtual bool begin() = 0;
    virtual bool shift(uint8_t txData, uint8_t* rxData) = 0;
    virtual void end() = 0;
};