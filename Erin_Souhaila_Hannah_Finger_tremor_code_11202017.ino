const int analogInPin = A0;                               //set input pin
const int digitalOutPinA = 4;                             //set output pins for lighting LEDs
const int digitalOutPinB = 6;
const int digitalOutPinC = 8;
const int digitalOutPinD = 10;
const int digitalInPinInterrupt = 2;                      //set input interrupt pin

int PhotoCellValue = 0;                                   //input value modulated by photoresistor
volatile int Count = 1;                                   //counting variable for loop
int LEDValueA = 0;                                        //1st LED output value
int LEDValueB = 0;                                        //2nd LED output value
int LEDValueC = 0;                                        //3rd LED output value
int LEDValueD = 0;                                        //4th LED output value
bool Interrupt = HIGH;                                    //value to monitor interrupt

void setup() {Serial.begin(9600);
  pinMode(analogInPin, INPUT);
  pinMode(digitalOutPinA, OUTPUT);
  pinMode(digitalOutPinB, OUTPUT);
  pinMode(digitalOutPinC, OUTPUT);
  pinMode(digitalOutPinD, OUTPUT);

attachInterrupt(digitalPinToInterrupt(2), reset, CHANGE);   //interrupt is attached to digital pin 2
                                                            //will execute reset when button is pressed
}

void loop() {
  PhotoCellValue = analogRead(analogInPin);
  Serial.println(PhotoCellValue);                           //values printed for input voltage modulated by photoresistor
Interrupt = digitalRead(digitalInPinInterrupt);
 Serial.println(Interrupt);                                 //values printed for input voltage modulated by reset button press

  if (PhotoCellValue>350 && Count<16) {                     //if statement will execute when photoresistor is covered by finger
        
      int LEDValueA=Count %2;                               //calculate LSB   
      int LEDValueB=Count/2 %2;     
      int LEDValueC=Count/4 %2;        
      int LEDValueD=Count/8 %2;                             //calculate MSB
   

      digitalWrite(digitalOutPinA, LEDValueA);              //light LEDs
      digitalWrite(digitalOutPinB, LEDValueB);
      digitalWrite(digitalOutPinC, LEDValueC);
      digitalWrite(digitalOutPinD, LEDValueD);
      
      delay(750);                                           //wait for .75 seconds
       Count++;  
 } 
 } 


void reset() {                                              //reset count for loop 
  Count = 1;
  
  LEDValueA= 0;                                             //turn LEDs off until next tremor
  LEDValueB= 0;  
  LEDValueC= 0;     
  LEDValueD= 0;

  digitalWrite(digitalOutPinA, LEDValueA);
  digitalWrite(digitalOutPinB, LEDValueB);
  digitalWrite(digitalOutPinC, LEDValueC);
  digitalWrite(digitalOutPinD, LEDValueD);
  
}


