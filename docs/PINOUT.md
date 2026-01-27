# SensorHub SAMD21 Pinout

Based on SensorHub SAMD21 v1.2.7 schematic and TinyAdapter v1.0.0.

## I2C Buses

The SAMD21 SensorHub has three I2C buses:

| Bus | Name | SCL | SDA | SERCOM | Function |
|-----|------|-----|-----|--------|----------|
| W0 | Backbone | PA22 (pin 27) | PA23 (pin 26) | SERCOM3 | Pi connection |
| W1 | Sensors A | PA13 (pin 39) | PA12 (pin 28) | SERCOM1 (ALT) | Sensor bus A |
| W2 | Sensors B | PA17 (pin 13) | PA16 (pin 11) | SERCOM4 | Sensor bus B |

### Arduino Pin Mapping

```cpp
// I2C pin definitions
#define W0_SCL 27  // PA22 - Backbone
#define W0_SDA 26  // PA23

#define W1_SCL 39  // PA13 - Sensors A
#define W1_SDA 28  // PA12

#define W2_SCL 13  // PA17 - Sensors B
#define W2_SDA 11  // PA16
```

### TwoWire Instances

```cpp
TwoWire WireBackbone(&sercom3, W0_SDA, W0_SCL);  // Pi connection
TwoWire WireSensorA(&sercom1, W1_SDA, W1_SCL);   // Sensor bus A
TwoWire WireSensorB(&sercom4, W2_SDA, W2_SCL);   // Sensor bus B
```

### Pin Peripheral Configuration

```cpp
portBackbone.setPinPeripheralStates();     // SERCOM3 - default peripheral
portSensorsA.setPinPeripheralAltStates();  // SERCOM1 - alternate peripheral
portSensorsB.setPinPeripheralStates();     // SERCOM4 - default peripheral
```

## Internal SPI (Flash Memory)

On-board SPI flash uses SERCOM2:

| Signal | Pin | Function |
|--------|-----|----------|
| FLASH_SCK | D3 | SPI Clock |
| FLASH_MOSI | D4 | SPI Data Out |
| FLASH_MISO | D2 | SPI Data In |
| FLASH_CS | - | Chip Select |

## LEDs

| LED | Pin | Function |
|-----|-----|----------|
| HB_LED0 | 14 | Heartbeat (Red) |
| TXLED | - | TX Activity |
| RXLED | - | RX Activity |
| Power LED | - | Power indicator (can be disabled via SJ1) |

## USB

| Signal | Pin | Function |
|--------|-----|----------|
| USB_D- | PA24 | USB Data Negative |
| USB_D+ | PA25 | USB Data Positive |

## Debug (SWD)

| Signal | Pin | Function |
|--------|-----|----------|
| SWCLK | PA30 | Debug Clock |
| SWDIO | PA31 | Debug Data I/O |
| RESET | - | System Reset |

## Interrupt Pins

| Signal | Function |
|--------|----------|
| INT4 | External interrupt 4 |
| INT5 | External interrupt 5 |
| INT8 | External interrupt 8 |
| INT9 | External interrupt 9 |

## SAMD21 Pin Capabilities

| Pin | Port | Functions |
|-----|------|-----------|
| PA00 | EINT0 | SERCOM1.0 |
| PA01 | EINT1 | SERCOM1.1 |
| PA02 | EINT2 | AIN0, DAC OUT |
| PA03 | EINT3 | AIN1, VREF |
| PA04 | EINT4 | AIN4, SERCOM0.0 |
| PA05 | EINT5 | AIN5, SERCOM0.1 |
| PA06 | EINT6 | AIN6, SERCOM0.2 |
| PA07 | I7 | AIN7, SERCOM0.3 |
| PA08 | I2C | AIN16, SERCOM0+2.0 |
| PA09 | I2C, I9 | AIN17, SERCOM0+2.1 |
| PA10 | I10 | AIN18, SERCOM0+2.2 |
| PA11 | I11 | AIN19, SERCOM0+2.3 |
| PA12 | I12, I2C | **SDA_SENSOR0** (SERCOM2+4.0) |
| PA13 | I13, I2C | **SCL_SENSOR0** (SERCOM2+4.1) |
| PA14 | I14 | SERCOM2+4.2 |
| PA15 | I15 | SERCOM2+4.3 |
| PA16 | I2C, I0 | **SDA_SENSOR1** (SERCOM1+3.0) |
| PA17 | I2C, I1 | **SCL_SENSOR1** (SERCOM1+3.1) |
| PA18 | I2 | SERCOM1+3.2 |
| PA19 | I3 | SERCOM1+3.3 |
| PA20 | I4 | SERCOM3+5.2 |
| PA21 | I5 | SERCOM3+5.3 |
| PA22 | I2C, I6 | **SCL Backbone** (SERCOM3+5.0) |
| PA23 | I2C, I7 | **SDA Backbone** (SERCOM3+5.1) |
| PA24 | I12 | USB D-, SERCOM3+5.2 |
| PA25 | I13 | USB D+, SERCOM3+5.3 |
| PA27 | I15 | GPIO |
| PA28 | I8 | GPIO |
| PA30 | I10 | SWCLK, SERCOM1.2 |
| PA31 | I11 | SWDIO, SERCOM1.3 |
| PB02 | I2 | AIN10, SERCOM5.0 |
| PB03 | I3 | AIN11, SERCOM5.1 |
| PB08 | I8 | AIN2, SERCOM4.0 |
| PB09 | I9 | AIN3, SERCOM4.1 |
| PB10 | I10 | SERCOM4.2 |
| PB11 | I11 | SERCOM4.3 |
| PB22 | I6 | SERCOM5.2 |
| PB23 | I7 | SERCOM5.3 |

---

# TinyAdapter (Pi Adapter) Pinout

The TinyAdapter connects the Raspberry Pi to the SensorHub backbone I2C bus.

## Pi to SensorHub Connection

| Pi GPIO | Pi Pin | Signal | SensorHub |
|---------|--------|--------|-----------|
| GPIO 2 | Pin 3 | SDA | PA23 (Backbone SDA) |
| GPIO 3 | Pin 5 | SCL | PA22 (Backbone SCL) |
| 3.3V | Pin 1 | 3.3V | 3.3V |
| 5V | Pin 2,4 | 5V | 5V |
| GND | Pin 6,9,etc | GND | GND |

## Wiring Diagram

```
Raspberry Pi 4                    SensorHub SAMD21
=============                     ================

Pin 1  (3.3V)  ─────────────────  3.3V
Pin 2  (5V)    ─────────────────  5V
Pin 3  (SDA)   ─────────────────  PA23 (W0_SDA, pin 26)
Pin 5  (SCL)   ─────────────────  PA22 (W0_SCL, pin 27)
Pin 6  (GND)   ─────────────────  GND
```

## I2C Configuration

- Pi uses I2C bus 1 (`/dev/i2c-1`)
- Default I2C speed: 100kHz (can be increased to 400kHz)
- Pull-up resistors: Internal on Pi, may need external 4.7k for stability
