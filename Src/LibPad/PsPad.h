#pragma once

#include "PsIo.h"

struct PsPad {
    uint8_t slot;
    struct PsIoPort* port;
};

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



