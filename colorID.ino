#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8
 
int redMin = 8;
int redMax = 60;
int greenMin = 11;
int greenMax = 56;
int blueMin = 6;
int blueMax = 39;
 
int redPW = 0;
int greenPW = 0;
int bluePW = 0;
  
int redValue;
int greenValue;
int blueValue;
 
void setup() {
 
  // Set S0 - S3 as outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Set Sensor output as input
  pinMode(sensorOut, INPUT);
  
  // Set Frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  // Setup Serial Monitor
  Serial.begin(9600);
}
 
void loop() {
  
  // Read Red value
  redPW = getRedPW();
  // Map to value from 0-255
  redValue = map(redPW, redMin,redMax,255,0);
  // Delay to stabilize sensor
  delay(200);
  
  // Read Green value
  greenPW = getGreenPW();
  // Map to value from 0-255
  greenValue = map(greenPW, greenMin,greenMax,255,0);
  // Delay to stabilize sensor
  delay(200);
  
  // Read Blue value
  bluePW = getBluePW();
  // Map to value from 0-255
  blueValue = map(bluePW, blueMin,blueMax,255,0);
  // Delay to stabilize sensor
  delay(200);
  

  redValue = fixNonHex(redValue);
  greenValue = fixNonHex(greenValue);
  blueValue = fixNonHex(blueValue);

  //Serial.println("RGB: " + String(redValue) + ", " + String(greenValue) + ", " + String(blueValue));

  String Hex = String(redValue,HEX) + String(greenValue,HEX) + String(blueValue,HEX);
  Serial.println("#" + Hex);

  // Convert RGB to HSV
  float R = redValue/255.0;
  float G = greenValue/255.0;
  float B = blueValue/255.0;

  float Cmax = max(max(R,G),B);
  float Cmin = min(min(R,G),B);
  float delta = Cmax - Cmin;

  int hue;
  int saturation;
  int value;

  // Hue
  if (delta = 0){
    hue = 0;
  }
  else if (Cmax == R){
    int temp = ((G-B)/delta);
    hue = 60 * temp%6;
  }
  else if (Cmax == G){
    hue = 60 * (((B-R)/delta)+2);
  }
  else if (Cmax == B){
    hue = 60 * (((R-G)/delta)+4);
  }

  // Saturation
  if (Cmax = 0){
    saturation = 0;
  }
  else{
    saturation = delta/Cmax * 100;
  }

  // Value
  value = Cmax * 100;

  if (delta < .05){
    if (value >= .95){
      Serial.println("WHITE");
    }
    else if (value <= .05){
      Serial.println("BLACK");
    }
    else{
      Serial.println("GRAY");
    }
  }
  else{
    if (hue <= 30 || hue > 350){
      Serial.println("RED");
    }
    else if (hue <= 70 || hue > 30){
      Serial.println("ORANGE");
    }
    else if (hue <= 100 || hue > 70){
      Serial.println("YELLOW");
    }
    else if (hue <= 200 || hue > 100){
      Serial.println("GREEN");
    }
    else if (hue <= 280 || hue > 200){
      Serial.println("BLUE");
    }
    else if (hue <= 320 || hue > 280){
      Serial.println("PURPLE");
    }
    else{
      Serial.println("MAGENTA");
    }
  }
/*
  // Detect Various Colors
  if (redValue>blueValue && redValue>greenValue && abs(blueValue-greenValue)<100){
    Serial.println("RED");
  }
  else if (blueValue>redValue && blueValue>greenValue && abs(redValue-greenValue)<100){
    Serial.println("BLUE");
  }
  else if (greenValue>redValue && greenValue>blueValue && abs(redValue-blueValue)<100){
    Serial.println("GREEN");
  }
  else if (abs(redValue-greenValue) < 50 && greenValue>blueValue && abs(redValue-blueValue)<100){
    Serial.println("GREEN");
  }
  else if (255-redValue < 50 && 255-blueValue < 50 && 255-greenValue < 50){
    Serial.println("WHITE");
  }
  else if (redValue < 50 && blueValue < 50 && greenValue < 50){
    Serial.println("BLACK");
  }
*/
}
 
 
// Function to read Red Pulse Widths
int getRedPW() {
 
  // Set sensor to read Red only
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
  
}
 
// Function to read Green Pulse Widths
int getGreenPW() {
 
  // Set sensor to read Green only
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
 
}
 
// Function to read Blue Pulse Widths
int getBluePW() {
 
  // Set sensor to read Blue only
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
 
}

int fixNonHex(int value){
  if (value > 255){
    value = 255;
  }
  if (value < 0){
    value = 0;
  }
  return value;
}


