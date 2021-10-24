
const int pinX = A0;
const int pinY = A1;
const int buzzerPin = 28;
const int buzzerFrequency = 1750;

void setup() {
  // put your setup code here, to run once:
  pinMode(buzzerPin, OUTPUT);
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int X = analogRead(pinX); // Read the X axis analog value
  int Y = analogRead(pinY); // Read the Y axis analog value

  // Check what direction joystick is pointing and send a signal to the serial port

  // UP
  if(Y < 300){
    Serial.print('w');
  }
  // DOWN
  if(Y > 700){
    Serial.print('s');
  }
  // RIGHT
  if(X > 700){
    Serial.print('d');
  }
  // LEFT
  if(X < 300){
    Serial.print('a');
  }
  
  
}
