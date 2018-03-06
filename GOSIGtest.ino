#include <LedControl.h>             // Library for LED control with MAX72XX
//#include <math.h>
/*
  Pins of Arduino Uno for LedControl:
  Pin #7 is connected to DataIn (DIN)
  Pin #8 is connected to CLK (CLK)
  Pin #9 is connected to LOAD (CS)
  There is only one display with MAX72XX
*/


LedControl lc = LedControl(7, 8, 9, 1);  // LedControl(int dataPin, int clkPin, int csPin, int numDevices)
char gosig = 0;

void setup() {

  lc.shutdown(0, false);      // The MAX72XX is in power-saving mode on startup, we have to do a wakeup call
  lc.setIntensity(0, 15);      // Set the brightness of display between 0 and 15
  lc.clearDisplay(0);         // Clear the display

  lc.setDigit(0, 7, 0, false);
  lc.setDigit(0, 6, 0, false);
  lc.setDigit(0, 5, 0, false);
  lc.setDigit(0, 4, 0, false);

  lc.setDigit(0, 3, 0, false);
  lc.setDigit(0, 2, 0, true);
  lc.setDigit(0, 1, 0, false);
  lc.setDigit(0, 0, 0, false);
  Serial.begin(9600);
}

void loop() {

  if(Serial.available()){
    gosig = Serial.read();
  }

  if(gosig == 'G') {
    int i=0;
    int digits[7] = {0};
    unsigned long int time = millis();
    unsigned long int time2 = time;
    while (time > 0) { //Gets the time variable and stores each digit into an array
      int digit = time % 10;
      digits[i] = digit;
      i++;
      time /= 10;
    }

    lc.setDigit(0, 0, digits[0], false); 
    lc.setDigit(0, 1, digits[1], false);
    lc.setDigit(0, 2, digits[2], false);
    lc.setDigit(0, 3, digits[3], false);
    lc.setDigit(0, 4, digits[4], false);
    lc.setDigit(0, 5, digits[5], false);
    lc.setDigit(0, 6, digits[6], false);
    lc.setDigit(0, 7, digits[7], false);


    Serial.print(time2);
    Serial.print(',');
    Serial.print(analogRead(A0));
    //Serial.print(sin(time2*M_PI/180));
    Serial.print('\n');
    if(Serial.available())
    {
      gosig = Serial.read(); 
    }
  }
  

  

}
