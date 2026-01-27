# SAMD21 - Raspberry Pi I2C Setup

## Overview

The SAMD21 acts as an I2C peripheral (slave) on the backbone port, communicating with the Raspberry Pi 4 as the master.

## Configuration

| Parameter | Value |
|-----------|-------|
| I2C Address | 0x08 |
| SERCOM | SERCOM5 (alt mux) |
| SCL | PA22 (pin 27) |
| SDA | PA23 (pin 26) |
| Pi I2C Bus | 1 |

## SAMD21 Setup Notes

- Uses `SERCOM5` with alternate pin mux (`PIO_SERCOM_ALT`) to avoid conflict with the default Wire library which claims SERCOM3
- Requires `SERCOM5_Handler` interrupt handler for callbacks to work:

```cpp
void SERCOM5_Handler(void) {
    WireBackbone.onService();
}
```

## Testing from Raspberry Pi

Detect the device:
```bash
i2cdetect -y 1
```

Send a byte:
```bash
i2cset -y 1 0x08 0x42
```

Read a byte:
```bash
i2cget -y 1 0x08
```

## Troubleshooting

| Symptom | Cause | Solution |
|---------|-------|----------|
| Device not detected | Wiring or address mismatch | Check connections, verify pull-ups |
| Detected but reads 0xFF | Missing SERCOM handler | Add `SERCOM5_Handler` function |
| Callbacks not firing | Wrong pin mux | Use `setPinPeripheralAltStates()` for SERCOM5 |
