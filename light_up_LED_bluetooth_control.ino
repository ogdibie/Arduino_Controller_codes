
/*
  Dibie Ogheneruona
  Turn on LED to test control
 
 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.
 
 The circuit: 
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)
 
 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts, 
 so only the following can be used for RX: 
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69
 
 Not all pins on the Leonardo support change interrupts, 
 so only the following can be used for RX: 
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).
 
 */
 
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

char incomingByte;  // incoming data
int  LED = 12;      // LED pin

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Press 1 for LED ON or 0 for LED OFF");
  pinMode(LED, OUTPUT);
}
void loop() {
  if (mySerial.available() > 0) {  // if the data came
    incomingByte = mySerial.read(); // read byte
    if(incomingByte == '0') {
       digitalWrite(LED, LOW);  // if 1, switch LED Off
       mySerial.println("LED OFF. Press turn on to LED ON!");  // print message to microcontroller
    }
    if(incomingByte == '1') {
       digitalWrite(LED, HIGH); // if 0, switch LED on
       mySerial.println("LED ON. Press turn off to LED OFF!");
    }
  }
}
