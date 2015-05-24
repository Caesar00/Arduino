// AUTHOR: CHRISTOPHER CANDY
// This program is designed to implement a traffic light
// system. This system supports road works, emergency
// vehicles, pedestrians, temperature changes, light
// levels and calibration via a potentiometer.

/*******FUNCTIONAL PROTOTYPES********/
void initialisation();
void lightSet1();
void lightSet2();
void pedestrianCrossing();
boolean emergencyService();
boolean roadWorks();
void getCalibration();
boolean getLight();
double getTemperature();

/**********GLOBAL VARIABLES**********/
const int potPin = 0;
const int thermistorPin = 1;
const int lightPin = 2;

const int LEDPin2 = 2;
const int LEDPin3 = 3;
const int LEDPin4 = 4;
const int LEDPin5 = 5;
const int LEDPin6 = 6;
const int LEDPin7 = 7;
const int buttonPin8 = 8;
const int LEDPin9 = 9;
const int LEDPin10 = 10;
const int buttonPin11 = 11;
const int buttonPin12 = 12;
const int LEDPin17 = 17;
const int LEDPin18 = 18;
const int LEDPin19 = 19;

int pedBut;
int emergencyButton;
int roadWorksButton;

double c1 = 1.346239e-03, c2 = 2.309426e-04, c3 = 9.815900e-08;
double voltage;
int vin = 5;
double R1;
double R2 = 10000.0;
double temperature = 0;
double lightLevel;

int lightDelay = 500;
boolean crossing = false;
boolean works = false;
boolean emergency = false;
  
void setup()
{
  Serial.begin(9600);
  pinMode(LEDPin2, OUTPUT);
  pinMode(LEDPin3, OUTPUT);
  pinMode(LEDPin4, OUTPUT);
  pinMode(LEDPin5, OUTPUT);
  pinMode(LEDPin6, OUTPUT);
  pinMode(LEDPin7, OUTPUT);  
  pinMode(buttonPin8, INPUT);  
  pinMode(LEDPin9, OUTPUT);
  pinMode(LEDPin10, OUTPUT);
  pinMode(buttonPin11, INPUT);
  pinMode(buttonPin12, INPUT);  
  pinMode(LEDPin17, OUTPUT);
  pinMode(LEDPin18, OUTPUT);
  pinMode(LEDPin19, OUTPUT);  
}// end setup

void loop()
{  
  // All traffic lights are initialised to red
  initialisation();
  
  while(works == true)
  {
    works = roadWorks(); // This is true when the road works button is pressed.
  }
  
  while(emergency == true)
  {
    emergency = emergencyService(); // This is true when the emergency button is pressed.
  }
  
  delay(lightDelay);

  lightSet1(); // Runs the first set of LEDs
  delay(lightDelay);
  
  while(emergency == true)
  {
    emergency = emergencyService();
  }
  
  if(crossing == true)
  {
    pedestrianCrossing(); // This is true when the pedestrian button is pressed.
  }
  else
    if(crossing == false) 
    {
      lightSet2(); // Runs the second set of LEDs
    }
  delay(lightDelay);
  
}// end loop

void initialisation()
{
  digitalWrite(LEDPin4, HIGH);
  digitalWrite(LEDPin7, HIGH);
  digitalWrite(LEDPin10, HIGH);
  digitalWrite(LEDPin19, HIGH);  
}// end initialisation

void lightSet1()
{
  digitalWrite(LEDPin7, HIGH);
  digitalWrite(LEDPin4, LOW);
  digitalWrite(LEDPin19, LOW);  
  
  do
  {
    getCalibration(); // Potentiometer reading is checked.
    temperature = getTemperature();
    lightLevel = getLight();
    
    for(int i = 0; i < (10 + (10 * voltage)); i++)
    {    
      // Green lights turn on
      digitalWrite(LEDPin2, HIGH);  
      digitalWrite(LEDPin17, HIGH); 
      delay(100);
      pedBut = digitalRead(buttonPin8);
      emergencyButton = digitalRead(buttonPin11);
      roadWorksButton = digitalRead(buttonPin12);
      
      if(roadWorksButton == 1)
      {
        works = true; // return true if road works button is pressed
      }      
      
      if(emergencyButton == 1)
      {
        emergency = true; // return true if emergency button is pressed
      }      
      
      if(pedBut == 1)
      {
        crossing = true; // return true if pedestrian button is pressed
      }
      pedBut = digitalRead(buttonPin8);  
    }
  }while(crossing == false && works == false && emergency == false && lightLevel == false);

  // Green lights turn off
  digitalWrite(LEDPin2, LOW);  
  digitalWrite(LEDPin17, LOW); 
  
  for(int j = 0; j < (6 + (6 * voltage) + temperature); j++)
  {
    // Yellow lights turn on
    digitalWrite(LEDPin3, HIGH);
    digitalWrite(LEDPin18, HIGH);    
    delay(100);
  }   
  // Yellow lights turn off and red lights turn on
  digitalWrite(LEDPin3, LOW);
  digitalWrite(LEDPin18, LOW);   
  digitalWrite(LEDPin4, HIGH);
  digitalWrite(LEDPin19, HIGH);  
}// end lightSet1

