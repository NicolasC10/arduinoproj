/*
Nicolas Cosentino
Arduino CPT
TER4M1-01
Mr. Kolch
2021-06-18
*/

//importing libraries
//library for neopixel LEDs
#include <Adafruit_NeoPixel.h>
//library for arduino interconnect
#include <SoftwareSerial.h>

//defining the pin that the neopixels are connected to
#define LED_PIN    5
//defining the buzzer pin
#define buzzPin 4

//number of LEDs used
#define LED_COUNT 19

//declaring the neopixel LEDs as an object
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)

//declaring 32-bit colour variables
uint32_t yellow = strip.Color(255, 255, 0);
uint32_t green = strip.Color(0, 255, 0);
uint32_t red = strip.Color(255, 0, 0);
uint32_t black = strip.Color(0, 0, 0);

//declaring comdata var
String comdata = "";

//defining the interconnect pins
SoftwareSerial link(7, 6); // Rx, Tx


//light and buzz pattern methods
void oor() //out-of-range method
{
  strip.clear(); //clears previous colour settings
  strip.setPixelColor(17, 0, 0, 255); //setting individual pixel colours using (LEDnumber, r, g, b)
  strip.setPixelColor(15, 0, 255, 0);
  strip.setPixelColor(13, 255, 0, 0);
  strip.setPixelColor(11, 0, 255, 255);
  strip.setPixelColor(9, 255, 0, 255);
  strip.setPixelColor(7, 255, 255, 0);
  strip.show(); //pushes data to LEDs for display at once
}
void far() //300-125cm
{
  strip.clear();
  strip.fill(green, 7, 18); //filling a certain part of the strip with one command
  strip.setPixelColor(0, 0, 255, 0);
  strip.show();
  delay(500); //delay for 0.5 seconds
  strip.fill(black, 0, 19); //show 'black' for a flashing/pulsing effect
  strip.show();
  delay(500);
}
void medium() //125-50cm
{
  strip.clear();
  strip.fill(yellow, 0, 7); //lights middle ring first
  strip.show();
  delay(500);
  strip.clear();
  strip.fill(yellow, 7, 18); //lights outer ring
  strip.show();
  delay(500);
  strip.fill(black, 0, 19); //turns off both rings
}
void close() //<50cm
{
  strip.clear();
  strip.fill(red, 0, 19); //lights both rings
  tone(buzzPin, 261); //turns on Lo-Tone buzzer
  strip.show();
  delay(250);
  strip.fill(black, 7, 19); //'flashes' outer ring
  tone(buzzPin, 415); //turns on Hi-Tone buzzer
  strip.show();
  delay(250);
  strip.fill(red, 7, 19);
  noTone(buzzPin); //turns off buzzer
  strip.show();
  delay(250);
  strip.fill(black, 0, 19);
  strip.show();
  delay(250);
}

//setup
void setup() {
  link.begin(9600); //setup software serial
  Serial.begin (9600); //setup serial monitor
  //pin modes
  pinMode(LED_PIN, OUTPUT);
  pinMode(buzzPin, OUTPUT);
  //initializes NeoPixel strip
  strip.begin();
  strip.show();
}

//loop
void loop()
{
  //resets comdata
  comdata = "";
  while (link.available() > 0) //as valid bytes are received, read input
		{
			comdata += char(link.read()); //reads bytes and amendsto comdata
			delay(2);
		}
  double distance = comdata.toDouble(); //converts comdata to distance var
  Serial.println(distance); //prints distance to monitor (debugging)
  delay(10);
  
  //processes distance value
  if (distance >= 335 || distance <=5) //distance is outside of operating values
  {
    oor(); //calls out of range method
  }
  else if (distance <= 300 && distance >=125) //distance is between 125 and 300cm
  {
    far(); //calls far method
  }
  else if (distance <= 125 && distance >=50) //distance is between 50 and 125cm
  {
    medium(); //calls moderate/medium method
  }
  else if (distance <= 50 && distance >= 5) //distance is between 5 and 50cm
  {
    close(); //calls close method
  }
  
}