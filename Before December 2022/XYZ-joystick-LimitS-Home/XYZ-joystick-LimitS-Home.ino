////////////////////////////          use ARDUINO UNO or HIGHER        \\\\\\\\\\\\\\\\\\\\\\\

// Joystick pins
int VRx = A0;
int VRy = A1;
int SW = 0;

const int stepsPerRevolution = 800;

// joystick variables
int xPosition = 0;
int yPosition = 0;
int SW_state = 0;

// Define pin connections for X - axis
const int dirPinX = 1;
const int stepPinX = 2;
const int enablePinX = 3;
const int limitSwitchX = 4;

// Define pin connections for Y - axis
const int dirPinY = 5;
const int stepPinY = 6;
const int enablePinY = 7;
const int limitSwitchY = 8;

// Define pin connections for Z - axis
const int dirPinZ = 9;
const int stepPinZ = 10;
const int enablePinZ = 11;
const int limitSwitchZ = 12;

int dely = 0;
int speed_breaker = 0;


bool x = 1;
bool y = 1;
bool z = 1;

// Naximum Travel
int maxStepsX = 0;
int maxStepsY = 0;
int maxStepsZ = 0;

void stepperCode(){
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(speed_breaker);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(speed_breaker);
}

homing( dirPinX, stepPinX, limitSwitchX);

void homing(int dirPin; int stepPin, int *limitSwitch){   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< left here
  digitalWrite(dirPin, LOW);
  int xyz = 0;
  while (xyz==1)
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);  
    xyz = digitalRead(limitSwitch);
  } 

}

      void setup() {
        Serial.begin(2000000); 
        
        pinMode(VRx, INPUT);
        pinMode(VRy, INPUT);
        pinMode(SW, INPUT_PULLUP); 
      
         // Declare pins as Outputs
        pinMode(stepPinX, OUTPUT);
        pinMode(dirPinX, OUTPUT);
        
        pinMode(enablePinX, OUTPUT);
        pinMode(limitStatusX, INPUT);
        
        pinMode(enablePinY, OUTPUT);
        pinMode(limitStatusY, INPUT);
      
        
        Serial.println("Starting...");
        delay(100);
        
  homing();
        
      }



                    void loop() {
                      
                      float start1 = micros();
                      xPosition = analogRead(VRx);
                      yPosition = analogRead(VRy);
                      SW_state = digitalRead(SW);
                     
                      // mapX = map(xPosition, 0, 1023, -1000, 1000);
                     // mapY = map(yPosition, 0, 1023, -1000, 1000);
                    
                      if (SW_state == 0) {speed_breaker+=50; delay(500);}
                      if (speed_breaker > 600) {speed_breaker= 0; }
                                           
                      x = digitalRead(LimitStatusX);
                      y = digitalRead(LimitStatusY);
                      
                      // stepper coding
                      if (xPosition > 525 && counterX < 6000)
                      {
                        digitalWrite(dirPin, HIGH);
                        stepperCode();
                        counterX++;
                        counterY++;
                      }

                      if (x==0)
                      {
                        
                        counterY = 0;
                      }
                    
                      else if (xPosition < 500 && counterX > -10000 && x==1)
                      {
                        digitalWrite(dirPin, LOW);
                        stepperCode();
                        counterX--;
                      }

                        Serial.print(" | X: ");
                        Serial.print(x);
                        Serial.print(" | Y: ");
                        Serial.print(yPosition);
                        Serial.print("  counterX: ");
                        Serial.print(counterX);
                        Serial.print("  counterY: ");
                        Serial.println(counterY);
                      // stepper coding
                   
                   /*
                
                        Serial.print(" | X: ");
                        Serial.print(xPosition);
                        Serial.print(" | Y: ");
                        Serial.print(yPosition);
                        Serial.print(" | delay: ");
                        Serial.print(speed_breaker);
               
                        Serial.print(" | time elapsed: ");
                      
                        float end1 = micros();
                        Serial.println(end1-start1);
                        Serial.print(speed_breaker);
                        Serial.println(end1-start1);

                   */            
                    }
