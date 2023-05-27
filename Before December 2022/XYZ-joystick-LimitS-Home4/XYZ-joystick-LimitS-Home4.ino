////////////////////////////          use ARDUINO UNO or HIGHER        \\\\\\\\\\\\\\\\\\\\\\\


                                        // Input required
                                        int linear_speed_mm_per_sec = 14;  // MAX 19.5
                                        int length_FD_mm = 20;             // MAX 30
                                        int numberOfSpirals = 8;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
float rev_per_length = length_FD_mm/5; // because of the 5mm/rev dipspacement ratio of X-axis actuator
int total_steps_per_length = rev_per_length*400;
int step_delay_to_linear_speed = 6387.50*pow(linear_speed_mm_per_sec, -1.016);

// Counting micro-seconds fot time measurements
unsigned long startTimer = micros();  

bool initiateFirstHoming = 0;

// spindle rpm speed output pin

int startSpindle = 10;

// Joystick pins
int VRx = A0;
int VRy = A1;
int VRz = A2;
int UnknownApplication = A3;
int SW1 = 12;
int SW2 = 13;

const int stepsPerRevolution = 800;

// joystick variables
int xPosition = 0;
int yPosition = 0;
int zPosition = 0;
int SW1_state = 0;
int SW2_state = 0;

// Define pin connections for X - axis
const int dirPinX = 2;
const int stepPinX = 3;
const int limitSwitchX = 4;

// Define pin connections for Y - axis
const int dirPinY = 8;
const int stepPinY = 9;
const int limitSwitchY = 7;

// Define pin connections for Z - axis
const int dirPinZ = 5;
const int stepPinZ = 6;
const int limitSwitchZ = 11;



int dely = 300;


bool x = 1;
bool y = 1;
bool z = 1;

// Maximum Travel limit
int maxStepsX = 0;
int maxStepsY = 0;
int maxStepsZ = 0;

// temperary: to count max steps for max travel limit for each axis
int test_counter = 0;




////////////////////////////////////////////   Declaration of Functions    \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

// X-axis reciprocating traveling function to print spirals. 
// NOTE: X-axis set at 400 steps per revolution: actuator displacement: 5mm/rev

void spiral(){
  unsigned long startTimer1 = micros(); 
  
  for (int i=0; i<total_steps_per_length; i++)
  {
    if (x == 1 && maxStepsX < (9500-length_FD_mm*400/5)) {   stepperCode(stepPinX, step_delay_to_linear_speed);   }
  }
  
  float Seconds_per_total_length = (micros()-startTimer1)/1000000.00;
  float measured_linear_speed_mm_per_sec = length_FD_mm/Seconds_per_total_length;
  Serial.print("Seconds_per_total_length: ");
  Serial.print(Seconds_per_total_length);
  Serial.print(" | Measured linear speed in mm/sec: ");
  Serial.println(measured_linear_speed_mm_per_sec);
  
}


// Common steping function
void stepperCode(int stepPin, int wait){
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(wait);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(wait);
}

// Homing Z axis function
void homingZ(){
  Serial.println("Homing Z-axis..");
  digitalWrite(dirPinZ, LOW);
  while (z==1)
  {
    stepperCode(stepPinZ, 300);  
    z = digitalRead(limitSwitchZ);
  } 
  maxStepsZ = 0;
  Serial.println("Homing Z-axis Complete");
}

// Homing X axis function
void homingX(){
  Serial.println("Homing X-axis..");
  digitalWrite(dirPinX, LOW);
  while (x==1)
  {
    stepperCode(stepPinX, 300);  
    x = digitalRead(limitSwitchX);
  } 
  maxStepsX = 0;
  Serial.println("Homing X-axis Complete");
}

// Homing Y axis function
void homingY(){
  Serial.println("Homing Y-axis..");
  digitalWrite(dirPinY, LOW);
  while (y==1)
  {
    stepperCode(stepPinY, 300);  
    y = digitalRead(limitSwitchY);
  } 
  maxStepsY = 0;
  Serial.println("Homing Y-axis complete");
}

void homingAllAxis(){
     // calling homing function for each axis sequentially 
        homingZ();
        homingX();
        homingY();
}

//////////////////////////////////////////////////////////    SETUP     \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

void setup(){
        Serial.begin(2000000); 
        
        pinMode(VRx, INPUT);
        pinMode(VRy, INPUT);
        pinMode(VRz, INPUT);
        pinMode(UnknownApplication, INPUT);
        pinMode(SW1, INPUT_PULLUP); 
        pinMode(SW2, INPUT_PULLUP); 
      
     // Declare pins as Outputs and Inputs for each axis
        pinMode(dirPinX, OUTPUT);  
        pinMode(stepPinX, OUTPUT);
        pinMode(limitSwitchX, INPUT);

        pinMode(dirPinY, OUTPUT);  
        pinMode(stepPinY, OUTPUT);
        pinMode(limitSwitchY, INPUT);

        pinMode(dirPinZ, OUTPUT);  
        pinMode(stepPinZ, OUTPUT);
        pinMode(limitSwitchZ, INPUT);

        pinMode(startSpindle, OUTPUT);

        // Asking spindle to stay stopped
        digitalWrite(startSpindle, 0);
       
        Serial.println("Starting...");
        delay(2000);
        Serial.println("Please click the second Joystick button to Intiate Homing Siquence.");
        
      }


