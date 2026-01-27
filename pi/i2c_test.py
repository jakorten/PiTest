#!/usr/bin/env python3
"""
Test I2C connection between Raspberry Pi 4 and SensorHub (SAMD21)
"""

import smbus2
import time

# I2C address of the SAMD21 (must match the address set on the SAMD21)
SAMD21_ADDRESS = 0x08

# Create I2C bus (bus 1 on Pi 4)
bus = smbus2.SMBus(1)


def send_byte(value: int) -> bool:
    """Send a single byte to the SAMD21."""
    try:
        bus.write_byte(SAMD21_ADDRESS, value)
        print(f"Sent: {value}")
        return True
    except OSError as e:
        print(f"Error sending byte: {e}")
        return False


def read_byte() -> int | None:
    """Read a single byte from the SAMD21."""
    try:
        data = bus.read_byte(SAMD21_ADDRESS)
        print(f"Received: {data}")
        return data
    except OSError as e:
        print(f"Error reading byte: {e}")
        return None


def send_and_receive(value: int) -> int | None:
    """Send a byte and read the response."""
    if send_byte(value):
        time.sleep(0.01)  # Small delay for SAMD21 to process
        return read_byte()
    return None


def scan_i2c_bus() -> list[int]:
    """Scan the I2C bus for connected devices."""
    devices = []
    for address in range(0x03, 0x78):
        try:
            bus.write_quick(address)
            devices.append(address)
        except OSError:
            pass
    return devices


def main():
    print("SensorHub I2C Test")
    print("=" * 40)

    # Scan for devices
    print("\nScanning I2C bus...")
    devices = scan_i2c_bus()
    if devices:
        print(f"Found devices at: {[hex(d) for d in devices]}")
    else:
        print("No I2C devices found. Check wiring and connections.")
        return

    if SAMD21_ADDRESS not in devices:
        print(f"\nWarning: SAMD21 not found at expected address {hex(SAMD21_ADDRESS)}")
        return

    print(f"\nSAMD21 found at {hex(SAMD21_ADDRESS)}")
    print("\nStarting test communication...")

    # Test: send incrementing values
    for i in range(5):
        print(f"\n--- Test {i + 1} ---")
        response = send_and_receive(i)
        if response is not None:
            print(f"Echo test: sent {i}, received {response}")
        time.sleep(0.5)

    print("\n" + "=" * 40)
    print("Test complete!")


if __name__ == "__main__":
    main()
