// On ESP8266:
// At 80MHz runs up 57600ps, and at 160MHz CPU frequency up to 115200bps with only negligible errors.
// Connect pin 12 to 14.

#include <SoftwareSerial.h>

#if defined(ESP8266) && !defined(D5)
#define D2 (4)
#define D3 (0)
#define D4 (2)
#define D5 (14)
#define D6 (12)
#define D7 (13)
#define D8 (15)
#endif

#ifdef ESP32
#define BAUD_RATE 115200
#else
#define BAUD_RATE 115200
#endif

// Reminder: the buffer size optimizations here, in particular the isrBufSize that only accommodates
// a single 8N1 word, are on the basis that any char written to the loopback SoftwareSerial adapter gets read
// before another write is performed. Block writes with a size greater than 1 would usually fail. 
SoftwareSerial blueetoothSer(D2, D3);


char c = ' ';
boolean NL = true;

void setup() {
  Serial.begin(BAUD_RATE);
  blueetoothSer.begin(BAUD_RATE);

  Serial.println("\nSoftware serial test started");

  
}

void loop() {
// Read from the Bluetooth module and send to the Arduino Serial Monitor
    if (blueetoothSer.available())
    {
        c = blueetoothSer.read();
        Serial.write(c);
    }
    
      
  
    // Read from the Serial Monitor and send to the Bluetooth module
    if (Serial.available())
    {
        c = Serial.read();
        blueetoothSer.write(c);   
        
        // Echo the user input to the main window. The ">" character indicates the user entered text.
        if (NL) { Serial.print(">");  NL = false; }
        Serial.write(c);
        if (c==10) { NL = true; }
    }


}
