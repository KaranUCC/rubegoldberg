// Rube Goldberg Machine Y9 Coding Project
// Arduino Color Sorter
// Made by: Karan Maheshwari

// Include the Servo library
#include <Servo.h>
 // Include the Adafruit TCS34725 color sensor library
#include "Adafruit_TCS34725.h"
// Include the Wire library for I2C communication
#include <Wire.h>

// Create a TCS34725 object with integration time of 50ms and gain of 4x
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

// Create a Servo object for the first servo
Servo servo1;
// Create a Servo object for the second servo
Servo servo2;

// Define the angle to block the marble for the first servo
const int angle_to_block_marble = 0;
// Define the angle to release the marble for the first servo
const int angle_to_release_marble = 90;

// Define the angle for the blue marble's track for the second servo
const int angle_for_blue = 0;
// Define the angle for the green marble's track for the second servo
const int angle_for_green = 60;
// Define the angle for the black marble's track for the second servo
const int angle_for_black = 80;

// Define the LED pin which will be used as a checkpoint once the color sensor detects a color
const int ledPin = 13;

void setup() {

  // Initialize the serial communication at a baud rate of 9600
  Serial.begin(9600);
  
  // Attach the first servo to pin 10
  servo1.attach(10);
  // Attach the first servo to pin 9
  servo2.attach(9);

  // Initialize the TCS34725 color sensor
  tcs.begin(); 

  // Set the LED pin as an output
  pinMode(ledPin, OUTPUT);

}

void loop() {

  // Declare variables to store the color readings
  float red, green, blue;

  // Rotate the first servo to block the marble
  servo1.write(angle_to_block_marble);

  // Wait for 500ms for the marble to settle
  delay(500);

  // Disable the color sensor interrupt to allow for readings
  tcs.setInterrupt(false);

  // Wait for 60ms for the color readings to stabilize
  delay(60);

  // Read the RGB values from the color sensor
  tcs.getRGB(&red, &green, &blue);

  // Enable the color sensor interrupt to prevent reading the metal track's color
  tcs.setInterrupt(true);

  // Print the red value on the serial monitor
  Serial.print("R:\t"); Serial.print(int(red)); 
  // Print the green value on the serial monitor
  Serial.print("\tG:\t"); Serial.print(int(green)); 
  // Print the blue value on the serial monitor
  Serial.print("\tB:\t"); Serial.print(int(blue));
  // Print a new line character to make the serial monitor neat
  Serial.print("\n");

  // Turn on the LED to signify a checkpoint that the color sensor got a reading
  digitalWrite(ledPin, HIGH);

  // Check if the marble is blue using this RGB value (53, 84, 118) with an error parameter of 2
  if (red >= 51 && red <= 55 && green >= 82 && green <= 86 && blue >= 116 && blue <= 120) {

    // Rotate the second servo to the angle for the blue marble's track
    servo2.write(angle_for_blue);

    // Turn off the LED
    digitalWrite(ledPin, LOW);

    // Rotate the first servo to release the marble down the track
    servo1.write(angle_to_release_marble);
    
  } 
  
  // Check if the marble is green using this RGB value (79, 111, 67) with an error parameter of 2
  else if (red >= 77 && red <= 81 && green >= 109 && green <= 113 && blue >= 65 && blue <= 69) {

    // Rotate the second servo to the angle for the green marble's track
    servo2.write(angle_for_green);

    // Turn off the LED
    digitalWrite(ledPin, LOW);

    // Rotate the first servo to release the marble down the track
    servo1.write(angle_to_release_marble);

  } 
  
  // Check if the marble is black using this RGB value (92, 98, 84) with an error parameter of 2
  else if (red >= 90 && red <= 94 && green >= 96 && green <= 100 && blue >= 82 && blue <= 86) {

    // Rotate the second servo to the angle for the black marble's track
    servo2.write(angle_for_black);

    // Turn off the LED
    digitalWrite(ledPin, LOW);

    // Rotate the first servo to release the marble down the track
    servo1.write(angle_to_release_marble);
  }
}

// Finish