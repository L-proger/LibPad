#pragma once

#include "PsIo.h"
#include <string.h>

#define PS_MEM_CARD_BLOCK_STATE_BEGIN 0xA1
#define PS_MEM_CARD_BLOCK_STATE_MIDDLE 0xA2
#define PS_MEM_CARD_BLOCK_STATE_END 0xA2
#define PS_MEM_CARD_BLOCK_STATE_FORMATTED 0xA0
#define PS_MEM_CARD_BLOCK_STATE_BEGIN_DELETED 0xA1
#define PS_MEM_CARD_BLOCK_STATE_MIDDLE_DELETED 0xA2
#define PS_MEM_CARD_BLOCK_STATE_END_DELETED 0xA2

struct PsMemCard {
    uint8_t slot;
    struct PsIoPort* port;
};

int psMemCardReadId(struct PsMemCard* memcard){
    uint8_t cmd[] = { memcard->slot, 0x53, 0, 0, 0, 0, 0, 0, 0, 0 };
    return psIoPortExecuteCommand(memcard->port, cmd, sizeof(cmd));
}

int psMemCardRead(struct PsMemCard* memcard, uint16_t addr, uint8_t* rxBuffer128){ //Addr: 0..3FFh
    int error;

    uint8_t cmd[10 + 128 + 2];
    memset(cmd, 0, sizeof(cmd));

    cmd[0] = memcard->slot;
    cmd[1] = 0x52;
    cmd[4] = (uint8_t)((addr & 0xff00) >> 8);
    cmd[5] = (uint8_t)(addr & 0xff);

    error = psIoPortExecuteCommand(memcard->port, cmd, sizeof(cmd));
    if(!error){
        memcpy(rxBuffer128, &memcard->port->rxBuffer.data[10], 128);
    }
    return error;
}
