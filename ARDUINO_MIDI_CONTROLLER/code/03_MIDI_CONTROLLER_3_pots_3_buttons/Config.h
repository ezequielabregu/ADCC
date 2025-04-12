#ifndef CONFIG_H
#define CONFIG_H

// BUTTONS
const int N_BUTTONS = 3; // Number of buttons
int buttonPin[N_BUTTONS] = { 2, 3, 4}; // the number of the pushbutton pin
int buttonNote[N_BUTTONS] = { 36, 37, 38}; // the note number for each button

// POTS
const int N_POTS = 3; // Number of potentiometers
int potPin[N_POTS] = {A0, A1, A2}; // Analog pins for potentiometers
int potCC[N_POTS] = {1, 2, 3}; // MIDI CC numbers for each potentiometer

#endif