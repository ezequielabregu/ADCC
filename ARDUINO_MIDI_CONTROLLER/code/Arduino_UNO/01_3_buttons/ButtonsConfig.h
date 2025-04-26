#ifndef BUTTON_CONFIG_H
#define BUTTON_CONFIG_H

//SETUP
// Number of buttons
const int N_BUTTONS = 3; 
// Number of the Arduino pins for the buttons
int buttonPin[N_BUTTONS] = { 2, 3, 4};
// the MIDI note number for each button 
int buttonNote[N_BUTTONS] = { 36, 37, 38};
// the MIDI channel for each button
int BUTTON_CH = 1; 
//-------------------------------------
#endif