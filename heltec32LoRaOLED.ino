
#include "HT_SSD1306Wire.h"
#include "Arduino.h"

//rotate only for GEOMETRY_128_64
static SSD1306Wire  display(0x3c, 500000, SDA_OLED, SCL_OLED, GEOMETRY_128_64, RST_OLED); // addr , freq , i2c group , resolution , rst

void VextON(void)
{
  pinMode(Vext,OUTPUT);
  digitalWrite(Vext, LOW);
}

void VextOFF(void) //Vext default OFF
{
  pinMode(Vext,OUTPUT);
  digitalWrite(Vext, HIGH);
}

void setup() {

  VextON();
  delay(100);
  display.init();
  display.clear();
  display.display();
  display.setContrast(255);
  display.setFont(ArialMT_Plain_10); 
  display.drawString(0, 0, "ROTATE_0");
  display.drawString(0, 10, "ROTATE_90");
  display.drawString(0, 20, "ROTATE_180");
  display.drawString(0, 30, "ROTATE_270");
  display.display();
  delay(2000);
}

void loop() { }