#include <DmxSimple.h>
#include "MIDIUSB.h"

#define dmxPin 3      // which pin is used to output to driver chip
#define dmxChannels   // number of DMX512 channels used
#define midiType 0x0B // which MIDI signal is to be interpretted as DMX value (default control change)

void setup() {
  Serial.begin(115200);         // Debug serial return
  DmxSimple.usePin(dmxPin);
  DmxSimple.maxChannel(dmxChannels);
}

midiEventPacket_t rx;

void loop() {
  do {
    rx = MidiUSB.read();
    if (rx.header != 0) {
      // for debug
      Serial.print(rx.header, HEX);
      Serial.print("-");
      Serial.print(rx.byte1, HEX);
      Serial.print("-");
      Serial.print(rx.byte2, DEC);
      Serial.print("-");
      Serial.println(rx.byte3, DEC);
      // DMX output
      if(rx.header == midiType){
        DmxSimple.write(rx.byte2,rx.byte3*2);
      }
    }
  } while (rx.header != 0);
}
