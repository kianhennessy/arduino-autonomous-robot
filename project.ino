#include <Servo.h> 

Servo servoLeft; // Include servo library
Servo servoRight; // Declare left and right servos

byte wLeftOld; // Previous loop whisker values
byte wRightOld;                              
byte counter; // For counting alternate corners

void setup() // Built-in initialization block
{
pinMode(7, INPUT); // Set right whisker pin to input 
pinMode(5, INPUT); // Set left whisker pin to input
pinMode(8, OUTPUT); // Left LED indicator -> output 
pinMode(2, OUTPUT); // Right LED indicator -> output
tone(4, 3000, 1000); // Play tone for 1 second 
delay(1000); // Delay to finish tone


servoLeft.attach(13); // Attach left signal to pin 13 
servoRight.attach(12); // Attach right signal to pin 12

wLeftOld = 0; // Init. previous whisker states
wRightOld = 1;  
counter = 0; // Initialize counter to 0

}
void loop() // Main loop auto-repeats
{
  

byte wLeft = digitalRead(5); // Copy left result to wLeft
byte wRight = digitalRead(7); // Copy right result to wRight

// Corner Escape
 if(wLeft != wRight) // If one whisker pressed
 { // Alternate from last time?
    if ((wLeft != wLeftOld) && (wRight != wRightOld))  
    {                                       
      counter++; // Increase count by one
      wLeftOld = wLeft; // Record current for next rep
      wRightOld = wRight;
      if(counter == 4) // Stuck in a corner?
      {
        wLeft = 0; // Set up for U-turn
        wRight = 0;
        counter = 0; // Clear alternate corner count
      }
    }  
    else // Not alternate from last time
    {
      counter = 0; // Clear alternate corner count
    }
  }  

 if((wLeft == 0) && (wRight == 0)) // If both whiskers contact
 {
  digitalWrite(8, HIGH); // Left LED on 
  digitalWrite(2, HIGH); // Right LED on 
  tone(4, 3000, 1000); // Play tone for 1 second 
  backward(500); // Back up 0.5 seconds
  turnRight(800); // Turn right about 120 degrees
 }
 else if(wLeft == 0) // If only left whisker contact
 {
  digitalWrite(8, HIGH); // Left LED on 
  digitalWrite(2, LOW); // Right LED off 
  tone(4, 3000, 1000); // Play tone for 1 second
  backward(500); // Back up 0.5 seconds
  turnRight(400); // Turn right about 60 degrees
 }
 else if(wRight == 0) // If only right whisker contact
 {
  digitalWrite(8, LOW); // Left LED off 
  digitalWrite(2, HIGH); // Right LED on 
  tone(4, 3000, 1000); // Play tone for 1 second
  backward(500); // Back up 0.5 seconds
  turnLeft(400); // Turn left about 60 degrees
 }
 else 
 {
  digitalWrite(8, LOW); // Left LED off 
  digitalWrite(2, LOW); // Right LED off
  forward(20); // Forward 1/50 of a second
 }

}

void forward(int time) // Forward function
{
servoLeft.writeMicroseconds(1700); // Left wheel counterclockwise 
servoRight.writeMicroseconds(1300); // Right wheel clockwise 
delay(time); // Maneuver for time ms
}

void turnLeft(int time) // Left turn function
{
servoLeft.writeMicroseconds(1300); // Left wheel clockwise
servoRight.writeMicroseconds(1300); // Right wheel clockwise 
delay(time); // Maneuver for time ms
}

void turnRight(int time) // Right turn function
{
servoLeft.writeMicroseconds(1700); // Left wheel counterclockwise 
servoRight.writeMicroseconds(1700); // Right wheel counterclockwise 
delay(time); // Maneuver for time ms
}

void backward(int time) // Backward function
{
tone(4, 3000, 250); //Series of tones - Play tone for 1 second
tone(4, 3000, 250); // Play tone for 1 second
tone(4, 3000, 250); // Play tone for 1 second
tone(4, 3000, 250); // Play tone for 1 second
servoLeft.writeMicroseconds(1300); // Left wheel clockwise
servoRight.writeMicroseconds(1700); // Right wheel counterclockwise 
delay(time); // Maneuver for time ms
}
