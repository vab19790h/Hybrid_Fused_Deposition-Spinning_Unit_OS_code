
// Define pin connections & motor's steps per revolution
const int dirPin = 3;
const int stepPin = 4;
const int enablePin = 2;


const int stepsPerRevolution = 1600; // half step


// Common steping function
void stepperCode(int wait){
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(wait);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(wait);
}



void setup() {
  Serial.begin(2000000);

   pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  digitalWrite(dirPin, HIGH);
  digitalWrite(enablePin, LOW);
  
  Serial.println("Starting....");
  delay(100);
}

                                      void loop() {
                                      
                                         stepperCode(8000);
                                        
                                      }
