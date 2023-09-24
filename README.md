# LibPad
Low-level PS1/PS2 gamepad communication library (mostly for embedded usage)

## Pad pinout

| Pin number    | Pin name   | Meaning                                        |
| ------------- | ---------- |------------------------------------------------|
| 1             | DATA       | Data from joypad/memory card (SPI_MISO on MCU) |
| 2             | CMD        | Data to joypad/memory card (SPI_MOSI on MCU)   |
| 3             | +7.6V      | Power supply for vibration motors              |
| 4             | GND        | Ground                                         |
| 5             | VCC        | 3.6V (should work fine with 3.3V)              |
| 6             | ATT        | Attention (SPI_CS on MCU)                      |
| 7             | CLK        | Clock (SPI_CLK on MCU)                         |
| 8             | N/C [IRQ10]| Joy only. Typically not connected              |
| 9             | Ack [IRQ7] | Goes low for at least 1 clock after 8 bits transmission with 60us timeout|
