 //line sensor

  #include <QTRSensors.h>

  QTRSensors qtr;

  const uint8_t SensorCount = 4;

  uint16_t SensorValues[SensorCount];


//colour sensor
  #define S0 2
  #define S1 9
  #define S2 4
  #define S3 5
  #define sensorOut 4

  int green[] = {18, 20, 20};
  bool greenFlag[] = {false, false, false};
  int difference = 0;
  int frequency = 0;

//H bridge
  const int In1 = 10;
  const int In2 = 8;
  const int In3 = 7;
  const int In4 = 6;
  const int Ena = 3; 
  const int Enb = 11; 

//ultra sonic 
  const int trigPin = A4;
  const int echoPin = A5;
  const int DISTANCE_THRESHOLD (20); //cm


  long duration, cm;
    long microsecondsToCentimeters(long microseconds)
  {
    return microseconds / 29 / 2;
  }


  void setup() 

  {

//colour sensor
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);


//line sensor
      qtr.setTypeAnalog();
      qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3}, 4);
    



      //ultrasonic
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

      //H bridge 
    pinMode(In1, OUTPUT);
    pinMode(In2, OUTPUT);
    pinMode(In3, OUTPUT);
    pinMode(In4, OUTPUT);
  
  //motor speed
    pinMode(Ena, OUTPUT);
    pinMode(Enb, OUTPUT);
    analogWrite (Ena, 150);
    analogWrite (Enb, 150);

      //serial monitor 
    Serial.begin(9600);
  }

  void Rotate() 
  { //also pushes timmy
    //motor1
    digitalWrite (In1, HIGH);
    digitalWrite (In2, LOW);
    //motor2
    digitalWrite (In3, LOW);
    digitalWrite (In4, HIGH);
    

  }

  void Moveforward() { 
      //motor1
      
    digitalWrite (In1, HIGH);
    digitalWrite (In2, LOW);
    //motor2
    digitalWrite (In3, HIGH);
    digitalWrite (In4, LOW);

  }

  void Stop() {
 digitalWrite (In1, LOW);
    digitalWrite (In2, LOW);
    //motor2
    digitalWrite (In3, LOW);
    digitalWrite (In4, LOW);


  }


  void loop() {

    //clour sensor
   
  digitalWrite(S2,LOW);

  digitalWrite(S3,LOW);

 

  frequency = pulseIn(sensorOut, LOW);

  difference = frequency - green[0];


  if(abs(difference)<10){

    greenFlag[0] = true;

  }

  delay(100);

  


  digitalWrite(S2,HIGH);

  digitalWrite(S3,HIGH);



  frequency = pulseIn(sensorOut, LOW);

  difference = frequency - green[1];


  if(abs(difference)<10){

    greenFlag[1] = true;

  }

  delay(100);

  


  digitalWrite(S2,LOW);

  digitalWrite(S3,HIGH);

 

  frequency = pulseIn(sensorOut, LOW);

  difference = frequency - green[2];


  if(abs(difference)<10){

    greenFlag[2] = true;
   
  }

//1
  if (greenFlag[0] && greenFlag[1] && greenFlag[2]){

    Serial.println("It is green");

     Stop();

     delay(2000);
    //ultra sonic 
   digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); 
    digitalWrite(trigPin, LOW);
    
    duration = pulseIn(echoPin, HIGH, 25000);

    cm = microsecondsToCentimeters(duration);
    
    //Serial.print(cm);
    //Serial.print("cm");
    //Serial.println();  
    //delay(100);
  

    //motors 
     if(cm > 0 && cm < DISTANCE_THRESHOLD) {


  Moveforward();

  } else {
  Rotate();
  }

  



  }else{

    Serial.println("UNKOWN");
   
  

  
 //rest of code i havent made yet goes here

  }
 

  delay(1000);


    //line sensor
  qtr.read(SensorValues);
  for (uint8_t i = 0; i < SensorCount; i++)
  {  Serial.print(SensorValues[i]); 

    Serial.print('\t'); }
    
    delay(250);


  
  


  delay(100);
  
  }


