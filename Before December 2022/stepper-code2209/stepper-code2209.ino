

// Define pin connections & motor's steps per revolution
const int dirPin = 2;
const int stepPin = 6;
const int enablePin = 8;
const int stepsPerRevolution = 200; // 
int dely = 200;
int counter = 0;




// Limit switch

const int LimitStatus = A2;


void setup() {
  Serial.begin(2000000); 
  
   // Declare pins as Outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(LimitStatus, INPUT);
  

  Serial.println("Starting...");
  delay(100);
  digitalWrite(enablePin, LOW);
  digitalWrite(dirPin, LOW);
}

                                                void loop() {

                                                  int xPosition = analogRead(LimitStatus); delay(1);
                                                  int mapX = map(xPosition, 0, 1023, -1000, 1000);
                                                  Serial.println(mapX);

                                                  /*
                                                  
                                                  for (int t = 0; t<= stepsPerRevolution; t++)
                                                  {
                                                      digitalWrite(stepPin, HIGH);
                                                      delayMicroseconds(dely);
                                                      digitalWrite(stepPin, LOW);
                                                      delayMicroseconds(dely);
                                                      counter++;
                                                  } 

                                                  if (LimitStatus = TRUE)
                                                  {
                                                    digitalWrite(dirPin, LOW);
                                                  }
                                                  */
                                               
                                                }
