

// Define pin connections & motor's steps per revolution
const int dirPin = 3;
const int stepPin = 4;
const int enablePin = 5;
const int stepsPerRevolution = 800; // 
int dely = 1000;   // Fastest=350
int counter = 0;




// Limit switch

const int LimitStatus = A2;


void setup() {
  Serial.begin(2000000); 
  Serial.println(micros());
  
   // Declare pins as Outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(LimitStatus, INPUT);
  

  Serial.println("Starting...");
  Serial.println(micros());
  delay(100);
  Serial.println(micros());
  digitalWrite(enablePin, 0);
  digitalWrite(dirPin, LOW);
}

                                                void loop() {

                                                
                                                  for (int t = 0; t<= stepsPerRevolution; t++)
                                                  {
                                                      digitalWrite(stepPin, HIGH);
                                                      delayMicroseconds(dely);
                                                      digitalWrite(stepPin, LOW);
                                                      delayMicroseconds(dely);   
                                                  } 
                                                
                                                  counter++;
                                                  Serial.println(micros());
                                                  Serial.print("Rev = ");
                                                  Serial.println(counter);
                                               
                                                }
