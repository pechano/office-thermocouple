//LCD
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; //problem med samme pins her (linje 11)

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//sensor
#include "max6675.h"
#include <SPI.h>

int soPin = 8;// SO=Serial Out
int csPin = 9;// CS = chip select CS pin
int sckPin = 10;// SCK = Serial Clock pin
double lowestTemp = 25;
//MAX6675 Module(sckPin, csPin, soPin);// create instance object of MAX6675

MAX6675 thermocouple;



//Alt dette er global scope!


int setupPin = 13; //<--- jeg skal finde en ledig digitalpin som kan være input

bool cycle = true;
bool cycle2 = true;
bool firstCycle = true;
int setupState = 0;

long minutesPassed = 0;

long int minute = 0;
long int hour   = 0;
long int offset = 0; //der er 1440 minutter på et døgn. Det tager vi udgangspunkt i.
long int lastTime = 0;	
long int lastTime2 = 0;	

String minuteString = "";
String hourString = "";	
String timeString = "";
String lowestTime = "";

bool colon = false;

long minuteOffset = offset % 60;
long hourOffset = offset - minuteOffset;

String TC = "";
double t = 0.0;
double tempOffset = 0.0;

void setup() {
	
thermocouple.begin(sckPin, csPin, soPin);

	
pinMode(setupPin,INPUT);	

Serial.begin(9600);
Serial.println("CHT11 initiated");
//  dht.begin();
  
  
	pinMode(d6, OUTPUT);//d6 er kontrast	

	pinMode(A0, INPUT);

  lcd.begin(16, 2);
	analogWrite(d6,0);
	
  lcd.print("Thermocouple");
  lcd.setCursor(0,1);
  lcd.print("MST TV5 2.24");
	delay(1000);

	

}

void loop() {


offset = map(analogRead(A0),0,1023,0,1440);
minuteOffset = offset % 60;
hourOffset = offset - minuteOffset;
hourOffset = hourOffset / 60;

if (digitalRead(setupPin)==LOW) setupState = 0;
if (digitalRead(setupPin)==HIGH) setupState = 1;

switch(setupState){
	
	case 0: //normal running mode
{	

if (firstCycle == true) {minute = minuteOffset; hour = hourOffset; }

long int second = millis()/1000;  //round(offset)*60;//med en offset i minutter?	

//update real time 


long int seconds = second - minutesPassed*60;

if (seconds >= 60) {minute = minute + 1; minutesPassed = minutesPassed + 1;}
if (minute >= 60) {hour = hour + 1; minute = 0;}
if (hour >= 24) {hour = 0;}

if (minute < 10){
minuteString = "0" + String(minute);} else {minuteString = String(minute);}

if (hour < 10){
hourString = "0" + String(hour);} else {hourString = String(hour);}

timeString = hourString + ":" + minuteString;


   


   delay(1000);

//measure temperature
//TODO 

 // Wait a few seconds between measurements.

cycle2 = timepassed(lastTime2, 2);
if (cycle2 == true) {	
  // Read temperature as Celsius (the default)
t = thermocouple.readCelsius();
t = t - tempOffset;
  TC = String(t,1);

if (t < lowestTemp) {lowestTemp = t; lowestTime = timeString;}
if (firstCycle == true) {firstCycle = false; lowestTime = timeString;}  
  // Check if any reads failed and exit early (to try again).


lastTime2 = millis();
}



/* For debugging:
  lcd.clear();
  lcd.print("Time: ");
  lcd.setCursor(6,0);
  lcd.print(second);
  


  Serial.print("Temperature: ");
  Serial.print(TC);
  Serial.println("C ");
  Serial.println("The time is:");
  //Serial.print(timeString +"\n");
  //Serial.print(hourString +"\n");
  //Serial.print(minuteString +"\n");
  Serial.print(second) ;
  Serial.println(" seconds");
  Serial.print(minute);
  Serial.println(" minutes");
  Serial.print(hourString);
  Serial.println(" hours");
  Serial.println();/*
  Serial.println(offset);
  Serial.println(minuteOffset);
  Serial.println(hourOffset);

*/



cycle = timepassed(lastTime, 1);
if (cycle == true) {	
  lcd.clear();
  lcd.print("Now:");
  lcd.setCursor(5,0);
  lcd.print(TC);
  lcd.setCursor(9,0);
  lcd.print("C ");
  lcd.setCursor(11,0);
  lcd.print(hourString);
 lcd.setCursor(13,0);
  if (colon == true) {lcd.print(":"); colon = false;} else {lcd.print(" "); colon = true;}

 lcd.setCursor(14,0);
  lcd.print(minuteString);  
  lcd.setCursor(0,1);
  lcd.print("Low:");
  lcd.setCursor(5,1);
  lcd.print(String(lowestTemp));
  lcd.setCursor(9,1);
  lcd.print("C ");
  lcd.setCursor(11,1);
  lcd.print(lowestTime);
  
lastTime = millis();
  }
  delay(200);
break;
}

case 1:
	//jeg har også brug for en analog pin her med en hjul på. A0 til A5 kan bruges.
firstCycle = true;
offset = map(analogRead(A0),0,1023,0,1440);
tempOffset = map(analogRead(A1),0,1023,-100,100);
tempOffset = tempOffset/100;

long int minuteOffset = offset % 60;
long int hourOffset = offset - minuteOffset;
hourOffset = hourOffset / 60;
timeString = String(hourOffset) + ":" + String(minuteOffset);

//For debugging:
/*
  Serial.println("Adjust time:");
  Serial.println(timeString);
*/
//For actual use:
  lcd.clear();
  lcd.print("Time set:");
    lcd.setCursor(11,0);
    lcd.print(timeString);
  
  lcd.setCursor(0,1);
  lcd.print("Offset C:");
  lcd.setCursor(11,1);
  lcd.print(String(tempOffset));
  


delay(300);
break; 
}


}

bool timepassed(long lastTime, int seconds) {
	long currentTime = 0;
  currentTime = millis()/1000;
	long diff; 
	diff = currentTime - lastTime/1000;
	bool passed;
	if (diff < seconds) {
		passed = false;
		} else {
			 passed = true;}
		return passed;
	
	}
