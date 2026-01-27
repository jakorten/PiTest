/*
 * SensorHub I2C Test - SAMD21 Side
 *
 * Responds to I2C commands from Raspberry Pi 4
 * Acts as I2C peripheral (slave) device on the backbone port
 */

#include <Wire.h>
#include "TwiPinHelper.h"

// I2C pin definitions
#define W0_SCL 27  // PA22
#define W0_SDA 26  // PA23

#define W1_SCL 39  // PA13
#define W1_SDA 28  // PA12

#define W2_SCL 13  // PA17
#define W2_SDA 11  // PA16

// Pin pair helpers
TwiPinPair portBackbone(W0_SCL, W0_SDA);
TwiPinPair portSensorsA(W1_SCL, W1_SDA);
TwiPinPair portSensorsB(W2_SCL, W2_SDA);

// TwoWire instances for each port
TwoWire WireBackbone(&sercom5, W0_SDA, W0_SCL);  // Main (Pi connection) - uses SERCOM5 alt mux
TwoWire WireSensorA(&sercom1, W1_SDA, W1_SCL);   // Sensor A
TwoWire WireSensorB(&sercom4, W2_SDA, W2_SCL);   // Sensor B

// I2C address (must match the address used on the Pi)
const uint8_t I2C_ADDRESS = 0x08;

// LED pin
#define ledHb 14

// Buffer for received data
volatile uint8_t receivedValue = 0;
volatile bool newData = false;

void setup() {
    delay(1500);
    Serial.begin(115200);
    delay(1500);

    pinMode(ledHb, OUTPUT);
    digitalWrite(ledHb, HIGH);

    // Initialize backbone port as I2C peripheral
    WireBackbone.begin(I2C_ADDRESS);
    WireBackbone.onReceive(onReceive);
    WireBackbone.onRequest(onRequest);

    // Set pin peripheral states (alt mux for SERCOM5)
    portBackbone.setPinPeripheralAltStates();

    while (!Serial);

    Serial.println("SensorHub I2C Test");
    Serial.println("==================");
    Serial.print("I2C Address: 0x");
    Serial.println(I2C_ADDRESS, HEX);
    Serial.println("Backbone port: PA22 (SCL) / PA23 (SDA)");
    Serial.println("Ready, waiting for Pi commands...");

    digitalWrite(ledHb, LOW);
}

void loop() {
    // Process received data in main loop
    if (newData) {
        Serial.print("Received: ");
        Serial.println(receivedValue);

        // Toggle LED on each received byte
        digitalWrite(ledHb, !digitalRead(ledHb));

        newData = false;
    }
}

// Called when data is received from master (Pi)
void onReceive(int numBytes) {
    while (WireBackbone.available()) {
        receivedValue = WireBackbone.read();
        newData = true;
    }
}

// Called when master (Pi) requests data
void onRequest() {
    // Echo back the last received value
    WireBackbone.write(receivedValue);
    Serial.print("Sent: ");
    Serial.println(receivedValue);
}

// SERCOM5 interrupt handler - required for WireBackbone callbacks
void SERCOM5_Handler(void) {
    WireBackbone.onService();
}
