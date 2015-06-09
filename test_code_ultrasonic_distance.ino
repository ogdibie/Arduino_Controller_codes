
/*
  Dibie Ogheneruona
  Test to be used in measuring distance using ultrasonic sensor SR04
 */
 
#define trigPin 3
#define echoPin 2
void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  pinMode(trigPin,OUTPUT);
  pinMode (echoPin,INPUT);
}
void loop() {
    
  int duration, distance;
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin,HIGH);
  distance = convert_distance(duration);
  
  Serial.println(distance);
     return (duration/148);
 }

