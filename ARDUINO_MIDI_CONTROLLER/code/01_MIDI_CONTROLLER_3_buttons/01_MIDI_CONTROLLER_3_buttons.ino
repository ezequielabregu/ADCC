#include <MIDIUSB.h>
#include "ButtonsConfig.h"
//-------------------------------------------------------

int buttonState[N_BUTTONS] = { 0 }; // Variable for reading the pushbutton status
int buttonPState[N_BUTTONS] = { 0 }; // Variable for reading the pushbutton status

unsigned long lastDebounceTime[N_BUTTONS] = { 0 }; // Store the last time the LED was updated
unsigned long debounceTimer[N_BUTTONS] = { 0 }; // the debounce time; increase if the output flickers
int debounceDelay = 10; // the debounce time; increase if the output flickers

int BUTTON_CH = 0;

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}


void setup() {
  Serial.begin(9600);

  for (int i = 0; i < N_BUTTONS; i++){
    pinMode(buttonPin[i], INPUT_PULLUP);
    }
}

void loop() {
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