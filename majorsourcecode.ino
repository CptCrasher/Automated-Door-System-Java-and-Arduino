#include <Servo.h>
#include <U8x8lib.h>
Servo myservo;

//Pin variables
int pirPin = 5; //Pin at which PIR Sensor is connected
int LDRPin = A2;//Pin at which LDR is connected
int buzzer = 12;//Pin at which Buzzer is connected
int servoPin = 11;//Pin at which Servo is connected
int trigPin = 10;//Pin at which Trigger is connected
int echoPin = 9;//Pin at which Echo is connected
int redPin = A3;//Pin at which RED RGB pin is connected
int greenPin = A5;//Pin at which GREEN RGB pin is connected
int bluePin = A4;//Pin at which BLUE RGB pin is connected

//Storage variables for later use.
int pirValue = 0;
int pos = 0;
int LDRValue = 0;
long duration;
int distance;
int looper = 0;
int doorCounter = 0;
int javaLooper = 1;

//Method to send an integer value to Java (changes each time door is opened)
void sendData() {
 const auto value = doorCounter;
 const byte data[] = {0, 0, highByte(value), lowByte(value)};
 Serial.write(data, 4);
 Serial.println();
}

void setup() {
  Serial.begin(9600);
//Initalizing Pin Modes
  pinMode(pirPin,INPUT);
  pinMode(LDRPin,INPUT);
  pinMode(echoPin,INPUT);
  pinMode(trigPin,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  myservo.attach(servoPin);

  myservo.write(0);//Servo Starting Position

  delay(1000);
}//void setup


//Method to change the colour of the RGB LED
void setColor(int red, int green, int blue)
{
  //Obtaining RGB Value
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  //Overwriting existing RGB values
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}//setColor




void loop() {
  //Recieves byte from Java
 const auto receivedData = Serial.read();
 
 //Turns System Off
  if (receivedData == 0){
    javaLooper *=-1;
    return;
  }
  
   //Manually opens the door and closes it after 2 seconds

  else if(receivedData == 255){
    tone(buzzer,1000,500);
    delay(25);
    tone(buzzer,750,500);
    delay(25);
    tone(buzzer,400,300);
    delay(25);
     //Door is opened for [BLANK AMOUNT OF TIME]
    for(pos = 0; pos<=90;pos++){
      myservo.write(pos);
      delay(25);
    }//for
    
  delay(2000);//Time door is opened for
    //Buzzer sound is played
    tone(buzzer,400,300);
    delay(25);
    tone(buzzer,750,500);
    delay(25);
    tone(buzzer,1000,500);
    delay(25);
    
    //Door is moved
    for(pos = 90; pos>=0;pos--){
      myservo.write(pos);
      delay(25);
    }//for  
    delay(2000);  
    return;
  }

  //Sends info to Java to graph
  sendData();
  delay(10);
if(javaLooper > 0){  
//The code only excutes when there is a high level of light detected
LDRValue = analogRead(LDRPin);
Serial.println(LDRValue);

//Brightness over 10 code will execute
if(LDRValue > 10){ 
  setColor(0, 0, 255);  // If LDR detects a high brightness level, a green light is displayed
  delay(1000);//Pause for 1 second
  
  digitalWrite(trigPin, LOW);//Initally determing the Outputing ultrasonic sensor pin as low
  delay(10);//Short pause; keeps steady flow
  
  
pirValue = digitalRead(pirPin);
if(pirValue == HIGH){
  doorCounter+=1;
   tone(buzzer,1000,500);
    delay(25);
    tone(buzzer,750,500);
    delay(25);
    tone(buzzer,400,300);
    delay(25);
     //Door is opened for [BLANK AMOUNT OF TIME]
    for(pos = 0; pos<=90;pos++){
      myservo.write(pos);
      delay(25);
    }//for
    
  delay(2000);//Time door is opened for
  
  //After door is opened, ultrasonic sound sensor detects if anything is in the way before closing the door  
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); 
  //Converting input value to a centimeter value to be later compared
  distance= duration*0.034/2;
  
  //'Error' Buzzer sound is repetivily played & Red light is displayed if an object comes [BLANK DISTANCE] away from the ultrasonic sound sensor 
  while(looper == 0){
  setColor(255, 0, 0);  // Display a red colour
  delay(10);//Delay to enchance flow of code
    
     //Condition if an object is too close to the door; Buzzer makes a sound
    if(distance < 30){
      tone(buzzer,850,100);
      delay(400);
      tone(buzzer,850,100);
      delay(400);
      tone(buzzer,850,300);
      delay(400);
      
  //Obtains the distance of object from door    
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); 
  distance= duration*0.034/2;
        }//if
    
  //If the ultrasonic sound sensor does not detect a nearby object, the loop is broken
      else{
        looper=1;
      }//else
    }//while

     looper=0;//Reset the loop varible
    
    
  //When the door is begins to close  
    
  setColor(0, 0, 255);  // Change the color back to green
  delay(1000);
   
    //Buzzer sound is played
    tone(buzzer,400,300);
    delay(25);
    tone(buzzer,750,500);
    delay(25);
    tone(buzzer,1000,500);
    delay(25);
    
    //Door is moved
    for(pos = 90; pos>=0;pos--){
      myservo.write(pos);
      delay(25);
    }//for  
    delay(2000);  
  pirValue = LOW;//Motion sensor is set back to a LOW state
  }//if PIR

  }//if LDR
  else{
   setColor(0, 255,0);
   delay(1000);
  }//else
  
}else{
  setColor(255, 0,0);
}//javaLooper if statement

}