unsigned long prevTime=millis();
const unsigned long interval_delay = 2000;
int relay = 3;
double average;
double temp[6];

double SetTemp = 55;  // In degree Celsius 

#include <thermistor.h>
register therm1(A0,0);

//From Arduino to Processing to Txt or cvs etc.
//import
import processing.serial.*;
//declare
PrintWriter output;
Serial mySerial;

void setup() 
{
  pinMode(relay, OUTPUT);
  mySerial = new Serial(this, Serial.list()[0], 2000000);
  output = createWriter ("Furnace_data.csv");
}

void draw() {
    if (mySerial.available() > 0 ) {
         String value = mySerial.readString();
         if ( value != null ) {
              output.println( value );
         }
    }
}

void keyPressed() {
    output.flush();  // Writes the remaining data to the file
    output.close();  // Finishes the file
    exit();  // Stops the program
}

void loop() 
{
  unsigned long currentTime = millis();

for(int i = 0; i <= 5; i++)
{
    delay(125);
    double tempread = therm1.analog2temp();
    temp[i]= tempread;
    prevTime = currentTime;
  if(i == 5)
    {
      average = (temp[0] + temp[1] + temp[2] + temp[3] + temp[4])/5;
      Serial.print("Temperature (Degrees C): "); 
      Serial.println(",");
      Serial.println(average);
      draw();
    }
}
  if(average < (SetTemp))
  {
      digitalWrite(relay, HIGH); // Heater On
  }

  if(average >= (SetTemp)) 
  {
    digitalWrite(relay, LOW); // Heater off
  }
}
