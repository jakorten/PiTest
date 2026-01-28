# SensorHub Pi - I2C Test

Test connection between Raspberry Pi 4 and SensorHub (SAMD21) via I2C.

## Hardware

- **Raspberry Pi 4**
- **[Adafruit Feather M0 Express](https://learn.adafruit.com/adafruit-feather-m0-express-designed-for-circuit-python-circuitpython/arduino-ide-setup)** (ATSAMD21G18)

## Wiring

Connect the Raspberry Pi 4 to the SAMD21 backbone port (W0):

| Pi 4 Pin | SAMD21 Pin | Signal |
|----------|------------|--------|
| GPIO 2 (Pin 3) | PA23 (pin 26) | I2C Data (SDA) |
| GPIO 3 (Pin 5) | PA22 (pin 27) | I2C Clock (SCL) |
| GND (Pin 6) | GND | Ground |

**Important:** Both devices must share a common ground.

**Note:** The Pi 4 has internal pull-up resistors on the I2C lines. If communication is unstable, add external 4.7k pull-up resistors to 3.3V.

### SAMD21 I2C Ports

| Port | Function | SCL | SDA |
|------|----------|-----|-----|
| W0 | Backbone (Pi) | PA22 (27) | PA23 (26) |
| W1 | Sensors A | PA13 (39) | PA12 (28) |
| W2 | Sensors B | PA17 (13) | PA16 (11) |

## Setup

### Raspberry Pi 4

1. Enable I2C:
   ```bash
   sudo raspi-config
   # Interface Options -> I2C -> Enable
   ```

2. Install dependencies:
   ```bash
   pip install smbus2
   ```

3. Run the test:
   ```bash
   python3 pi/i2c_test.py
   ```

### SAMD21

1. Open `samd21/i2c_test/i2c_test.ino` in Arduino IDE
2. Select board: Tools -> Board -> Arduino SAMD -> (your board)
3. Upload to SAMD21
4. Open Serial Monitor at 115200 baud to see debug output

## Testing

1. Upload the sketch to the SAMD21
2. Wire up the connections
3. Run the Python script on the Pi
4. You should see:
   - Pi: "Found devices at: ['0x8']" and echo responses
   - SAMD21: Received/sent values in Serial Monitor
   - LED toggles on each received byte

## I2C Address

Both sides use address `0x08`. To change, update:
- `SAMD21_ADDRESS` in `pi/i2c_test.py`
- `I2C_ADDRESS` in `samd21/i2c_test/i2c_test.ino`
