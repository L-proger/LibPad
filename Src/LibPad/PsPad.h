#pragma once

#include "PsIo.h"

struct PsPad {
    uint8_t slot = 0x01;
    struct PsIoPort* port;

    //(SCPH-1010)
    inline bool psPadPollDigital(){
        uint8_t cmd[5] = {slot, 0x42, 0x00, 0x00, 0x00};
        return port->psIoPortExecuteCommand(cmd, sizeof(cmd));
    }

    // (SCPH-1110) or (SCPH-1180)
    inline bool psPadPollAnalog(){
        uint8_t cmd[9] = {slot, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        return port->psIoPortExecuteCommand(cmd, sizeof(cmd));
    }

    // DualShock 1,2 (SCPH-1180, SCPH-1200, SCPH-10010)
    inline bool psPadPollAnalogRumble(std::uint8_t rightMotor, std::uint8_t leftMotor){
        uint8_t cmd[9] = {slot, 0x42, 0x00, 0x00, 0x00, rightMotor, leftMotor, 0x00, 0x00};
        return port->psIoPortExecuteCommand(cmd, sizeof(cmd));
    }

    // DualShock 2 SCPH-10010
    inline bool psPadPollDualshock2(){
        uint8_t cmd[21] = {slot, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        return port->psIoPortExecuteCommand(cmd, sizeof(cmd));
    }


    inline int psPadSetDataMask(uint8_t b0, uint8_t b1, uint8_t b2) {
        uint8_t cmd[] = { slot, 0x4F, 0x00, b0, b1, b2, 0x00, 0x00, 0x00 };
        return port->psIoPortExecuteCommand(cmd, sizeof(cmd));
    }

    inline int psPadConfigEnter() {
        uint8_t cmd[] = { slot, 0x43, 0x00, 0x01, 0x00};
        return port->psIoPortExecuteCommand(cmd, sizeof(cmd));
    }

    inline int psPadConfigExit() {
        uint8_t cmd[] = { slot, 0x43, 0x00, 0x00, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A };
        return port->psIoPortExecuteCommand(cmd, sizeof(cmd));
    }

    inline int psPadConfigQueryModel() { //no args 100%
        uint8_t cmd[9] = { slot, 0x45, 0x00, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A };
        return port->psIoPortExecuteCommand(cmd, sizeof(cmd));
    }

    inline int psPadConfigQueryAct(uint8_t b1) {  //b1 = index
        uint8_t cmd[9] = { slot, 0x46, 0x00, b1, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A };
        return port->psIoPortExecuteCommand(cmd, sizeof(cmd));
    }

    inline int psPadConfigQueryComb(uint8_t b1) { //b1 - maybe index, not failed but single record
        uint8_t cmd[9] = { slot, 0x47, 0x00, b1, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A };
        return port->psIoPortExecuteCommand(cmd, sizeof(cmd));
    }

    inline int psPadConfigQueryMode(uint8_t b1) { //byte #6 - supported mode, b1 = index
        uint8_t cmd[9] = { slot, 0x4c, 0x00, b1, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A };
        return port->psIoPortExecuteCommand(cmd, sizeof(cmd));
    }

    inline int psPadSetControllerMode(uint8_t analog, uint8_t lockMode) {
        uint8_t cmd[] = { slot, 0x44, 0x00, (uint8_t)(analog ? 0x01 : 0x00), (uint8_t)(lockMode ? 0x03 : 0x5A), 0x00, 0x00, 0x00, 0x00 };
        return port->psIoPortExecuteCommand(cmd, sizeof(cmd));
    }
};
