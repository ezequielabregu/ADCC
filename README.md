# Implementación de un Controlador MIDI USB con Arduino (chip ATmega32U4)

Este documento describe paso a paso cómo implementar un controlador MIDI utilizando una placa Arduino basada en el chip ATmega32U4 (Leonardo, Micro o Pro Micro).
Este controlador MIDI puede enviar mensajes MIDI a través de USB, permitiendo controlar software musical o dispositivos compatibles con MIDI.

El chip ATmega32u4 es ideal para el desarrollo de dispositivos MIDI USB debido a su capacidad integrada de comunicación USB nativa, lo que elimina la necesidad de chips adicionales para la interfaz USB. Esto permite que las placas basadas en este chip, como Arduino Leonardo, Micro y Pro Micro, sean reconocidas directamente como dispositivos MIDI por el sistema operativo, simplificando la implementación. Además, su soporte para múltiples pines analógicos y digitales facilita la conexión de potenciómetros, botones y otros componentes, mientras que su compatibilidad con el entorno Arduino IDE y librerías como MIDIUSB agiliza el desarrollo y personalización del código.

## Requisitos

### Hardware
1. **Placa Arduino**: Leonardo, Micro o Pro Micro (chip ATmega32U4).
2. **Potenciómetros lineales de 10k ohms (B10k)**: Dependiendo del modelo que elijas (1, 3 o más).
3. **Botones pulsadores sin retención**: Según el modelo (1, 3 o más).
4. **Cables de conexión (tipo Dupont)**: Para realizar las conexiones entre los componentes y la placa.
5. **Protoboard**: Opcional, para facilitar las conexiones.
6. **Cable USB**: Para conectar la placa Arduino al ordenador.

### Software
1. **Arduino IDE**: Descárgalo desde [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software).
2. **Librería MIDIUSB** (Gary Grewal): Necesaria para enviar mensajes MIDI a través de USB.

---

## Paso 1: Instalación del Entorno de Desarrollo

1. Descarga e instala el **Arduino IDE** desde el enlace proporcionado.
2. Abre el Arduino IDE y ve a **Herramientas > Placa**. Selecciona tu placa Arduino (Leonardo, Micro o Pro Micro). Habitualmente seleccionaremos *Arduino Leonardo*.
3. Instala la librería MIDIUSB:
   - Ve a **Herramientas > Administrar bibliotecas**.
   - Busca "MIDIUSB" en el cuadro de búsqueda.
   - Haz clic en "Instalar".

---

## Paso 2: Esquema de Conexión

### Potenciómetros
Los potenciómetros se conectan a los pines analógicos de la placa Arduino. Cada potenciómetro tiene tres pines:
- **Pin central**: Conéctalo al pin analógico correspondiente (A0, A1, A2, etc.).
- **Pin lateral 1**: Conéctalo a GND.
- **Pin lateral 2**: Conéctalo a 5V.

### Botones
Los botones se conectan a los pines digitales de la placa Arduino. Cada botón tiene dos pines:
- **Un pin**: Conéctalo al pin digital correspondiente (2, 3, 4, etc.).
- **Otro pin**: Conéctalo a GND.

## Esquema de Conexión Detallado

A continuación, se muestran los esquemas de conexión para diferentes configuraciones de potenciómetros y botones.

### Esquema básico con 1 potenciómetro y 1 botón
![Esquema básico con 1 potenciómetro y 1 botón](/ARDUINO_MIDI_CONTROLLER/images/1%20Pot-1%20Button.png)

### Esquema con 3 potenciómetros y 3 botones
![Esquema con 3 potenciómetros y 3 botones](/ARDUINO_MIDI_CONTROLLER/images/3%20Pot-3%20Button.png)

---

## Pinout del Arduino Pro Micro

El siguiente esquema muestra el pinout del Arduino Pro Micro, útil para identificar los pines analógicos y digitales necesarios para las conexiones.

![Pinout del Arduino Pro Micro](/ARDUINO_MIDI_CONTROLLER/images/arduino_ProMicro_pinout.jpg)

Utiliza este esquema como referencia para conectar correctamente los potenciómetros y botones a los pines de la placa.

---

## Paso 3: Carga del Código

1. Abre el archivo de código correspondiente en el Arduino IDE:
   - Para un controlador con 3 potenciómetros: `MIDI_CONTROLLER_(3_pots).ino`.
   - Para un controlador con 3 botones: `MIDI_CONTROLLER_(3_buttons).ino`.
   - Para un controlador con 3 potenciómetros y 3 botones: `MIDI_CONTROLLER_(3_pots_3_buttons).ino`.
2. Conecta tu placa Arduino al ordenador mediante un cable USB.
3. Selecciona el puerto USB de tu placa en **Herramientas > Puerto**. Habitualmente seleccionaremos *Arduino Leonardo*.
4. Haz clic en el botón de **Subir** para cargar el código en la placa.

---

## Paso 4: Pruebas y Depuración

1. Abre el **Monitor Serial** (menú *Herramientas/Monitor Serial*) en el Arduino IDE para verificar los mensajes de depuración.
2. Gira los potenciómetros o presiona los botones y observa los mensajes enviados al monitor serial.
3. Conecta tu Arduino a un software MIDI (MIDI monitor, Ableton Live, FL Studio o cualquier otro compatible) para probar el envío de mensajes MIDI.

---

## Paso 5: Personalización

Puedes personalizar el código para adaptarlo a tus necesidades:
- Cambia los pines asignados a los potenciómetros o botones.
- Modifica los números de Control Change (CC) o notas MIDI asignadas.
- Ajusta el umbral de sensibilidad (`potThreshold`) para los potenciómetros.

---
## Recursos Adicionales

- [Documentación oficial de Arduino](https://www.arduino.cc/).
- [Referencia de la librería MIDIUSB](https://www.arduino.cc/reference/en/libraries/midiusb/).

