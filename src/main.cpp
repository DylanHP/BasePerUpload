#define F_CPU 20000000L
#include <avr/wdt.h>
#include <global.h>
#include <ATmega4809.h>  // definizioni specifiche del micro in uso

void setup() {
  wdt_enable(WDTO_500MS);
  Serial3.pins(12, 13);  // RX3, TX3
  Serial3.begin(115200);
}

void loop() { Serial3.println(millis()); }
