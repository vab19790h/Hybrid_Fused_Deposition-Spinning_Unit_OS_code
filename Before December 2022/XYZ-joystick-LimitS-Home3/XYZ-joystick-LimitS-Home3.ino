////////////////////////////          use ARDUINO UNO or HIGHER        \\\\\\\\\\\\\\\\\\\\\\\


                                        // Input required
                                        float linear_speed_mm_per_sec;
                                        int length_FD_mm;
                                        int numberOfSpirals;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
float rev_per_length = length_FD_mm/5; // because of the 5mm/rev dipspacement ratio of X-axis actuator
int total_steps_per_length = rev_per_length*400;
int step_delay_to_linear_speed = 6387.50*pow(linear_speed_mm_per_sec, -1.016);

// Counting micro-seconds fot time measurements
unsigned long startTimer = micros();  

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
    if (x == 1 && maxStepsX < 9500) {   stepperCode(stepPinX, step_delay_to_linear_speed);   }
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
    stepperCode(stepPinZ, dely);  
    z = digitalRead(limitSwitchZ);
  } 
  Serial.println("Homing Z-axis Complete");
}

// Homing X axis function
void homingX(){
  Serial.println("Homing X-axis..");
  digitalWrite(dirPinX, LOW);
  while (x==1)
  {
    stepperCode(stepPinX, dely);  
    x = digitalRead(limitSwitchX);
  } 
  Serial.println("Homing X-axis Complete");
}

// Homing Y axis function
void homingY(){
  Serial.println("Homing Y-axis..");
  digitalWrite(dirPinY, LOW);
  while (y==1)
  {
    stepperCode(stepPinY, dely);  
    y = digitalRead(limitSwitchY);
  } 
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

        Serial.println("Starting...");
        delay(1000);
        
// Homing all axis by calling the homing function
        homingAllAxis();
      }


//////////////////////////////////////////////////////////      LOOP      \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

                    void loop() {
                      

                      // reading-in joystick maneuver 
                      xPosition = analogRead(VRx);
                      yPosition = analogRead(VRy);
                      zPosition = analogRead(VRz);
                      SW1_state = digitalRead(SW1);
                      SW2_state = digitalRead(SW2);

                     // mapX = map(xPosition, 0, 1023, -1000, 1000);
                     // mapY = map(yPosition, 0, 1023, -1000, 1000);





                    // Raciprocating X-axis for spiral priting
                      if (SW1_state == 0) {

                        Serial.println("////////////////////    Spiral program is Initiated   \\\\\\\\\\\\\\\\\\\\\\\\\\\\");


                        while (linear_speed_mm_per_sec < 1.00 || linear_speed_mm_per_sec > 19.50) {
                        Serial.print("\n Input Linear speed in mm/sec (Range: 1-19.5): ");
                        while (Serial.available() == 0) { }
                        linear_speed_mm_per_sec = Serial.parseFloat();
                        Serial.println(linear_speed_mm_per_sec);
                        }

                        while (length_FD_mm < 2 || length_FD_mm > 70) {
                        Serial.print("\n Length of the FD in mm (Range: 2-70): ");
                          while (Serial.available() == 0) { }
                        length_FD_mm = Serial.parseInt();
                        Serial.println(linear_speed_mm_per_sec);
                        }
                        
                        while (numberOfSpirals < 2 || numberOfSpirals > 30) {
                        Serial.print("\n Number of spirals (Range: 2-30): ");
                        while (Serial.available() == 0) { }
                        numberOfSpirals = Serial.parseInt();
                        Serial.println(linear_speed_mm_per_sec);
                        } 
                        
                        Serial.print(" | Calculated Delay to relate Linear speed: ");
                        Serial.println(step_delay_to_linear_speed);
                        
                        bool dir_status = 1;

                        delay(1000);
                        
                        for (int i = 0; i<numberOfSpirals; i++)
                        {
                          digitalWrite(dirPinX, dir_status);
                          spiral();
                          dir_status = i%2;
                        }
                        
                        homingZ();
                        
                        while (maxStepsY < 6000)
                        {
                          digitalWrite(dirPinY, HIGH);
                          stepperCode(stepPinY, 500);
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
                     

                      // Limit switch readings
                      x = digitalRead(limitSwitchX);
                      y = digitalRead(limitSwitchY);
                      z = digitalRead(limitSwitchZ);
                      


                      
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
