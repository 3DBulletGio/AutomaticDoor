/*Automatic Door
 * Code by Giorgi Samukashvili
 * 9/23/2022
 */

//Pin Definitions
const int close_button=A1;
const int open_button=A2;
const int current_sensor=A0;
const int R1=2;
const int R2=3;
const int R3=4;
const int R4=5;
const int door_time=50; //maximum amount of time your door takes to close or open +10 seconds, I set it to 50 seconds as default but you might need to change it depending on your needs. 
//this is for a protection system that if anything goes wrong and the code doesn't detect the change in door open/close state, it will automaticly turn off the motor.
const int current_diff=40; //increase this number if the motor is turning off too soon without displaying an error in the serial monitor

void close_door(){
  static int average_current = 0;
  static int current = 0;
 
  static int i = 0;
  
  static int runtime = 0;
  runtime = millis() / 1000; //this line gets the time the arduino has been running for.
  static int save_runtime = 0;
  save_runtime = runtime; // this line saves the time of execution of this function.

  digitalWrite(R2,LOW); //these digitalWrite statements turn on the two relays that are used to turn the motor either clockwise or counter clockwise.
  digitalWrite(R4,LOW);
  
  for(i=0;i<10000;i++){
    runtime = millis() / 1000;
    current = analogRead(current_sensor);
    
    if(runtime - save_runtime >= 2) { //this if statement checks if the current we are getting is too high, and if its not it gets the average current.
       if(current>900){
        Serial.println("ERROR: Current Sensor is detecting high current too soon! either the door is already closed/opened, you need to adjust the referance potentiometer on the sensor or there is a short circuit!");
        digitalWrite(R2,HIGH);
        digitalWrite(R4,HIGH);
        break;
       }
       
       average_current = current;
       
       if(current > average_current + current_diff){ // this if statment turns off the motor if current sensor detects the door closed/opened fully.
      digitalWrite(R2,HIGH);
      digitalWrite(R4,HIGH);
      Serial.println("Door Closed");
      break;
        }
         
    }
    
    if(runtime - save_runtime >= door_time){ //this if statement turns off the motor if given door_time was exeeded.
      digitalWrite(R2,HIGH);
      digitalWrite(R4,HIGH);
      Serial.println("ERROR: Motor automaticly turned off beacuse the given door_time definition was reatched.");
      break;
        }
     }
   }
/////////////////////////////////////////////////////////////////////
void open_door(){
  static int average_current = 0;
  static int current = 0;
 
  static int i = 0;
  
  static int runtime = 0;
  runtime = millis() / 1000; //this line gets the time the arduino has been running for.
  static int save_runtime = 0;
  save_runtime = runtime; // this line saves the time of execution of this function.

  digitalWrite(R1,LOW); //these digitalWrite statements turn on the two relays that are used to turn the motor either clockwise or counter clockwise.
  digitalWrite(R3,LOW);
  
  for(i=0;i<10000;i++){
    runtime = millis() / 1000;
    current = analogRead(current_sensor);
    
    if(runtime - save_runtime >= 2) { //this if statement checks if the current we are getting is too high, and if its not it gets the average current.
       if(current>900){
        Serial.println("ERROR: Current Sensor is detecting high current too soon! either the door is already closed/opened, you need to adjust the referance potentiometer on the sensor or there is a short circuit!");
        digitalWrite(R1,HIGH);
        digitalWrite(R3,HIGH);
        break;
       }
        
         average_current = current;
        
        if(current > average_current + current_diff){ // this if statment turns off the motor if current sensor detects the door closed/opened fully.
      digitalWrite(R1,HIGH);
      digitalWrite(R3,HIGH);
      Serial.println("Door Opened");
      break;
       }
    }
    
    
    
    if(runtime - save_runtime >= door_time){ //this if statement turns off the motor if given door_time was exeeded.
      digitalWrite(R1,HIGH);
      digitalWrite(R3,HIGH);
      Serial.println("ERROR: Motor automaticly turned off beacuse the given door_time definition was reatched.");
      break;
        }
     }
   }
/////////////////////////////////////////////////////////////////////
void setup() {
  
//Start the Serial Monitor
  Serial.begin(9600);
  
  //Pin Mode declarations
pinMode(close_button,INPUT);
pinMode(open_button,INPUT);
pinMode(current_sensor,INPUT);
pinMode(R1,OUTPUT);
pinMode(R2,OUTPUT);
pinMode(R3,OUTPUT);
pinMode(R4,OUTPUT);

digitalWrite(R1,HIGH);
digitalWrite(R2,HIGH);
digitalWrite(R3,HIGH);
digitalWrite(R4,HIGH);
}
/////////////////////////////////////////////////////////////////////
void loop() {

static int cbutton_val = 0;
static int obutton_val = 0;

cbutton_val = analogRead(close_button);
obutton_val = analogRead(open_button);
if(cbutton_val > 700){
  close_door();
  cbutton_val = 0;
  delay(100);
}

if(obutton_val > 700){
  open_door();
  obutton_val = 0;
  delay(100);
}

/* 
 *  // >>>>> only use this part of the code during testing. <<<<<
 *  static int current = 0;
 *  current = analogRead(current_sensor); //Reads the value from the current sensor

Serial.print("Current Sensor Value=");
Serial.println(current); */




}
