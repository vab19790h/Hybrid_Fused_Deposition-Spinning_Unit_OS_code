long average = 0;
const int relayControl = 10;
const int thermistorRead = A2;
const int startORstop = A1;
int readInJoystick2;
int go123 = 0;

// Define pin connections & motor's steps per revolution
const int dirPin = 3;
const int stepPin = 4;
const int enablePin = 2;

const int dely = 25000;


const int stepsPerRevolution = 1600; // half step


// Common steping function
void stepperCode(int wait){

    digitalWrite(stepPin, HIGH);
    delayMicroseconds(wait);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(wait);
}

void tempRead(){
    average = 0;
    for (int i = 0; i<30; i++){
    average += analogRead(thermistorRead);  
  }
   average = average/30;
   Serial.print("A2: ");
   Serial.println(average);
}



void setup() {
  Serial.begin(2000000);
  // put your setup code here, to run once:
  pinMode(thermistorRead, INPUT);
  pinMode(startORstop, INPUT);
  pinMode(relayControl, OUTPUT);

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  
  digitalWrite(dirPin, HIGH);
  digitalWrite(enablePin, HIGH);
  Serial.println("Starting....");
  
  delay(100);
}

                                      void loop() {

                                        readInJoystick2 = analogRead(startORstop);
                                        
                                        if ( readInJoystick2 < 250) { go123 = 1; }
                                        if ( readInJoystick2 > 780) { go123 = 0; }

                                        if (go123 == 1)
                                        {

                                        tempRead();
                                        digitalWrite(relayControl, 1); // Turning on the heater

                                        for (int i =0; i<20; i++)
                                            {
                                                stepperCode(dely);
                                            }
                                        
 
                                        while (average < 130){  // SET TEPERATURE HERE   100=93C; 90=85C
                                            
                                        digitalWrite(relayControl, 0); // Turn off the heater
                                            
                                        digitalWrite(enablePin, LOW);
                                            
                                        Serial.println("Heater is OFF!");

                                        for (int i =0; i<20; i++)
                                          {
                                              stepperCode(dely);
                                          }

                                            tempRead();
                                          }
                                        }

                                        else 
                                        {
                                          digitalWrite(enablePin, HIGH);  // turning off the spindle
                                          digitalWrite(relayControl, 0); // Turn off the heater
                                          Serial.print("Flip the switch to turn Extruder ON: ");
                                          Serial.println(readInJoystick2);
                                        } 
                                      }
