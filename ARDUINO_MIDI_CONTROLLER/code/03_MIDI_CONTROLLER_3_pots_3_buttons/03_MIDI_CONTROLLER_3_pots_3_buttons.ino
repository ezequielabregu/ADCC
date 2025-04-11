//--------------------------------------------------------
// MIDI Controller with Buttons and Potentiometers
// This code is a simple MIDI controller that uses buttons and potentiometers
#include <MIDIUSB.h>

//-------------------------------------------------------
// BUTTONS
const int N_BUTTONS = 3; // Number of buttons

int buttonPin[N_BUTTONS] = { 2, 3, 4}; // the number of the pushbutton pin
int buttonNote[N_BUTTONS] = { 36, 37, 38}; // the note number for each button

int buttonState[N_BUTTONS] = { 0 }; // Variable for reading the pushbutton status
int buttonPState[N_BUTTONS] = { 0 }; // Variable for reading the pushbutton status

unsigned long lastDebounceTime[N_BUTTONS] = { 0 }; // Store the last time the LED was updated
unsigned long debounceTimer[N_BUTTONS] = { 0 }; // the debounce time; increase if the output flickers
int debounceDelay = 10; // the debounce time; increase if the output flickers

int BUTTON_CH = 0;

//-------------------------------------------------------
// POTENTIOMETERS

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

// Functions to send MIDI messages (USBMIDI library)
void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}
//-------------------------------------------------------
void setup() {
  Serial.begin(9600);

  for (int i = 0; i < N_BUTTONS; i++){
    pinMode(buttonPin[i], INPUT_PULLUP);
    }
}

//-------------------------------------------------------
// Buttons function
void button() {
  for (int i = 0; i < N_BUTTONS; i++){
    buttonState[i] = digitalRead(buttonPin[i]);

    debounceTimer[i] = millis() - lastDebounceTime[i]; 

    if (debounceTimer[i] > debounceDelay) {
      if(buttonState[i] != buttonPState[i]) {
        lastDebounceTime[i] = millis();

        if (buttonState[i] == LOW) {
          noteOn(BUTTON_CH, buttonNote[i], 127);
          MidiUSB.flush();
          Serial.print("Button ");
          Serial.print(i);
          Serial.print(" is ");
          Serial.println("ON");
        }
      else {
        noteOn(BUTTON_CH, buttonNote[i], 0); 
        MidiUSB.flush();
        Serial.print("Button ");
        Serial.print(i);
        Serial.print(" is ");  
        Serial.println("OFF");
      }
      buttonPState[i] = buttonState[i];
      }
    }
  }
}

//-------------------------------------------------------
// Potentiometers function
void potentiometer() {
  
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

//-------------------------------------------------------
// Main loop
void loop() {
  button();
  potentiometer();
}