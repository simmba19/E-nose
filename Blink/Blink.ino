int knobvalue;  // variable to read voltage in the potentiometer 
int potpin =3; //pin to read potentiometer's voltage  
int led = 3;  // the PWM pin the LED is attached to 
void setup() 
{ 
pinMode(led, OUTPUT);   // declare pin 3 to be an output 
Serial.begin(9600);  
//uncomment to see result in serial monitor  
} 

void loop() 
{ 
knobvalue = analogRead(potpin);  // read voltage in the potentiometer 
knobvalue = map(knobvalue, 0, 1023, 0, 255);  //convert values from ADC (0-1023) to PWM (0-255) 
analogWrite(led, knobvalue);  // set the brightness of pin 3 
Serial.println(knobvalue);      
}