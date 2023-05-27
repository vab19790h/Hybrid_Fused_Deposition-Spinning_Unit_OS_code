

// Define pin connections & motor's steps per revolution
const int dirPin = 3;
const int stepPin = 6;
const int enablePin = 8;

int startSpindle = 10;

int startSpindleReading = 0;

const int stepsPerRevolution = 400; // half step

int dely = 400;

int counter = 0;



// Counting micro-seconds fot time measurements
unsigned long startTimer = micros(); 
float rpm;
const int NumberOfRevolution = 30;



// Common steping function
void stepperCode(int wait){
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(wait);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(wait);
}


void setup() {
  Serial.begin(2000000); 
  
   // Declare pins as Outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enablePin, OUTPUT);

  pinMode(startSpindle, INPUT);
  

  Serial.println("Starting...");
  delay(100);
  digitalWrite(dirPin, LOW);
}

                                                void loop() {
                                                  digitalWrite(enablePin, HIGH);
                                                  startSpindleReading = digitalRead(startSpindle);

                                                  counter = 0;
                                                  
                                                  while (startSpindleReading == 1){

                                                    if (counter == 0) { startTimer = micros(); }  // time count starts
                                                    digitalWrite(enablePin, LOW);
                                                    
                                                    for (int t = 0; t< stepsPerRevolution; t++)
                                                    {
                                                        stepperCode(dely);
                                                    }
                                                    counter++;
                                                    startSpindleReading = digitalRead(startSpindle);
                                                    if ( startSpindleReading == 0) { startSpindleReading = 2;}
                                                  }
                                                  

                                                  if (startSpindleReading == 2){
                                                    rpm = (counter*1000000.00/(micros()-startTimer))*60.00;
                                                    digitalWrite(enablePin, LOW);
                                                    Serial.print("Delay: ");
                                                    Serial.print(dely);
                                                    Serial.print(" | Counter: ");
                                                    Serial.print(counter);
                                                    Serial.print(" | seconds: ");
                                                    Serial.print((micros()-startTimer)/1000000.00);
                                                    Serial.print(" | Revolution per Minute: ");
                                                    Serial.println(rpm);
                                                  }
                                                  
                                                }
