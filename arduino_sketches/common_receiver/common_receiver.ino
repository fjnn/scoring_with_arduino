//Receiver coding for the nrf24L01 radio transceiver.
//https://www.electroniclinic.com/
// Download Libraries:
//https://www.electroniclinic.com/arduino-libraries-download-and-projects-they-are-used-in-project-codes/
//editted by Gizem


#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define CE_PIN 9
#define CSN_PIN 10

#define TX_AMOUNT 2

struct PayloadStruct
{
  unsigned long nodeID;
  unsigned long payloadID;
};
PayloadStruct payload;

const uint64_t address[6] = {0x7878787878LL,
                       0xB3B4B5B6F1LL,
                       0xB3B4B5B6CDLL,
                       0xB3B4B5B6A3LL,
                       0xB3B4B5B60FLL,
                       0xB3B4B5B605LL
                      };

RF24 radio(CE_PIN, CSN_PIN);

void setup()
{
  Serial.begin(9600);
  while (!Serial) {
    // some boards need to wait to ensure access to serial over USB
  }
  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    while (1) {} // hold in infinite loop
  }
  Serial.println("NRF common receiver is set");
  radio.setPALevel(RF24_PA_LOW); // RF24_PA_MAX is default.
  radio.setPayloadSize(sizeof(payload));
  for (uint8_t i = 0; i < TX_AMOUNT; ++i)
      radio.openReadingPipe(i, address[i]);

  radio.startListening(); // put radio in RX mode

  // For debugging info
  // printf_begin();             // needed only once for printing details
  // radio.printDetails();       // (smaller) function that prints raw register values
  // radio.printPrettyDetails(); // (larger) function that prints human readable data

}

void loop() {
  uint8_t pipe;
    if (radio.available(&pipe)) {             // is there a payload? get the pipe number that recieved it
      uint8_t bytes = radio.getPayloadSize(); // get the size of the payload
      radio.read(&payload, bytes);            // fetch payload from FIFO
      Serial.print(F("Received "));
      Serial.print(bytes);                    // print the size of the payload
      Serial.print(F(" bytes on pipe "));
      Serial.print(pipe);                     // print the pipe number
      Serial.print(F(" from node "));
      Serial.print(payload.nodeID);           // print the payload's origin
      Serial.print(F(". PayloadID: "));
      Serial.println(payload.payloadID);      // print the payload's number
    }
}
