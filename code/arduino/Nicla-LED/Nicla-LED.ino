#include "Nicla_System.h"
using namespace nicla;


void setup() {
  // put your setup code here, to run once:
begin();
leds.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
int blue = 128;
  int green = 73;
  int red = 255;

  leds.setColor(blue, green, red);
  delay(1000);
  leds.setColor(off);
  delay(1000); 
}
