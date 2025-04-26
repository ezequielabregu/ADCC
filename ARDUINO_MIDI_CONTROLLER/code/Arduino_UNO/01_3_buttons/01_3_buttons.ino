#include <MIDI.h>
#include "ButtonsConfig.h"

//-------------------------------------------------------
// Configuración de la librería MIDI
MIDI_CREATE_DEFAULT_INSTANCE();

//-------------------------------------------------------

int buttonState[N_BUTTONS] = { 0 }; // Estado actual de los botones
int buttonPState[N_BUTTONS] = { 0 }; // Estado previo de los botones

unsigned long lastDebounceTime[N_BUTTONS] = { 0 }; // Última vez que se actualizó el estado
unsigned long debounceTimer[N_BUTTONS] = { 0 }; // Temporizador para el debounce
int debounceDelay = 10; // Tiempo de debounce en milisegundos

//-------------------------------------------------------

void setup() {
  // Inicializa la comunicación MIDI
  MIDI.begin(MIDI_CHANNEL_OMNI);
  Serial.begin(115200);

  // Configura los pines de los botones como entrada con resistencia pull-up
  for (int i = 0; i < N_BUTTONS; i++) {
    pinMode(buttonPin[i], INPUT_PULLUP);
  }
}

void loop() {
  for (int i = 0; i < N_BUTTONS; i++) {
    buttonState[i] = digitalRead(buttonPin[i]); // Lee el estado del botón

    debounceTimer[i] = millis() - lastDebounceTime[i];

    if (debounceTimer[i] > debounceDelay) {
      if (buttonState[i] != buttonPState[i]) {
        lastDebounceTime[i] = millis();

        if (buttonState[i] == LOW) {
          // Enviar mensaje MIDI Note On
          MIDI.sendNoteOn(buttonNote[i], 127, BUTTON_CH);
          //Serial.print("Button ");
          //Serial.print(i);
          //Serial.println(" ON");
        } else {
          // Enviar mensaje MIDI Note Off
          MIDI.sendNoteOff(buttonNote[i], 0, BUTTON_CH);
          //Serial.print("Button ");
          //Serial.print(i);
          //Serial.println(" OFF");
        }
        buttonPState[i] = buttonState[i];
      }
    }
  }
}