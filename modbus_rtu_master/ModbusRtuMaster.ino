#include <ModbusRTUMaster.h>
#include <SoftwareSerial.h>

// select serial pins
const uint8_t rxPin = 10;
const uint8_t txPin = 11;

// create modbsu serial interface
SoftwareSerial modbusSerial(rxPin, txPin);
// create modbus rtu master object
ModbusRTUMaster modbus(modbusSerial);
// baudrate
const uint32_t baud = 38400;
// modbus master local buffers
uint16_t holdingRegisters[2];
uint16_t inputRegisters[2];
bool discreteInputs[2];

// door status strings
char *frontDoor;
char *backDoor;

void setup(){
  // initialization
  Serial.begin(9600);
  modbus.begin(baud, SERIAL_8N1);
}


void loop(){
  // read input registers
  modbus.readInputRegisters(1, 0, inputRegisters, 2);
  // read motor rpm
  Serial.print("Motor RPM: ");
  Serial.print(inputRegisters[0]);
  Serial.print("\n");

  // read discrete inputs
  modbus.readDiscreteInputs(1, 0, discreteInputs, 2);
  // read front door status
  frontDoor = (discreteInputs[0])? "Front Door is Closed": "Front Door is Open";
  Serial.println(frontDoor);
  // read back door status
  backDoor = (discreteInputs[1])? "Back Door is Closed": "Back Door is Open";
  Serial.println(backDoor);

  Serial.println("--------------------------------------");
  Serial.println("");

  // set holding registers
  // set temp setpoint
  holdingRegisters[0] = 30;
  // set humid set point
  holdingRegisters[1] = 25;
  modbus.writeMultipleHoldingRegisters(1, 0, holdingRegisters, 2);
  delay(2000);
}


