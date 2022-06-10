//Transmitter1 coding for the nrf24L01 radio transceiver.
//https://www.electroniclinic.com/
//editted by Gizem

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define CE_PIN 9
#define CSN_PIN 10

struct PayloadStruct
{
  unsigned long nodeID;
  unsigned long payloadID;
};
PayloadStruct payload;


const uint64_t address = 0xB3B4B5B6CDLL;

RF24 radio(CE_PIN, CSN_PIN);
int data[2]; // depending on the number of sensors you want to use
const uint8_t button_pin = 2; //vresistor define as interrupt later
int button_val;

void setup() {
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

  payload.nodeID = address;
  payload.payloadID = 0;

  radio.stopListening(); // put radio in TX mode
  radio.openWritingPipe(address);

  // For debugging info
  // printf_begin();             // needed only once for printing details
  // radio.printDetails();       // (smaller) function that prints raw register values
  // radio.printPrettyDetails(); // (larger) function that prints human readable data

  pinMode(button_pin, INPUT);
}

void loop() {
  // read the value at analog input
  button_val = digitalRead(button_pin);

  unsigned long start_timer = micros();                    // start the timer
  bool report = radio.write(&payload, sizeof(payload));    // transmit & save the report
  unsigned long end_timer = micros();  

  if (report) {
      // payload was delivered

      Serial.print(F("Transmission of payloadID "));
      Serial.print(payload.payloadID);                       // print payloadID
      Serial.print(F(" as node "));
      Serial.print(payload.nodeID);                          // print nodeID
      Serial.print(F(" successful!"));
      Serial.print(F(" Time to transmit: "));
      Serial.print(end_timer - start_timer);                 // print the timer result
      Serial.println(F(" us"));
    } else {
      Serial.println(F("Transmission failed or timed out")); // payload was not delivered
    }
    payload.payloadID++;                                     // increment payload number

    // to make this example readable in the serial monitor
    delay(1000); // slow transmissions down by 1 second


  //  if(button_val)
  //    Serial.println("pressed-1");
  //
  //  data[0] = 231;  // code to identify the transmitter.
  //  data[1] = button_val;
  //  radio.write( data, sizeof(data) );
}
