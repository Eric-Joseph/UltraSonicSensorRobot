#define echoPin A5 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin A4 //attach pin D3 Arduino to pin Trig of HC-SR04
#define echoPin2 4
#define trigPin2 3
#define echoPin3 2
#define trigPin3 5
const int sensor_pin = A0;
int sensor_state = 0;
boolean endOfProgram = false;
int lineCount = 0;

// defines variables
long duration, sideDuration, rightSideDuration; // variable for the duration of sound wave travel
int distance, sideDistance, rightSideDistance; // variable for the distance measurement 
// Motor A connections
int Lin1 = 13;
int Lin2 = 12;
int Lin3 = 11;
int Lin4 = 10;
// Motor B connections
int Rin1 = 9;
int Rin2 = 8;
int Rin3 = 7;
int Rin4 = 6;
int dt = 100;

void setup() {
  // Set all the motor control pins to outputs
  Serial.begin(9600);
  pinMode(sensor_pin, INPUT);
  pinMode(Lin1, OUTPUT);
  pinMode(Lin2, OUTPUT);
  pinMode(Lin3, OUTPUT);
  pinMode(Lin4, OUTPUT);
  pinMode(Rin1, OUTPUT);
  pinMode(Rin2, OUTPUT);
  pinMode(Rin3, OUTPUT);
  pinMode(Rin4, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin2, INPUT); // Sets the echoPin as an INPUT
  pinMode(trigPin3, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin3, INPUT); // Sets the echoPin as an INPUT
  
  // Turn off motors - Initial state
  digitalWrite(Lin1, LOW);
  digitalWrite(Lin2, LOW);
  digitalWrite(Lin3, LOW);
  digitalWrite(Lin4, LOW);
  digitalWrite(Rin1, LOW);
  digitalWrite(Rin2, LOW);
  digitalWrite(Rin3, LOW);
  digitalWrite(Rin4, LOW);

}

void loop() {
  
  sensor_state = analogRead(sensor_pin);
  SensorCheck();
  directionForward();
  if (getSideDistance() < 50){
    turnSlightRight();
  }
  if (getSideDistance() >= 60){
    if (getDistance() >= 50){
      turnSlightLeft();
      }
    else {
      turnRight();
      directionForward();
      delay(500);
      }
    }
  else if (getDistance() < 50){
    turnRight();
    directionForward();
    delay(500);
  }
}

void SensorCheck(){
    if(sensor_state > 800){
    lineCount++;
    if (lineCount == 1){
      directionForward();
      delay(1000);
    }
    if (lineCount == 2){
        turnRight();
        turnRight();
        delay(3000);
        while(endOfProgram == false){
          directionForward();
            if(sensor_state > 800){
              lineCount++;
              delay(750);
              while(endOfProgram == true){
                stopRobot();
              }
            }
            if (getRightSideDistance() < 50){
              turnSlightLeft();
            }
            if (getRightSideDistance() >= 60){
              if (getDistance() >= 50){
                turnSlightRight();
                }
              else {
                turnLeft();
                directionForward();
                delay(500);
                }
              }
            else if (getDistance() < 50){
              turnLeft();
              directionForward();
              delay(1000);
//              turnRight();
//              directionForward();
//              delay(1500);
              }
        }
    }
  }
}

// This function lets you control spinning direction of motors
void directionForward() {
  // Turn on motor A & B
  digitalWrite(Lin1, HIGH);
  digitalWrite(Lin2, LOW);
  digitalWrite(Lin3, HIGH);
  digitalWrite(Lin4, LOW);

  digitalWrite(Rin1, HIGH);
  digitalWrite(Rin2, LOW);
  digitalWrite(Rin3, HIGH);
  digitalWrite(Rin4, LOW);
  
}
  
void directionReverse() { 
  // Now change motor directions
  digitalWrite(Lin1, LOW);
  digitalWrite(Lin2, HIGH);
  digitalWrite(Lin3, LOW);
  digitalWrite(Lin4, HIGH);

  digitalWrite(Rin1, LOW);
  digitalWrite(Rin2, HIGH);
  digitalWrite(Rin3, LOW);
  digitalWrite(Rin4, HIGH);
  
  
}