void lightSet2()
{
  getCalibration(); // Potentiometer reading is checked.
  temperature = getTemperature();
  int pedBut;
  
  for(int j = 0; j < (10 + (10 * voltage)); j++)
  {
    // Green light turn on
    digitalWrite(LEDPin7, LOW);        
    digitalWrite(LEDPin5, HIGH);  
    delay(100);
    pedBut = digitalRead(buttonPin8);
    emergencyButton = digitalRead(buttonPin11);
    roadWorksButton = digitalRead(buttonPin12);
      
    if(pedBut == 1)
    {
      crossing = true;
    }
    if(emergencyButton == 1)
    {
      emergency = true;
    } 
    if(roadWorksButton == 1)
    {
      works = true;
    }   
  }
  // Green light turn off
  digitalWrite(LEDPin5, LOW);

  for(int k = 0; k < (6 + (6 * voltage) + temperature); k++)
  {
    // Yellow light turn on
    digitalWrite(LEDPin6, HIGH);  
    delay(100);
    pedBut = digitalRead(buttonPin8);
    
    if(pedBut == 1)
    {
      crossing = true;  
    }   
  }
  
  // Yellow lights turn off and red light turn on  
  digitalWrite(LEDPin6, LOW);
  digitalWrite(LEDPin7, HIGH);  
}// end lightSet2

void pedestrianCrossing()
{ 
  getCalibration(); // Potentiometer reading is checked.
  temperature = getTemperature();
  crossing = false;   
  
  // Pedestrian light and traffic light have red light turn off
  // and green turn on
  digitalWrite(LEDPin7, LOW);   
  digitalWrite(LEDPin5, HIGH);
  
  for(int j = 0; j < (7 + (7 * voltage)); j++)
  {  
    digitalWrite(LEDPin9, HIGH);
    digitalWrite(LEDPin10, LOW);
    delay(100);
  }
  digitalWrite(LEDPin9, LOW);
    
  for(int k = 0; k < (1 + (1 * voltage)); k++)
  {  
    // Flash pedestrian light red before turning off
    digitalWrite(LEDPin10, HIGH);
    delay(250);
    digitalWrite(LEDPin10, LOW);
    delay(250);    
  }  
  digitalWrite(LEDPin5, LOW);
  digitalWrite(LEDPin10, HIGH);  
  
  for(int k = 0; k < (6 + (6 * voltage)); k++)
  {
    digitalWrite(LEDPin6, HIGH);
    delay(100);
  }
  
  digitalWrite(LEDPin6, LOW); 
  digitalWrite(LEDPin7, HIGH);  
  
  delay(lightDelay);  
}// end pedestrianCrossing

boolean emergencyService()
{
  // Turn all lights red until emergency button is pressed again
  digitalWrite(LEDPin4, HIGH);
  digitalWrite(LEDPin7, HIGH);
  digitalWrite(LEDPin19, HIGH);  
  
  emergencyButton = digitalRead(buttonPin11);
    
  if(emergencyButton == 1)
    return(false);
  else
    return(true);  
}// end emergencyService

boolean roadWorks()
{
  // Flash all lights orange until road works button is pressed again
  digitalWrite(LEDPin4, LOW);  
  digitalWrite(LEDPin7, LOW);
  digitalWrite(LEDPin19, LOW);  
  
  for(int i = 0; i < (1 + (1 * voltage)); i++)
  {  
    digitalWrite(LEDPin3, HIGH);
    digitalWrite(LEDPin6, HIGH);
    digitalWrite(LEDPin18, HIGH);    
    delay(250);
    digitalWrite(LEDPin3, LOW);
    digitalWrite(LEDPin6, LOW);
    digitalWrite(LEDPin18, LOW);
    delay(250);

    roadWorksButton = digitalRead(buttonPin12);
      
    if(roadWorksButton == 1)
      return(false);
    else
      return(true);
  }  
}// end roadWorks

void getCalibration()
{
  // Read potentiometer voltage
  double calibration = analogRead(potPin);
  
  voltage = ((calibration + 1) * 5) / 1024.0, 3;
  
  Serial.print("Potentiometer: ");
  Serial.println(voltage);
}// end getCalibration

boolean getLight()
{
  // Read light levels. This affects the main road option
  int light = analogRead(lightPin);
  
  voltage = ((light + 1) * vin) / 1024.0, 3;
  R1 = ((vin * R2) / voltage) - R2;

  if(R1 < 4000)
    return(true);
  else
    return(false);
}// end getLight

double getTemperature()
{
  // Read temperature in Kelvin
  double logRt;
  double T;
  int tempRange;
  int tempRead = analogRead(thermistorPin); 
  
  voltage = ((tempRead + 1) * vin) / 1024.0, 3;
  R1 = (vin * R2) / voltage - R2;
  logRt = log(R1);
  T = (1.0 / (c1 + (c2 * logRt) + (c3 * logRt * logRt * logRt)));
  
  if(T > 295 && T <= 298)
    tempRange = 1;
  else
    if(T > 298 && T <= 301)
      tempRange = 2;
  else
    if(T > 301)
      tempRange = 3;
  
  Serial.print("Temperature: ");
  Serial.println(T);
   
  return tempRange;
}// end getTemperature
