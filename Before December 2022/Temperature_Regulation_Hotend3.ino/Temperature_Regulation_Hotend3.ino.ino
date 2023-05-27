long average = 0;
const int relayControl = 10;
const int thermistorRead = A2;
const int thermistorCONTROL = 6;
int thermistorCONTROLRange = 0;   // max

// Define pin connections & motor's steps per revolution
const int dirPin = 3;
const int stepPin = 4;
const int enablePin = 2;

const int setTemp = 250;

int tempLimitSignal;
const int stepsPerRevolution = 1600; // half step
const int dely = 12000;

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
  pinMode(thermistorCONTROL, OUTPUT);
  pinMode(relayControl, OUTPUT);

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  digitalWrite(dirPin, HIGH);
  digitalWrite(enablePin, HIGH);
  tempLimitSignal = 0;
  analogWrite(thermistorCONTROL, thermistorCONTROLRange);
  Serial.println("Starting....");
  
  delay(100);
}

                                      void loop() {
                                        tempRead();
                                        analogWrite(thermistorCONTROL, thermistorCONTROLRange);
                                      
                                        for (int i =0; i<20; i++)
                                          {
                                              stepperCode(dely);
                                          }      
                                        
                                        digitalWrite(relayControl, 1); // Turning on the heater
                                        if (thermistorCONTROLRange < 255) {   thermistorCONTROLRange+=5;   }
                                        
                                        Serial.println(thermistorCONTROLRange);
                                        
                                        while (average < setTemp){  // SET TEPERATURE HERE
                                          digitalWrite(enablePin, LOW);    // Extruder enable
                                          
                                          if (average < (setTemp-20)) { digitalWrite(relayControl, 0);   } // Turn off the heater
                                          if (thermistorCONTROLRange > 0) {   thermistorCONTROLRange-=5;   }
                                          Serial.println(thermistorCONTROLRange);
                                          analogWrite(thermistorCONTROL, thermistorCONTROLRange);
                                          Serial.println("Heater is OFF!");
                                          
                                          for (int i =0; i<20; i++)
                                          {
                                              stepperCode(dely);
                                          }      
                                          tempRead();
                                        }
                                      }
