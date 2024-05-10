#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigPins[] = {4, 6, A3, A0};
const int echoPins[] = {3, 7, A2, A1};
const int numSensors = sizeof(trigPins) / sizeof(trigPins[0]);

const int ledPins[] = {8, 10, 13, 12};
const int numLEDs = sizeof(ledPins) / sizeof(ledPins[0]);

const int buzzerPin = 9;

const int detectionDistance1 = 50;
const int detectionDistance2 = 20;
const int quickApproachThreshold = 20;

int prevDistances[numSensors] = {0};


void setup() { 
  Serial.begin(9600);
  lcd.init();         // initialize the lcd
  lcd.backlight(); 

  for (int i = 0; i < numSensors; i++) {
    pinMode(trigPins[i], OUTPUT);
    pinMode(echoPins[i], INPUT);
  }

  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  long durations[numSensors];

  for (int i = 0; i < numSensors; i++) {
    digitalWrite(trigPins[i], LOW);
    delayMicroseconds(2);
    digitalWrite(trigPins[i], HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPins[i], LOW);
    durations[i] = pulseIn(echoPins[i], HIGH);
  }

  int distances[numSensors];
  for (int i = 0; i < numSensors; i++) {
    distances[i] = durations[i] * 0.034 / 2;
  }

  //Serial.print("Distances: ");
  for (int i = 0; i < numSensors; i++) {
    Serial.print(distances[i]);
    Serial.print(" ");
  }
  Serial.println();

  bool objectDetected = false;
  bool objectDetected2 = false;
  bool quickApproachDetected = false;
  int detectedObjects = 0;

  for (int i = 0; i < numSensors; i++) {
    if (distances[i] < detectionDistance1) {
      objectDetected = true;
      detectedObjects++; 
      if(distances[i] < detectionDistance2)
      {
        objectDetected2=true;
      }
      if (prevDistances[i] - distances[i] > quickApproachThreshold ) {
        quickApproachDetected = true;
        break;  
      }
    }
  }
  if (quickApproachDetected) {
      //Serial.println("Object approaching quickly!");
      lcd.setCursor(1, 0);
      lcd.print("Object approaching quickly!");
  
        digitalWrite(buzzerPin, HIGH);
        delay(400);
        digitalWrite(buzzerPin, LOW);
      
    }
  if (objectDetected2) {
      //Serial.println("Object nearly detected!");
        digitalWrite(buzzerPin, HIGH);
        delay(300);
        digitalWrite(buzzerPin, LOW);
      
    }
  if (objectDetected) {
    //Serial.print("Object detected! ");
    lcd.setCursor(1, 0);
    lcd.print("Objects : ");
    
    lcd.print(detectedObjects);
    //Serial.print(detectedObjects); 
    //Serial.println(" objects detected.");
    for (int i = 0; i < numSensors; i++) {
      if (distances[i] < detectionDistance1) {
        switch(i) {
          case 0:
            //Serial.println("Object detected: Left front side");
            lcd.setCursor(2, 1);
            lcd.print("Left Front");
            break;
          case 1:
            //Serial.println("Object detected: Left side");
            lcd.setCursor(2, 1);
            lcd.print("Left");
            break;
          case 2:
            //Serial.println("Object detected: Left back side");
            lcd.setCursor(2, 1);
            lcd.print("Left Back");
            break;
          case 3:
            //Serial.println("Object detected: Right back side");
            lcd.setCursor(2, 1);
            lcd.print("Right Back");
            break;
          case 4:
            //Serial.println("Object detected: Right side");
            lcd.setCursor(2, 1);
            lcd.print("Right");
            break;
          case 5:
            //Serial.println("Object detected: Right front side");
            lcd.setCursor(2, 1);
            lcd.print("Right Front");
            break;
          default:
            break;
        }
      }
    }
  }

  for (int i = 0; i < numSensors; i++) {
    prevDistances[i] = distances[i];
  }

  for (int i = 0; i < numLEDs; i++) {
    digitalWrite(ledPins[i], distances[i] < detectionDistance1 ? HIGH : LOW);
  }

  delay(10);
  lcd.clear();
}
