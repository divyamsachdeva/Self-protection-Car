#define LM1 3//7 // left motor M1 D1
#define LM2 2//8 // left motor M2 D2
#define RM1 5//3 // right motor M2 D3
#define RM2 4//4 // right motor M2 D4

//defining trig and echo pin
const int echopin = 6;
const int trigpin = 7;

//declaring time & dist variable
long duration;
int dist,r ;
int d2,i=0;

//for buzzer 
int b = 8;
int gnd = 9;

//for touch sensor
int ts= 10;

void setup() {
  // put your setup code here, to run once:
 
 //setting pinmode
 pinMode(LM1, OUTPUT);
 pinMode(LM2, OUTPUT);
 pinMode(RM1, OUTPUT);
 pinMode(RM2, OUTPUT);

 pinMode(b,OUTPUT);
 pinMode(gnd,OUTPUT);

 pinMode(trigpin,OUTPUT);
 pinMode(echopin,INPUT);
 pinMode(ts,INPUT);
 Serial.begin(115200); 
 digitalWrite(gnd,LOW);

 randomSeed(analogRead(A0));
}

int proxyread(int,int)
{
    //first giving trig a low value
  digitalWrite(trigpin,LOW);
  delayMicroseconds(2);

  //getting sound wave from it
  digitalWrite(trigpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin,LOW);

  //getting input from echo pin
  duration = pulseIn(echopin,HIGH);
  //calcuating distance
  dist = duration*0.017;

 return(dist);
}

void loop() {
  // put your main code here, to run repeatedly:
if(digitalRead(ts)==HIGH)
 {
   Serial.println("ts high");
   i++;
   delay(50);
 }
else Serial.println("ts low");

if (i%2==1)
{
  //car moving fwd
  digitalWrite(LM1, HIGH); 
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, LOW);
  delay(100);


  d2 = proxyread(trigpin,echopin);
  Serial.print("d2=");
  Serial.println(d2);


 if(d2<=10)
 {
  while(d2<=10)
  {  
  digitalWrite(LM1, LOW);                               //reverse
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
  d2 = proxyread(trigpin,echopin);
  Serial.println(d2);
    switch(d2)                                          //buzzer freq
    {
      case 10:{
               digitalWrite(b,HIGH);
               delay(30);
               digitalWrite(b,LOW);
               delay(570);
              }
              break;
          
      case 9:{
                digitalWrite(b,HIGH);
                delay(30);
                digitalWrite(b,LOW);
                delay(270);
             }
             break;
         
      case 8:{
                digitalWrite(b,HIGH);
                delay(30);
                digitalWrite(b,LOW);
                delay(120);
             }
             break;
         
      case 6:
      case 7:{
                digitalWrite(b,HIGH);
                delay(30);
                digitalWrite(b,LOW);
                delay(70);
             }
             break;

      case 5:
      case 4:
      case 3:
      case 2:
      case 1:{
                digitalWrite(b,HIGH);
                delay(30);
                digitalWrite(b,LOW);
                delay(30);
             }
             break;
      case 0: delay(1000); 
              break;
    }

  Serial.println("reverse");
  } 
  r  = random(0,2);
  Serial.print("r=");
  Serial.println(r);
  
  switch(r)
  {
    case 0: digitalWrite(LM1, HIGH);   //right
            digitalWrite(LM2, LOW);
            digitalWrite(RM1, LOW);
            digitalWrite(RM2, HIGH);
            delay(1200);
            Serial.println("turning right");        
            break;
    case 1: digitalWrite(LM1, LOW);     //left
            digitalWrite(LM2, HIGH);
            digitalWrite(RM1, HIGH);
            digitalWrite(RM2, LOW);
            delay(1200);
            Serial.println("turning left");        
            break;
  }
 }
}
else
{
   digitalWrite(LM1, LOW);     //stop
   digitalWrite(LM2, LOW);
   digitalWrite(RM1, LOW);
   digitalWrite(RM2, LOW);
}
}
