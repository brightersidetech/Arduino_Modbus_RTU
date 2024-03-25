#include <ModbusRTUSlave.h>

ModbusRTUSlave modbus_rtu_slave(Serial);

const uint8_t slaveID = 1;
const uint32_t baud = 9600;

uint16_t holdingRegisters[20] = {0};
uint16_t value = 0;

void setup() {
  // put your setup code here, to run once:
  modbus_rtu_slave.configureHoldingRegisters(holdingRegisters, 20);
  //modbus.configureDiscreteInputs(discreteInputs, 2);
  modbus_rtu_slave.begin(slaveID, baud, SERIAL_8N1);

}

void loop() {
  // put your main code here, to run repeatedly:
  value = value + 3;
  holdingRegisters[1] = value;
  holdingRegisters[2] = 3;
  modbus_rtu_slave.poll();
  //Serial.println(value);

  //delay(5000);
}
