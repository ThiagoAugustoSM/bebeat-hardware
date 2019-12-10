int LED = 4;

#define AUDIO_INPUT_PIN A0

#ifndef START
#define START 0
#endif

#ifndef START_RECORDING
#define START_RECORDING 1
#endif

#ifndef STOP_RECORDING
#define STOP_RECORDING 2
#endif

//#define START 0
//#define START_RECORDING 1
//#define STOP_RECORDING 2


int audio_input = 0;
int STATE = START_RECORDING;

char audio_input_string[4];
char data_received;

unsigned int audio;

class DataReceived{
  public: 
    char turnOnLed = '1';
    char startRecording = '2';
    char stopRecording = '3';
};

DataReceived data;

int audio_string_length = 4;

void setup() {
 pinMode(LED, OUTPUT);
 Serial.begin(115200); /* Define baud rate for serial communication */
  
//  attachInterrupt(digitalPinToInterrupt(AUDIO_INPUT_PIN), handleAudio, CHANGE);
}

void loop() {

  audio_input = analogRead(AUDIO_INPUT_PIN); // analog values from 0 to 1023
  
  if(Serial.available() > 0){ /* If data is available on serial port */
    data_received = Serial.read();  /* Data received from bluetooth */
  }else{
    data_received = '0';
  }
  
  if(STATE == START){
    if (data_received == '0'){
    } else if (data_received == data.turnOnLed){
      digitalWrite(LED, HIGH);
      Serial.write("LED turned ON\n");        
    } else if (data_received == data.startRecording){
      STATE = START_RECORDING;
      digitalWrite(LED, LOW);
      Serial.write("LED turned OFF\n");
    } else if (data_received == data.stopRecording){
      STATE = START;
    } else{
      Serial.write("Select either 1 or 2\n");
    }
  } else if (STATE == START_RECORDING){
    memset(audio_input_string, 0, sizeof(audio_input_string)); // Cleaning the previous string input value
    itoa(audio_input, audio_input_string, 10);
    Serial.write(audio_input_string, audio_string_length);
    Serial.write("\n");

    if (data_received == '3'){
      STATE = STOP_RECORDING;
    }
  } else if (STATE == STOP_RECORDING){
    STATE = START;
  }
}
