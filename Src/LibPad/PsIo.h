#pragma once

#include <stdint.h>
#include "PsIoPhy.h"

struct PsIoBuffer {
    uint8_t size;
    uint8_t data[200] = {};
};

struct PsIoPort {
    uint8_t id;
    PsIoPhy* phy;
    PsIoBuffer rxBuffer;

    inline bool psIoPortExecuteCommand(uint8_t* cmd, uint8_t cmdSize) {
        uint8_t i;

        if(!phy->begin()){
            return false;
        }

        rxBuffer.size = 0;
        for(i = 0; i < cmdSize; ++i){
            if(!phy->shift(cmd[i], &rxBuffer.data[i])){
                break;
            }
            rxBuffer.size = i + 1;
        }

        phy->end();
        return true;
    }
};
