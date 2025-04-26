#ifndef POTS_CONFIG_H
#define POTS_CONFIG_H

//-------------------------------------------------------
//SETUP
// Number of potentiometers
const int N_POTS = 3; 
// Arduino analog pins for potentiometers
int potPin[N_POTS] = {A0, A1, A2};
// MIDI CC numbers for each potentiometer 
int potCC[N_POTS] = {1, 2, 3};
// MIDI channel for the potentiometers 
byte POT_CH = 1; 
//-------------------------------------------------------
#endif