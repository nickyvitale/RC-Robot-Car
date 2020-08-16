#include <IRremote.h>
#include <ir_Lego_PF_BitStreamEncoder.h>
#include <AFMotor.h>
// Based on the hex code signal sent by each button pressed on the remote controller
#define BUTTON_UP 1033561079
#define BUTTON_RIGHT 71952287
#define BUTTON_DOWN 465573243
#define BUTTON_LEFT 2351064443
#define REPEAT_BUTTON 0xFFFFFFFF
#define UP_TWO 0xFF18E7
#define DOWN_TWO 0xFF4AB5
#define LEFT_TWO 0xFF10EF
#define RIGHT_TWO 0xFF5AA5

// declarations of components

int receiver = A0;

IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

bool forward = false;
bool backward = false;
bool turn_left = false;
bool turn_right = false;

void setup() {
  // put your setup code here, to run once:
  irrecv.enableIRIn();
  
  motor1.setSpeed(255);
  motor2.setSpeed(255);
  motor3.setSpeed(255);
  motor4.setSpeed(255);
  pinMode(receiver,INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode"); 
  irrecv.enableIRIn(); // Start the receiver
}

void moveForward(){
  Serial.println("FORWARD");
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void moveBackward(){
  Serial.println("BACKWARD");
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void moveLeft(){
  Serial.println("LEFT");
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void moveRight(){
  Serial.println("RIGHT");
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void dontMove(){
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void UP(){
  forward = true;
  backward = false;
  turn_left = false;
  turn_right = false;
}
void DOWN(){
  forward = false;
  backward = true;
  turn_left = false;
  turn_right = false;
}

void RIGHT(){
  forward = false;
  backward = false;
  turn_left = false;
  turn_right = true;
}

void LEFT(){
  forward = false;
  backward = false;
  turn_left = true;
  turn_right = false;
}

void NOMOVE(){
  forward = false;
  backward = false;
  turn_left = false;
  turn_right = false;
}

void loop() {
  // put your main code here, to run repeatedly:

  if (irrecv.decode(&results)){ // If a button is pressed
    Serial.println(results.value);
    switch(results.value){
     case BUTTON_UP:
     UP();
     break;

     case UP_TWO: // Two codes for each input because the sensor is inconsistent
     UP();
     break;

     case BUTTON_DOWN:
     DOWN();
     break;

     case DOWN_TWO:
     DOWN();
     break;

     case BUTTON_RIGHT:
     RIGHT();
     break;

     case RIGHT_TWO:
     RIGHT();
     break;

     case BUTTON_LEFT:
     LEFT();
     break;

     case LEFT_TWO:
     LEFT();
     break;

     case REPEAT_BUTTON: // if button is being held down, keep doing what that button implies
     break;

     default: // if invalid button is pressed, don't do anything
     NOMOVE();
    }
    irrecv.resume();
  }
  else{ // if no button is pressed, don't do anything
    NOMOVE();
  }


  // controls movement based on buttons pressed
  if (forward){
    moveForward();
  }
  else if (backward){
    moveBackward();
  }
  else if (turn_left){
    moveLeft();
  }  
  else if (turn_right){
    moveRight();
  }
  else{
    dontMove();
  }
  delay(500); 
}
