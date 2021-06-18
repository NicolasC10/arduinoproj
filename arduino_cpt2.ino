/*
Nicolas Cosentino
Arduino CPT
TER4M1-01
Mr. Kolch
2021-06-18

Data Processor Code (Arduino 2)
*/

//importing libraries
//library for LCD screen
#include<LiquidCrystal.h>
//library for arduino interconnect
#include <SoftwareSerial.h>
//defining range finder trigger and echo pins
#define trigPin 10
#define echoPin 13

//defining LCD parameters for library
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
//defining the interconnect pins
SoftwareSerial link(7, 6); // Rx Tx

//setup
void setup()
{
  	link.begin(9600); //setup software serial
  	Serial.begin (9600); //setup serial monitor
  	//pinmodes
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
    //initializes LCD resolution
 	lcd.begin(16, 2); 
}

//loop
void loop()
{
    //range finder algorithm
  		//distance and duration vars
  	float duration, distance;
  		//outputs 8 microsecond pulse
	digitalWrite(trigPin, LOW); 
	delayMicroseconds(2);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);
 		//waits for echo on pulse
	duration = pulseIn(echoPin, HIGH); 
  		//calculates distance
  	distance = (duration / 2) * 0.0344;
 
  	//
  	//serial debugging processing
	if (distance >= 335 || distance <= 2)//when distance is out of detection range
    {
      //outputs out of range text to serial monitor
		Serial.print("Distance = ");
		Serial.println("Out of range");
	}
	else //when distance is within detection range
    {
      //outputs distance to serial monitor
		Serial.print("Distance = ");
		Serial.print(distance);
		Serial.println(" cm");
		delay(50);
	}
  	//
  	//
  
  	//LCD output processing
  	if (distance >= 335 || distance <=5)//out-of-range method
  	{
    	lcd.setCursor(1,1); //sets cursor location on LCD
  		lcd.print("Out of Range"); //outputs text below distance value
  	}
  	else if (distance <= 300 && distance >=125)//300-125cm
  	{
    	lcd.setCursor(1,1);          
  		lcd.print("Safe        ");
  	}
  	else if (distance <= 125 && distance >=50)//125-50cm
  	{
    	lcd.setCursor(1,1);          
  		lcd.print("Moderate    ");
  	}
  	else if (distance <= 50 && distance >= 3)//<50cm
  	{
    	lcd.setCursor(1,1);          
  		lcd.print("Close       ");
  	}
  	
  	lcd.setCursor(1,0); //sets cursor location on LCD      
  	lcd.print(distance); //outputs ditance data to LCD
  
  	link.println(distance); //send data to output processor arduino
  	delay(100);
}
