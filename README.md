# LibPad
Low-level PS1/PS2 gamepad communication library (mostly for embedded usage)

## Data interface
It is just SPI: LSB first, CPOL=1, CPHA=1

## Pad pinout

| Pin number    | Pin name           | Meaning                                        |
| ------------- | ------------------ |------------------------------------------------|
| 1             | DATA [Open-drain!] | Data from joypad/memory card (SPI_MISO on MCU). Open drain (requires pull-up) |
| 2             | CMD                | Data to joypad/memory card (SPI_MOSI on MCU)   |
| 3             | +7.6V              | Power supply for vibration motors              |
| 4             | GND                | Ground                                         |
| 5             | VCC                | 3.6V (should work fine with 3.3V)              |
| 6             | ATT                | Attention (SPI_CS on MCU)                      |
| 7             | CLK                | Clock (SPI_CLK on MCU) PS1: 250KHz for controller and memory card, 500KHz or 1MHz for multitap. PS2: 250KHz for controller, 25MHz for memory card |
| 8             | N/C [IRQ10]        | Joy only (Konami Justifier). Typically not connected              |
| 9             | Ack [IRQ7] [Open-drain!]| Goes low for at least 1 clock after each 8 bits transmitted with 60us timeout . Open drain (requires pull-up)|
