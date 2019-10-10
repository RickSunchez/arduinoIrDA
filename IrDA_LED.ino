#include <ir_Lego_PF_BitStreamEncoder.h>
#include <IRremoteInt.h>
#include <boarddefs.h>
#include <IRremote.h>

int LED_lightness = 0;
int LED_pin = 9;
int case2_light = 0;

IRrecv irrecv(2);
decode_results results;

String buttonCode;
int mode = 0;

void setup() {
  Serial.begin(9600); // выставляем скорость COM порта
  irrecv.enableIRIn(); // запускаем прием

  pinMode(LED_pin, OUTPUT);
}

void loop() {
  if ( irrecv.decode( &results )) {
    String valueResieve = String(results.value, HEX);
    //if button is pressed
    if (valueResieve != "ffffffff") {
      buttonCode = valueResieve;
      }

    //ligntness up
    if (buttonCode == "ffa857") {
      LED_lightness+=10;
      if (LED_lightness >= 250) {LED_lightness = 250;}
      }
    //ligntness down
    if (buttonCode == "ffe01f") {
      LED_lightness-=10;
      if (LED_lightness <= 0) {LED_lightness = 0;}
      }
    //light ON/OFF
    if (buttonCode == "ffc23d") {
      if (LED_lightness == 0) {
          LED_lightness = 255;
        }
      else {
        LED_lightness = 0;
        }
      }
    //numeric buttons
    if (buttonCode == "ff6897") {mode = 0;}
    if (buttonCode == "ff30cf") {mode = 1;}
    if (buttonCode == "ff18e7") {mode = 2;}
    
    Serial.println( buttonCode );

    delay(100);
    irrecv.resume();
  }

  switch (mode) {
    case 0:
      analogWrite(LED_pin, LED_lightness);
      break;
    case 1:
      analogWrite(LED_pin, 0);
      delay(100);
      analogWrite(LED_pin, LED_lightness);
      delay(100);
      break;
    case 2:
      analogWrite(LED_pin, case2_light);
      case2_light += 10;
      delay(50);
    }
}

/*
 * ffffffff - buttonDown
ffa857 - VOL+
ffe01f - VOL-
ff906f - EQ
ffc23d - PLAY/PAUSE

ff6897 - 0
ff30cf - 1
ff18e7 - 2
*/