void turnLeft() {
  // Turn on motor A & B
  digitalWrite(Lin1, LOW);
  digitalWrite(Lin2, HIGH);
  digitalWrite(Lin3, LOW);
  digitalWrite(Lin4, HIGH);

  digitalWrite(Rin1, HIGH);
  digitalWrite(Rin2, LOW);
  digitalWrite(Rin3, HIGH);
  digitalWrite(Rin4, LOW);
  
  delay(1250);

  digitalWrite(Lin1, LOW);
  digitalWrite(Lin2, LOW);
  digitalWrite(Lin3, LOW);
  digitalWrite(Lin4, LOW);

  digitalWrite(Rin1, LOW);
  digitalWrite(Rin2, LOW);
  digitalWrite(Rin3, LOW);
  digitalWrite(Rin4, LOW);
  delay(1000);

}

void turnSlightLeft(){
  // Turn on motor A & B
  digitalWrite(Lin1, LOW);
  digitalWrite(Lin2, HIGH);
  digitalWrite(Lin3, LOW);
  digitalWrite(Lin4, HIGH);

  digitalWrite(Rin1, HIGH);
  digitalWrite(Rin2, LOW);
  digitalWrite(Rin3, HIGH);
  digitalWrite(Rin4, LOW);
  
  delay(250);

  digitalWrite(Lin1, LOW);
  digitalWrite(Lin2, LOW);
  digitalWrite(Lin3, LOW);
  digitalWrite(Lin4, LOW);

  digitalWrite(Rin1, LOW);
  digitalWrite(Rin2, LOW);
  digitalWrite(Rin3, LOW);
  digitalWrite(Rin4, LOW);
  delay(250);
  directionForward();
  delay(500);
}

void turnRight() {

  digitalWrite(Lin1, HIGH);
  digitalWrite(Lin2, LOW);
  digitalWrite(Lin3, HIGH);
  digitalWrite(Lin4, LOW);

  digitalWrite(Rin1, LOW);
  digitalWrite(Rin2, HIGH);
  digitalWrite(Rin3, LOW);
  digitalWrite(Rin4, HIGH);
  delay(1250);
  
  // Turn on motor A & B
  digitalWrite(Lin1, LOW);
  digitalWrite(Lin2, LOW);
  digitalWrite(Lin3, LOW);
  digitalWrite(Lin4, LOW);

  digitalWrite(Rin1, LOW);
  digitalWrite(Rin2, LOW);
  digitalWrite(Rin3, LOW);
  digitalWrite(Rin4, LOW);
  delay(1000);
}

void turnSlightRight(){
  digitalWrite(Lin1, HIGH);
  digitalWrite(Lin2, LOW);
  digitalWrite(Lin3, HIGH);
  digitalWrite(Lin4, LOW);

  digitalWrite(Rin1, LOW);
  digitalWrite(Rin2, HIGH);
  digitalWrite(Rin3, LOW);
  digitalWrite(Rin4, HIGH);
  

  delay(250);
  
  // Turn on motor A & B
  digitalWrite(Lin1, LOW);
  digitalWrite(Lin2, LOW);
  digitalWrite(Lin3, LOW);
  digitalWrite(Lin4, LOW);

  digitalWrite(Rin1, LOW);
  digitalWrite(Rin2, LOW);
  digitalWrite(Rin3, LOW);
  digitalWrite(Rin4, LOW);
  delay(250);
  directionForward();
  delay(500);
}

void stopRobot(){
  digitalWrite(Lin1, LOW);
  digitalWrite(Lin2, LOW);
  digitalWrite(Lin3, LOW);
  digitalWrite(Lin4, LOW);

  digitalWrite(Rin1, LOW);
  digitalWrite(Rin2, LOW);
  digitalWrite(Rin3, LOW);
  digitalWrite(Rin4, LOW);
  delay(250);
}


int getDistance(){
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
}

int getSideDistance(){
    // Clears the trigPin condition
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  sideDuration = pulseIn(echoPin2, HIGH);
  // Calculating the distance
  sideDistance = sideDuration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Side Distance: ");
  Serial.print(sideDistance);
  Serial.println(" cm");
  return sideDistance;
}

int getRightSideDistance(){
    // Clears the trigPin condition
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  rightSideDuration = pulseIn(echoPin3, HIGH);
  // Calculating the distance
  rightSideDistance = rightSideDuration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Side Distance: ");
  Serial.print(rightSideDistance);
  Serial.println(" cm");
  return rightSideDistance;
}
