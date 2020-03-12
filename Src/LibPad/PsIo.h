#pragma once

#include <stdint.h>

#define PS_IO_RESULT_OK 0
#define PS_IO_RESULT_FAIL 1

struct PsIoPhy {
    int (*init)(void* context);
    int (*begin)(void* context);
    int (*shift)(void* context, uint8_t txData, uint8_t* rxData);
    void (*end)(void* context);
    void* context;
};

struct PsIoBuffer {
    uint8_t size;
    uint8_t data[200];
};

struct PsIoPort {
    uint8_t id;
    struct PsIoPhy* phy;
    struct PsIoBuffer rxBuffer;
};


void psIoByteDelay();

inline int psIoPortExecuteCommand(struct PsIoPort* port, uint8_t* cmd, uint8_t cmdSize) {
    int result;
    uint8_t i;

    result = port->phy->begin(port->phy->context);

    if(result != PS_IO_RESULT_OK){
        return result;
    }

    port->rxBuffer.size = 0;
    for(i = 0; i < cmdSize; ++i){
        result = port->phy->shift(port->phy->context, cmd[i], &port->rxBuffer.data[i]);
        if(result != PS_IO_RESULT_OK){
            break;
        }
        port->rxBuffer.size = i + 1;
    }

    port->phy->end(port->phy->context);
    return result;
}
