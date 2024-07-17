#define HELTEC_POWER_BUTTON   // must be before "#include <heltec_unofficial.h>"

// creates 'radio', 'display' and 'button' instances 
#include <heltec_unofficial.h>
#include <DHT22.h>
#include <Wire.h> 

#define DHTPIN 19
DHT22 dht22(DHTPIN); 

float t;
float h;
int sw1 = 39;
int led1 = 41;


void displayReadingsOnOled(float t,float h) {
  
 String tDisplay ="Temperature: " + (String)t +  "°C";
 String hDisplay = "Humidity: " + (String)h + "%";

 // Clear the OLED screen
 display.clear();
 // Prepare to display temperature
 display.drawString(0, 0, tDisplay);
 // Prepare to display humidity
 display.drawString(0, 12, hDisplay);
 // Display the readings
 display.display();
}

void drawCircle() {
  for (int16_t i = 0; i < display.getHeight(); i += 2) {
    display.drawCircle(display.getWidth() / 2, display.getHeight() / 2, i);
    display.display();
    heltec_delay(10);
  }
  heltec_delay(1000);
  display.clear();

  // This will draw the part of the circel in quadrant 1
  // Quadrants are numberd like this:
  //   0010 | 0001
  //  ------|-----
  //   0100 | 1000
  //
  display.drawCircleQuads(display.getWidth() / 2, display.getHeight() / 2, display.getHeight() / 4, 0b00000001);
  display.display();
  heltec_delay(200);
  display.drawCircleQuads(display.getWidth() / 2, display.getHeight() / 2, display.getHeight() / 4, 0b00000011);
  display.display();
  heltec_delay(200);
  display.drawCircleQuads(display.getWidth() / 2, display.getHeight() / 2, display.getHeight() / 4, 0b00000111);
  display.display();
  heltec_delay(200);
  display.drawCircleQuads(display.getWidth() / 2, display.getHeight() / 2, display.getHeight() / 4, 0b00001111);
  display.display();
}


void setup() {
  heltec_setup();
  display.init();
  Serial.begin(115200); //1bit=10µs
  Serial.println("\ntest capteur DTH22");
  pinMode(sw1, INPUT);
  pinMode(led1, OUTPUT);
  drawCircle();
}

void loop() {
  Serial.println(dht22.debug()); //optionnal

  t = dht22.getTemperature();
  h = dht22.getHumidity();

  if (dht22.getLastError() != dht22.OK) {
    Serial.print("last error :");
    Serial.println(dht22.getLastError());
    display.clear();
    // Prepare to display temperature
    display.drawString(0, 0, "Failed to Connected");
    // Prepare to display humidity
    display.drawString(0, 12, "DHT22");
    // Display the readings
    display.display();
  }

  Serial.print("h=");Serial.print(h,1);Serial.print("\t");
  Serial.print("t=");Serial.println(t,1);
  displayReadingsOnOled(t,h);
  Serial.println(t);
  Serial.println(h);
  //myButton.update();

  int sw1State = digitalRead(sw1);
  if(sw1State == 0){
    Serial.println("sw1: pressed");
    digitalWrite(led1, HIGH);
    display.fillCircle(38, 32, 5);
    display.drawString(80, 25, "ON ");
    display.display();
  }else{
    Serial.println("sw1: unpressed");
    digitalWrite(led1, LOW);
    display.drawCircle(38, 32, 5);
    display.drawString(80, 25, "OFF");
    display.display();
  }


  display.drawString(0, 25, "LED1:");
  display.drawCircle(38, 32, 5);

  display.drawString(50, 25, "SW1:");
  
  display.drawString(0, 38, "LED2:");
  display.fillCircle(38, 45, 5);

  display.drawString(50, 38, "SW2:");
  display.drawString(80, 38, "ON");
  
  display.display();
  delay(2000); //Collecting period should be : >1.7 second
}

