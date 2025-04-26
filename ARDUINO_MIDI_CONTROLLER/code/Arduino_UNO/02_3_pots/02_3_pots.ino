#include <MIDI.h>
#include "PotsConfig.h"

//-------------------------------------------------------
// Configuración de la librería MIDI
MIDI_CREATE_DEFAULT_INSTANCE();

//-------------------------------------------------------

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
}

void loop() {
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