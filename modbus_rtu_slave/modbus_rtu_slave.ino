#include <ModbusRTUSlave.h>
#include <SoftwareSerial.h>

const uint8_t rxPin = 10;
const uint8_t txPin = 11;

SoftwareSerial mySerial(rxPin, txPin);
ModbusRTUSlave modbus_rtu_slave(mySerial);

const uint8_t slaveID = 1;
const uint32_t baud = 9600;

uint16_t holdingRegisters[20] = {0};
uint16_t sensor = 0;

void setup() {
  // configure Holding Registers
  modbus_rtu_slave.configureHoldingRegisters(holdingRegisters, 20);
  // Start slave
  modbus_rtu_slave.begin(slaveID, baud, SERIAL_8N1);

}

void loop() {
  // Read Analog value
  sensor = analogRead(A1);
  // Write value to Holding register
  holdingRegisters[0] = sensor;
  // Modbus Poll
  modbus_rtu_slave.poll();
}