//////////////////////////////////////////////////////////      LOOP      \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

                    void loop() {

                      if (initiateFirstHoming == 0){
                        SW2_state = digitalRead(SW2);
                        if (SW2_state == 0){
                          // Homing all axis by calling the homing function
                          homingAllAxis();
                          initiateFirstHoming = 1;
                        }
                      }

                      if (initiateFirstHoming == 1)
                      {
                         // reading-in joystick maneuver 
                      xPosition = analogRead(VRx);
                      yPosition = analogRead(VRy);
                      zPosition = analogRead(VRz);
                      SW1_state = digitalRead(SW1);
                      SW2_state = digitalRead(SW2);

                     // mapX = map(xPosition, 0, 1023, -1000, 1000);
                     // mapY = map(yPosition, 0, 1023, -1000, 1000);
                      
                      
                     // Limit switch readings
                      x = digitalRead(limitSwitchX);
                      y = digitalRead(limitSwitchY);
                      z = digitalRead(limitSwitchZ);
                      



                    ////////////////////////////////              Raciprocating X-axis for spiral priting                   \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
                    
                      if (SW1_state == 0) {

                        


                        Serial.println("\n\n=== Spiral program is Initiated ===\n");
                        

                        Serial.print("Input Linear speed: ");
                        Serial.print(linear_speed_mm_per_sec);
                        Serial.print(" | Length of the FD: ");
                        Serial.println(length_FD_mm);
                        Serial.print("Number of spirals: ");
                        Serial.print(numberOfSpirals);
                        Serial.print(" | Calculated Delay to relate Linear speed: ");
                        Serial.println(step_delay_to_linear_speed);
                        Serial.print("\n\n");
                        
                        bool dir_status = 1;

                        delay(1000);

                        for (int i = 0; i<600; i++)   // Moving 5 mm away and 5 mm high before initiating spirals
                        {
                          if (maxStepsX < 9500 && x==1 && maxStepsZ > -10 && z==1)
                          {
                            digitalWrite(dirPinX, dir_status);
                            stepperCode(stepPinX, 300);
                            maxStepsX++;
                            digitalWrite(dirPinZ, LOW);
                            stepperCode(stepPinZ, 300);
                            maxStepsZ--;
                          }
                          
                          else
                          {
                            Serial.println(" X & Z axis positions are at or near on of the edges");
                            delay(1000);
                          }
                        }

                        digitalWrite(startSpindle, 1);
                        
                        for (int i = 0; i<numberOfSpirals; i++)  // Initiating spiral code "numberOfSpirals" many times
                        {
                          digitalWrite(dirPinX, dir_status);
                          spiral();
                          dir_status = i%2;
                        }

                       // stopping spindle
                      digitalWrite(startSpindle, 0);

                        // moving axis out of the way
                        homingZ();

                        // moving axis to the front end
                        while (maxStepsY < 6000)
                        {
                          digitalWrite(dirPinY, HIGH);
                          stepperCode(stepPinY, 300);
                          maxStepsY++;
                        }
                        
                         delay(500);
                        }










                      // travel speed adjustment
                      if (SW2_state == 0) {
                        dely = dely+200;

                        if (dely > 1500) { dely = 300; }
                      
                        delay(500);
                      }
                     
                      
                      
           // stepper coding for X - axis in the OPPOSITE direction of the limit switch
                      if (xPosition < 300 && maxStepsX < 9500) // defines maximum travelable steps
                      {
                        digitalWrite(dirPinX, HIGH);
                        stepperCode(stepPinX, dely);
                        maxStepsX++;
            // test_counter++;
                      }
                                                                                             
           // stepper coding for X - axis in the direction of the limit switch
                      else if (xPosition > 400 && maxStepsX > -10 && x==1) // In the direction of the limit switch
                      {
                        digitalWrite(dirPinX, LOW);
                        stepperCode(stepPinX, dely);
                        maxStepsX--;
                      }

           // stepper coding for Y - axis in the OPPOSITE direction of the limit switch
                       if (yPosition < 300 && maxStepsY < 6000) // In the direction of the limit switch
                      {
                        digitalWrite(dirPinY, HIGH); // opposite to the limit switch: 
                        stepperCode(stepPinY, dely);
                        maxStepsY++;
                    //    test_counter++;
                      }

           // stepper coding for Y - axis in the direction of the limit switch
                      else if (yPosition > 400 && maxStepsY > -10 && y==1) // defines maximum travelable steps
                      {
                        digitalWrite(dirPinY, LOW);
                        stepperCode(stepPinY, dely);
                        maxStepsY--;
                        
                      }
                                                                                       
           // stepper coding for Z - axis in the OPPOSITE direction of the limit switch
                      if (zPosition < 300 && maxStepsZ < 8000) // defines maximum travelable steps
                      {
                        digitalWrite(dirPinZ, HIGH);
                        stepperCode(stepPinZ, dely);
                        maxStepsZ++;
                       test_counter++;
                      }
                                                                                          
           // stepper coding for Z - axis in the direction of the limit switch
                      else if (zPosition > 400 && maxStepsZ > -10 && z==1) // In the direction of the limit switch
                      {
                        digitalWrite(dirPinZ, LOW);
                        stepperCode(stepPinZ, dely);
                        maxStepsZ--;
                      }

                                                                                  /* Temporary: to count number of steps it takes to get to the other end
                                                                                                             if (y==0)
                                                                                                              {
                                                                                                                test_counter = 0;
                                                                                                              }  
                                                                                      */              

                      }
                     

      /*                
                        Serial.print(" | X: ");
                        Serial.print(xPosition);
                        Serial.print(" | Y: ");
                        Serial.print(yPosition);
                        Serial.print(" | Z: ");
                        Serial.print(zPosition);
                        Serial.print(" | SW1: ");
                        Serial.print(SW1_state);
                        Serial.print(" | SW2: ");
                        Serial.print(SW2_state);
                        Serial.print(" | maxStepsZ: ");
                        Serial.println(maxStepsZ);
                     //   Serial.print(" | test_counter: ");
                     //   Serial.println(test_counter);
                      // stepper coding
                   
               */                
                    }
