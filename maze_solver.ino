const int TRIG_PIN = A4;
const int ECHO_PIN = A5;
const int IR_Front = 2;

const int ENA = 6;   
const int IN1 = 7;   
const int IN2 = 8;   
const int IN3 = 9;   
const int IN4 = 10;   
const int ENB = 5;
void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(IR_Front, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  // Reading distance
  int Distance = getDistance();
  // Print distance to Serial Monitor
  Serial.print("Distance: ");
  Serial.print(Distance);
  Serial.println(" cm");
  // Reading IR Sensors (LOW = object/wall detected)
  bool FrontWall = (digitalRead(IR_Front) == LOW);
 
  // Robot behavior execution
  if(FrontWall == false && Distance <= 9){
    if (Distance < 5){
      movedanside();
    }
    else if(Distance > 8){
      movebamside();   
    }
    else if (Distance >=6 && Distance  <=7){
      moveForward();
    }
  }
  else if (FrontWall == false && Distance > 9){
          movebamside();
  }
  else if (FrontWall == true){
    if(Distance >= 1 || Distance <= 9 ) {
      movedanside();
    }
  }
  else{
    stopMotors();
  }
  delay(100); // Small delay to make Serial Monitor output readable
}
// Function to calculate ultrasonic distance
int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH, 30000); 
  if (duration == 0) return 100; 
  int distanceCm = duration * 0.034 / 2;
  return distanceCm;
}
void moveForward() {
  analogWrite(ENA, 52); // bam wheel
  analogWrite(ENB, 50); // dan wheel
  digitalWrite(IN1, HIGH);//front
  digitalWrite(IN2, LOW); 
  digitalWrite(IN3, HIGH);//front
  digitalWrite(IN4, LOW); 
}
void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
void movebamside() {
  analogWrite(ENA, 52);  // bam wheel
  analogWrite(ENB, 50); // dan wheel
  digitalWrite(IN1, LOW);// front
  digitalWrite(IN2, LOW);  
  digitalWrite(IN3, HIGH);// front
  digitalWrite(IN4, LOW); 
}
void movedanside() {
  analogWrite(ENA, 52); // bam wheel
  analogWrite(ENB, 50);  // dan wheel
  digitalWrite(IN1, HIGH);// front
  digitalWrite(IN2, LOW); 
  digitalWrite(IN3, LOW);// front
  digitalWrite(IN4, LOW);  
}