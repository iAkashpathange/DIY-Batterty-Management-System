/*********
 OLED display interface for DIY BMS project  
*********/

#include <Wire.h>         // I2C interface
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//voltage sensor
int analogInput = A0; // Assign A1 for voltage reading
float vout = 0.0;
float vin = 0.0;
float Vcc = 4.68;
float R1 = 30000.0; // Value of resistor 
float R2 = 7500.0; //  Value of resistor
int value = 0;

void setup() 
{
  //volatge
   pinMode(analogInput, INPUT);
   Serial.begin(115200); //serial monitoring
   Serial.print("DC VOLTMETER\n");
   
  //oled
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))  // Address 0x3D for 128x64
  {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(500);
}

void loop() 
{
  //voltage calculation
  value = analogRead(analogInput);
  vout = (value * Vcc) / 1024.0; // see text
  vin = vout / (R2/(R1+R2)); 
  
  Serial.print("INPUT V= "); //serial monitoring
  Serial.println(vin,3);
  delay(500);

  display.clearDisplay(); // clear buffer

  //voltage reading
  display.setTextSize(1);             
  display.setTextColor(WHITE);        
  display.setCursor(0,10); 
  display.write(4);    // ASCII Symbol Ex: 4 = Diamond symbol          
  display.print("volatge = ");  display.print(vin, 4); display.print("v");
  display.display();  //print message
  delay(500); 
}
