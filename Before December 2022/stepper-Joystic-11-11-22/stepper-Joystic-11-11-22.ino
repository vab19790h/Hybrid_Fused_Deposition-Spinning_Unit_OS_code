// Joystick pins
int VRx = A0;
int VRy = A1;
int SW = 2;

// joystick variables
int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
int mapX = 0;
int mapY = 0;

// Define pin connections & motor's steps per revolution
const int dirPin = 3;
const int stepPin = 4;
const int enablePinX = 5;
const int enablePinY = 6;
const int stepsPerRevolution = 200; // set MS1, MS2,MS3 to HIGH in A4988
int counterX = 0;
int counterY = 0;
int dely = 0;
int printer = 0;
int speed_breaker = 0;

// Limit switch
const int LimitStatusX = 7;
const int LimitStatusY = 8;
bool x = 1;
bool y = 1;


void stepperCode(){
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(speed_breaker);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(speed_breaker);
}

void homing(){
  digitalWrite(dirPin, LOW);
  while (x==1)
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);  
    x = digitalRead(LimitStatusX);
  } 

}



      void setup() {
        Serial.begin(2000000); 
        
        pinMode(VRx, INPUT);
        pinMode(VRy, INPUT);
        pinMode(SW, INPUT_PULLUP); 
      
         // Declare pins as Outputs
        pinMode(stepPin, OUTPUT);
        pinMode(dirPin, OUTPUT);
        
        pinMode(enablePinX, OUTPUT);
        pinMode(LimitStatusX, INPUT);
        
        pinMode(enablePinY, OUTPUT);
        pinMode(LimitStatusY, INPUT);
      
        
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
