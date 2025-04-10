#include "MIDIUSB.h"

const int N_POTS = 3; // Number of potentiometers

int potPin[N_POTS] = {A0, A1, A2}; // Analog pins for potentiometers
int potCC[N_POTS] = {1, 2, 3}; // MIDI CC numbers for each potentiometer

int potState[N_POTS]= {0};
int potPState[N_POTS] = {0};

int midiState[N_POTS]= {0};
int midiPState[N_POTS] = {0};

byte potThreshold = 3; // Threshold for detecting changes

//int potReading[N_POTS] = {0};

byte POT_CH = 0; // MIDI channel for the potentiometers

// Function to send MIDI control change messages (USBMIDI library)
void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

void setup() {
  //for debugging
  Serial.begin(9600);
}

void loop() {
  
  for (int i = 0; i < N_POTS; i++) {
    // read the pot value
    potState[i] = analogRead(potPin[i]);
    //map the pot value to MIDI range
    midiState[i] = constrain(map(potState[i], 0, 1023, 0, 128), 0, 127);
    // Calculate the change in potState
    int potVar = abs(potState[i] - potPState[i]);
    // Update only if the change exceeds the threshold
    if(potVar > potThreshold){
      // Send or print MIDI state only if it has changed
      if (midiState[i] != midiPState[i]) {

        controlChange(POT_CH, potCC[i], midiState[i]);
        MidiUSB.flush(); // Send the MIDI message

        // debbugging
        Serial.print("potState ");
        Serial.print(potState[i]);
        Serial.print(" ");
        Serial.print("midiState: ");
        Serial.println(midiState[i]);
        // Update the previous MIDI state
        midiPState[i] = midiState[i];
      }
      // Update the previous potState
      potPState[i] = potState[i];
    }
  }
}


