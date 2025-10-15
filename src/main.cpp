#include <Arduino.h>
#include <ModbusMaster.h>

#define RS485_RX1 (35)
#define RS485_TX1 (15)
#define RS485_DIR1 (14)

#define RS485_RX2 (16)
#define RS485_TX2 (17)
#define RS485_DIR2 (27)

#define MODE_SEND HIGH
#define MODE_RECV LOW

ModbusMaster node1;
ModbusMaster node2;

// RS485 Port One
void preTransmissionOne() { digitalWrite(RS485_DIR1, 1); }
void postTransmissionOne() { digitalWrite(RS485_DIR1, 0); }

// RS485 Port Two
void preTransmissionTwo() { digitalWrite(RS485_DIR2, 1); }
void postTransmissionTwo() { digitalWrite(RS485_DIR2, 0); }

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(RS485_DIR1, OUTPUT);
  digitalWrite(RS485_DIR1, 0);

  Serial1.begin(9600, SERIAL_8N1, RS485_RX1, RS485_TX1);

  uint8_t currentSlaveId = 3;

  uint16_t newSlaveId = 1;

  Serial.printf("Changing address from %d to %d...\n", currentSlaveId, newSlaveId);

  node1.begin(currentSlaveId, Serial1);
  node1.preTransmission(preTransmissionOne);
  node1.postTransmission(postTransmissionOne);

  uint8_t result = node1.writeSingleRegister(0x0101, newSlaveId);

  if (result == node1.ku8MBSuccess)
  {
    Serial.println("Success: Slave address changed!");
  }
  else
  {
    Serial.print("Error: ");
    Serial.println(result);
  }
}

void loop()
{
  // put your main code here, to run repeatedly:
}