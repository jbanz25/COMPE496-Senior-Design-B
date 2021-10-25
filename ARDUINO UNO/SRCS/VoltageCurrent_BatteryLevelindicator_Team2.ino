/* 
   *  Voltage/Current Battery Level Indicator 
   *  ARDUINO UNO / ARDUINO IDE
   *  Team 2
   *  NAMES: Jacob, Yousef, Abdul, Tom, Eisa
   *  COMPE496B Fall 21' 
 */

// Resistors 
const float R1 = 10000;
const float R2 = 3000;

// stores the value from A2 for the internal battery pack 
int sensor1;
float voltage1;
float vout;

// stores values from A0 for LTC6102 current sense
int sensor2;
float voltage2;


void setup()
{
  // sets Analog PIN0 (A0 - LTC6102 Current Sense) and Analog PIN2 (A2 - internal battery pack)
  DDRC = B000101; 

  // sets Digital Pins (D2-D7) and Digital Pins (B8-B13)
  DDRD = B11111100;
  DDRB = B111111;

  Serial.begin(9600);
}

void loop() 
{
  // Internal Battery Pack
  sensor1 = analogRead(A2);
  voltage1 = (sensor1 / 1024.0) * 5.0;
  vout = voltage1 * ((R1+R2)/R2); 

  // LTC6102 Current Sense Amplfier 
  sensor2 = analogRead(A0);
  voltage2 = (sensor2 / 1024.0) * 5.0;

  // serial prints values for internal battery pack
  Serial.print(sensor1); 
  Serial.print("\n");
  Serial.print(voltage1);
  Serial.print("\n");
  Serial.print(vout);
  Serial.print("\n");
  // serial prints values for LTC6102 current sense amplifier
  Serial.print(sensor2);
  Serial.print("\n");
  Serial.print(voltage2);
  Serial.print("\n");
  
  /*
   * if statements for the LTC6102 current sense amplifier (A0)
   */
  if ((voltage2 < 1.55) && (voltage2 > 1.35))
  {
    PORTB = B001000; // turns on PINB11 (Yellow LED)  
  }
  else if ((voltage2 >= 1.55) && (voltage2 <= 1.65))
  {
    PORTB = B010000; // turns on PINB12 (Green LED)  
  }
  else if ((voltage2 > 1.65) && (voltage2 < 1.85))
  {
    PORTB = B100000; // turns on PINB13 (Red LED)  
  }
  else
  {
    PORTB = B000000; // turns off all three LED
  }

 
 

  /*
   * if statements for the internal battery pack (A2)
   */
  if ((vout >= 9.7) && (vout < 10.5))
  { 
     PORTD = B00000100; // sets PIND2 high 
  }
  else if ((vout >= 10.5) && (vout < 11))
  {
     PORTD = B00001000; // sets PIND3 high 
  }
  else if ((vout >= 11) && (vout < 11.5))
  {
     PORTD = B00010000; // sets PIND4 high
  }
  else if ((vout >= 11.5) && (vout < 12))
  { 
     PORTD = B00100000; // sets PIND5 high  
  }
  else if ((vout >= 12) && (vout < 12.5))
  { 
    PORTD = B01000000; // sets PIND6 high 
  }
  else if ((vout >= 12.5) && (vout < 13))
  { 
    PORTD = B10000000; // sets PIND7 high
    PORTB = B000000; // keeps PINSB low 
  }
  else if ((vout >= 13) && (vout < 13.5))
  { 
    PORTB = B000001; // sets PINB8 high
    PORTD = B00000000; // keeps PINSD from turning on
  }
  else if ((vout >= 13.5) && (vout < 14))
  { 
    PORTB = B000010; // sets PINB9 high 
    PORTD = B00000000; // keeps PINSD from turning on
  }
  else if ((vout >= 14) && (vout < 14.5))
  { 
    PORTB = B000100; // sets PINB10 high
    PORTD = B00000000; // keeps PINSD from turning on
  }
  else if ((vout >= 14.5))
  { 
    PORTD = B11111100; // turns all 9 LEDs on (PIND2-PIND7) & (PINB8-PINB10)
    PORTB = B000111;
  }
  else
  {
    PORTD = B00000000; // turns all 9 LEDs off (PIND2-PIND7) & (PINB8-PINB10)
    PORTB = B000000;
  }
  delay(10);
}
