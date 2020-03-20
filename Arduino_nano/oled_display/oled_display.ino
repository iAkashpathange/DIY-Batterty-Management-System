/*********
 OLED display interface for DIY BMS project  
*********/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//voltage sensor
int analogInput = A1; // Assign A1 for voltage reading
float vout = 0.0;
float vin = 0.0;
float R1 = 30000.0; // Value of resistor 
float R2 = 8050.0; //  Value of resistor
int value = 0;

//SOC
float mesV = 0.0; //a variable with a decimal point to hold battery voltage
int perC = 0;     //a variable with no decimal point to hold battery percentage

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
  delay(2000);
}

void loop() 
{
  //voltage calculation
  value = analogRead(analogInput);
  vout = (value * 5.0) / 1024.0; // see text
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

  //SOC
  mesV = vin; //use voltage value

  //comparision for SOC %
  if (mesV < 3.4){                              //battery @ 3.5V or less
   perC = 0;                                   //% = 0
  }
 
  if(mesV > 3.5  && mesV < 3.7){                 //battery @ 3.6V
   perC = 2;
  }
 
  if (mesV > 3.6 && mesV < 3.8){                //battery @ 3.7V
   perC = 12;
  }
 
  if (mesV > 3.7 && mesV <3.9){                 //battery @ 3.8V
   perC = 42;
  }
 
  if (mesV > 3.8 && mesV < 4.0){                //battery @ 3.9V
   perC = 62;
  }
 
  if (mesV > 3.9 && mesV < 4.1){                //battery @ 4.0V
   perC = 79;
  }
 
  if (mesV > 4.0 && mesV < 4.2){                //battery @ 4.1V
   perC = 81;
  }
 
  if (mesV > 4.19){                             //battery @ 4.2V 
  perC = 100;                                   //%=100
  }
  
  display.setTextSize(1);             
  display.setTextColor(WHITE);        
  display.setCursor(0,0);  
  display.write(4);           
  display.print("SOC = "); display.print(perC); display.print("%");
  
  display.display();  //print message
  delay(500); 
}
