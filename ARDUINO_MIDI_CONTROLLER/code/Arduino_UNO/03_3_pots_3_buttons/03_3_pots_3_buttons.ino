//--------------------------------------------------------
// MIDI Controller with Buttons and Potentiometers
// This code is a simple MIDI controller that uses buttons and potentiometers
#include <MIDI.h>
#include "Config.h"

//-------------------------------------------------------
// Configuración de la librería MIDI
MIDI_CREATE_DEFAULT_INSTANCE();

//-------------------------------------------------------
// BUTTONS

int buttonState[N_BUTTONS] = { 0 }; // Estado actual de los botones
int buttonPState[N_BUTTONS] = { 0 }; // Estado previo de los botones

unsigned long lastDebounceTime[N_BUTTONS] = { 0 }; // Última vez que se actualizó el estado
unsigned long debounceTimer[N_BUTTONS] = { 0 }; // Temporizador para el debounce
int debounceDelay = 10; // Tiempo de debounce en milisegundos

//-------------------------------------------------------
// POTENTIOMETERS

int potState[N_POTS] = {0};       // Estado actual de los potenciómetros
int potPState[N_POTS] = {0};      // Estado previo de los potenciómetros

int midiState[N_POTS] = {0};      // Estado MIDI actual
int midiPState[N_POTS] = {0};     // Estado MIDI previo

byte potThreshold = 3;            // Umbral para detectar cambios

//-------------------------------------------------------

void setup() {
  // Inicializa la comunicación MIDI
  MIDI.begin(MIDI_CHANNEL_OMNI);
  Serial.begin(115200); // Para depuración

  // Configura los pines de los botones como entrada con resistencia pull-up
  for (int i = 0; i < N_BUTTONS; i++) {
    pinMode(buttonPin[i], INPUT_PULLUP);
  }
}

void loop() {
  handleButtons();
  handlePotentiometers();
}

//-------------------------------------------------------
// Función para manejar los botones
void handleButtons() {
  for (int i = 0; i < N_BUTTONS; i++) {
    buttonState[i] = digitalRead(buttonPin[i]); // Lee el estado del botón

    debounceTimer[i] = millis() - lastDebounceTime[i];

    if (debounceTimer[i] > debounceDelay) {
      if (buttonState[i] != buttonPState[i]) {
        lastDebounceTime[i] = millis();

        if (buttonState[i] == LOW) {
          // Enviar mensaje MIDI Note On
          MIDI.sendNoteOn(buttonNote[i], 127, BUTTON_CH);
/*           Serial.print("Button ");
          Serial.print(i);
          Serial.println(" ON"); */
        } else {
          // Enviar mensaje MIDI Note Off
          MIDI.sendNoteOff(buttonNote[i], 0, BUTTON_CH);
/*           Serial.print("Button ");
          Serial.print(i);
          Serial.println(" OFF"); */
        }
        buttonPState[i] = buttonState[i];
      }
    }
  }
}

//-------------------------------------------------------
// Función para manejar los potenciómetros
void handlePotentiometers() {
  for (int i = 0; i < N_POTS; i++) {
    // Leer el valor del potenciómetro
    potState[i] = analogRead(potPin[i]);
    // Mapear el valor del potenciómetro al rango MIDI (0-127)
    midiState[i] = constrain(map(potState[i], 0, 1023, 0, 127), 0, 127);
    // Calcular el cambio en el estado del potenciómetro
    int potVar = abs(potState[i] - potPState[i]);

    // Actualizar solo si el cambio excede el umbral
    if (potVar > potThreshold) {
      // Enviar mensaje MIDI solo si el estado MIDI ha cambiado
      if (midiState[i] != midiPState[i]) {
        // Enviar mensaje MIDI Control Change
        MIDI.sendControlChange(potCC[i], midiState[i], POT_CH);

        // Depuración
/*         Serial.print("Pot ");
        Serial.print(i);
        Serial.print(" State: ");
        Serial.print(potState[i]);
        Serial.print(" MIDI State: ");
        Serial.println(midiState[i]); */

        // Actualizar el estado MIDI previo
        midiPState[i] = midiState[i];
      }
      // Actualizar el estado previo del potenciómetro
      potPState[i] = potState[i];
    }
  }
}