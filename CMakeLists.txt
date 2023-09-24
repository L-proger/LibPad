

add_library(LibPad INTERFACE)

target_include_directories(LibPad
INTERFACE
    Src
)

target_sources(LibPad
INTERFACE
    Src/LibPad/PsIoPhy.h
    Src/LibPad/PsIo.h
    Src/LibPad/PsMemCard.h
    Src/LibPad/PsPad.h
)