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
    uint8_t data[35];
};

struct PsIoPort {
    uint8_t id;
    struct PsIoPhy* phy;
    struct PsIoBuffer rxBuffer;
};

struct PsPad {
    uint8_t slot;
    struct PsIoPort* port;
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

inline void psPadRead(struct PsPad* pad){
    uint8_t cmd[5] = {pad->slot, 0x42, 0x00, 0x00, 0x00};
    psIoPortExecuteCommand(pad->port, cmd, sizeof(cmd));
}

inline int psPadSetDataMask(struct PsPad* pad, uint8_t b0, uint8_t b1, uint8_t b2) {
    uint8_t cmd[] = { pad->slot, 0x4F, 0x00, b0, b1, b2, 0x00, 0x00, 0x00 };
    return psIoPortExecuteCommand(pad->port, cmd, sizeof(cmd));
}

inline int psPadConfigEnter(struct PsPad* pad) {
    uint8_t cmd[] = { pad->slot,0x43,0x00,0x01,0x00};
    return psIoPortExecuteCommand(pad->port, cmd, sizeof(cmd));
}

inline int psPadConfigExit(struct PsPad* pad) {
    uint8_t cmd[] = { pad->slot, 0x43, 0x00, 0x00, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A };
    return psIoPortExecuteCommand(pad->port, cmd, sizeof(cmd));
}

inline int psPadConfigQueryModel(struct PsPad* pad) { //no args 100%
    uint8_t cmd[9] = { pad->slot, 0x45, 0x00, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A };
    return psIoPortExecuteCommand(pad->port, cmd, sizeof(cmd));
}

inline int psPadConfigQueryAct(struct PsPad* pad, uint8_t b1) {  //b1 = index
    uint8_t cmd[9] = { pad->slot, 0x46, 0x00, b1, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A };
    return psIoPortExecuteCommand(pad->port, cmd, sizeof(cmd));
}

inline int psPadConfigQueryComb(struct PsPad* pad, uint8_t b1) { //b1 - maybe index, not failed but single record
    uint8_t cmd[9] = { pad->slot, 0x47, 0x00, b1, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A };
    return psIoPortExecuteCommand(pad->port, cmd, sizeof(cmd));
}

inline int psPadConfigQueryMode(struct PsPad* pad, uint8_t b1) { //byte #6 - supported mode, b1 = index
    uint8_t cmd[9] = { pad->slot, 0x4c, 0x00, b1, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A };
    return psIoPortExecuteCommand(pad->port, cmd, sizeof(cmd));
}

inline int psPadSetControllerMode(struct PsPad* pad, uint8_t analog, uint8_t lockMode) {
    uint8_t cmd[] = { pad->slot, 0x44, 0x00, (uint8_t)(analog ? 0x01 : 0x00), (uint8_t)(lockMode ? 0x03 : 0x5A), 0x00, 0x00, 0x00, 0x00 };
    return psIoPortExecuteCommand(pad->port, cmd, sizeof(cmd));
}



