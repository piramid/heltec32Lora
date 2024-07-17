#define HELTEC_POWER_BUTTON   // must be before "#include <heltec_unofficial.h>"

// creates 'radio', 'display' and 'button' instances 
#include <heltec_unofficial.h>
#include <DHT22.h>
#include <Wire.h> 

#define Button1   39
#define Button2   40
#define LED1     41
#define LED2     42

#define DHTPIN 19
DHT22 dht22(DHTPIN); 

float t;
float h;
int stateLED1;
int stateLED2;

 
void IRAM_ATTR isr1()
{
  // Toggle The LED
  digitalWrite(LED1, !digitalRead(LED1));
    
}

void IRAM_ATTR isr2()
{
  // Toggle The LED
  digitalWrite(LED2, !digitalRead(LED2));
}

void displayReadingsOnOled(float t,float h) {
  String tDisplay ="Temperature: " + (String)t +  "°C";
  String hDisplay = "Humidity: " + (String)h + "%";

  stateLED1 = digitalRead(LED1);
  stateLED2 = digitalRead(LED2);
  
  // Clear the OLED screen
  display.clear();
  // Prepare to display temperature
  display.drawString(0, 0, tDisplay);
  // Prepare to display humidity
  display.drawString(0, 12, hDisplay);
  // Display the readings
  if(stateLED1 == 1){
    display.drawString(0, 25, "LED1:");
    display.fillCircle(38, 32, 5);
    display.drawString(50, 25, "SW1:");
    display.drawString(80, 25, "ON ");
    //display.display();
  }else{
    display.drawString(0, 25, "LED1:");
    display.drawCircle(38, 32, 5);
    display.drawString(50, 25, "SW1:");
    display.drawString(80, 25, "OFF ");
  }

  if(stateLED2 == 1){
    display.drawString(0, 38, "LED2:");
    display.fillCircle(38, 45, 5);
    display.drawString(50, 38, "SW2:");
    display.drawString(80, 38, "ON");
  }else{
    display.drawString(0, 38, "LED2:");
    display.drawCircle(38, 45, 5);
    display.drawString(50, 38, "SW2:");
    display.drawString(80, 38, "OFF");
  }
  display.display();
}
 
void setup()
{
  heltec_setup();
  display.init();
  Serial.begin(115200); //1bit=10µs
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(Button1, INPUT);
  pinMode(Button2, INPUT);  

  attachInterrupt(Button1, isr1, RISING); // interrupt on rising edge
  attachInterrupt(Button2, isr2, RISING); // interrupt on rising edge
}
 
void loop()
{
  // digitalWrite(LED2, HIGH);
  // delay(1000);
  // digitalWrite(LED2, LOW);
  // delay(1000);


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

}