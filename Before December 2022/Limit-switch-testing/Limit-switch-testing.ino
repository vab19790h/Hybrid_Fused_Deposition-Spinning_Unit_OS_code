

// Define pin connections & motor's steps per revolution
const int dirPin = 3;
const int stepPin = 4;
const int enablePin = 5;
const int stepsPerRevolution = 200; // 
int dely = 200;
int counter = 0;




// Limit switch

const int LimitStatusX = 7;

const int LimitStatusY = 8;



void setup() {
  Serial.begin(2000000); 
  
   // Declare pins as Outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(LimitStatusX, INPUT);
  pinMode(LimitStatusY, INPUT);
  

  Serial.println("Starting...");
  delay(100);
  digitalWrite(enablePin, LOW);
  digitalWrite(dirPin, LOW);
}

                                                void loop() {

                                                  bool xPosition = digitalRead(LimitStatusX); delay(1);
                                                  Serial.print("xPosition:");
                                                  Serial.print(xPosition);
                                                  bool yPosition = digitalRead(LimitStatusY); delay(100);
                                                  Serial.print("  yPosition:");
                                                  Serial.println(yPosition);

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
