#include <VirtualWire.h>
#include <Ultrasonic.h>

#define trig1  8
#define echo1  9
#define trig2  10
#define echo2  11
#define trig3  12
#define echo3  13
#define trig4  7
#define echo4  6
Ultrasonic ultrasonic1(trig1, echo1);
Ultrasonic ultrasonic2(trig2, echo2);
Ultrasonic ultrasonic3(trig3, echo3);
Ultrasonic ultrasonic4(trig4, echo4);
const int ledPin1 = A3;
const int ledPin2 = A2;
const int ledPin3 = A1;
const int ledPin4 = A0;
char *data="0";
int a = 0;
int b = 0;
int c = 0;
int d = 0;
void setup() 
{
  Serial.begin(9600);
  pinMode(ledPin1,OUTPUT);
  pinMode(ledPin2,OUTPUT);
  pinMode(ledPin3,OUTPUT);
  pinMode(ledPin4,OUTPUT); 
  vw_set_ptt_inverted(true);
  vw_set_tx_pin(5);
  vw_setup(4000);
  Serial.println("Initialising..!!");
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(trig3, OUTPUT);
  pinMode(echo3, INPUT);
  pinMode(trig4, OUTPUT);
  pinMode(echo4, INPUT);
}

void loop()
{
   long duration1, distance1; 
  digitalWrite(trig1, LOW);  
  delayMicroseconds(2);
  digitalWrite(trig1, HIGH);  
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);
  duration1 = pulseIn(echo1, HIGH);
  distance1 = (duration1/2) / 29.1;

  long duration2, distance2; 
  digitalWrite(trig2, LOW);  
  delayMicroseconds(2);
  digitalWrite(trig2, HIGH);  
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);
  duration2 = pulseIn(echo2, HIGH);
  distance2 = (duration2/2) / 29.1;  

  long duration3, distance3;
  digitalWrite(trig3, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trig3, HIGH);  
  delayMicroseconds(10); 
  digitalWrite(trig3, LOW);
  duration3 = pulseIn(echo3, HIGH);
  distance3 = (duration3/2) / 29.1;
  
  long duration4, distance4;
  digitalWrite(trig4, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trig4, HIGH);  
  delayMicroseconds(10); 
  digitalWrite(trig4, LOW);
  duration4 = pulseIn(echo4, HIGH);
  distance4 = (duration4/2) / 29.1;
  
  if (distance1 < 30)
  { 
    
      data = "1";
      digitalWrite(ledPin1,255);
      Serial.println("Obstacle Ahead");          
  }
  else if (distance2 < 30)
  {
       data = "1";
       digitalWrite(ledPin2,255);
       Serial.println("Obstacle Behind");    
  }
  else if (distance3 < 30)
  {
       data = "1";
       digitalWrite(ledPin3,255);
       Serial.println("Obstacle on your left");      
  }
  else if (distance4 < 30)
  {
       data = "1";
       analogWrite(ledPin4,255);
       Serial.println("Obstacle on your right");
   }
  else 
  {
  data = "0";
  digitalWrite(ledPin1,LOW);
  digitalWrite(ledPin2,LOW);
  digitalWrite(ledPin3,LOW);
  digitalWrite(ledPin4,LOW);
  Serial.println("Gentleman, you are safe");
  }
  
  if(data == "1")
  {
   vw_send((uint8_t *)data, strlen(data));
   vw_wait_tx();
   Serial.println(data);
   
  }
  else if(data=="0"){
  vw_send((uint8_t *)data, strlen(data));
  vw_wait_tx(); 
  Serial.println(data);
  
}
}
