#include <SoftwareSerial.h>

#define LEFT_A1 5 //왼쪽 바퀴
#define LEFT_B1 6 //왼쪽 바퀴
const int ENA = 4;
#define RIGHT_A2 7 //오른쪽 바퀴
#define RIGHT_B2 8 //오른쪽 바퀴
const int ENB = 9;

#define tPin_f 10  //초음파센서 트리거
#define ePin_f 11

#define tPin_b 12  //후방초음파센서 트리거
#define ePin_b 13

//블루투스 PIN 설정
#define BLUE_TX 2 //블루투스 TX
#define BLUE_RX 3 //블루투스 RX

const int LED1 = A0;
const int LED2 = A1;
const int horn = A2;

int MOTOR_SPEED = 130;

SoftwareSerial mySerial(BLUE_TX, BLUE_RX);
char value;

void setup() {
  Serial.begin(9600);   //시리얼모니터
  mySerial.begin(9600); //블루투스 시리얼
  
  pinMode(LED1,OUTPUT); //led
  pinMode(LED2,OUTPUT);
  
  pinMode(horn,OUTPUT); //경적
  
  pinMode(LEFT_A1, OUTPUT);
  pinMode(RIGHT_A2, OUTPUT);
  pinMode(LEFT_B1, OUTPUT);
  pinMode(RIGHT_B2, OUTPUT);

  pinMode(tPin_f, OUTPUT);   //초음파센서 트리거핀을 출력모드로 설정합니다.
  pinMode(ePin_f, INPUT);    //초음파센서 에코핀을 입력모드로 설정합니다.
  digitalWrite(tPin_f, LOW); //초음파센서 트리거핀 LOW로 초기화

  pinMode(tPin_b, OUTPUT);   //초음파센서 트리거핀을 출력모드로 설정합니다.
  pinMode(ePin_b, INPUT);    //초음파센서 에코핀을 입력모드로 설정합니다.
  digitalWrite(tPin_b, LOW);
}

void loop() {
  long distance_f = 0, distance_b = 0;
  distance_f = howclose_f();
  distance_b = howclose_b();

  while (mySerial.available()) //mySerial에 전송된 값이 있으면
  {
    value = mySerial.read(); //전송값 읽음
    Serial.print(value);

    if (value == 'l') {          //좌회전
      left();
      analogWrite(LED2,255);
      delay(60);
      analogWrite(LED2,0);
      delay(60);
    }

    else if (value == 'r') {    //우회전
      
      right();
      analogWrite(LED1,255);
      delay(60);
      analogWrite(LED1,0);
      delay(60);
    }

    else if (value == 'f') {    //전진

      if (distance_f > 30) {
        forward();
      }
      
      else {
        stop();
        caution();
        Klaxon();
      }
    }

    else if (value == 'b') {    //후진

      if (distance_b > 30) {
        backward();
      }

      else {
        stop();
        caution();
        Klaxon();
      }
    }

    else if (value == 'C') {    //비상등
      
        analogWrite(LED1,255);
        analogWrite(LED2,255);
        delay(100);
        analogWrite(LED1,0);
        analogWrite(LED2,0);
        delay(100);
      
    }
    else if(value == 'c'){
        analogWrite(LED1,0);
        analogWrite(LED2,0);
    }
    
    else if (value == 'R') {    //우측 깜빡이
      analogWrite(LED1,255);
      delay(100);
      analogWrite(LED1,0);
      delay(100);
    }
    else if(value == 'E'){
        analogWrite(LED1,0);
    }
    
    else if (value == 'L') {    //좌측 깜빡이
      analogWrite(LED2,255);
      delay(100);
      analogWrite(LED2,0);
      delay(100);
    }
    else if(value == 'Q'){
        analogWrite(LED2,0);
    }
    
    else if(value == 'X'){    //경적
        tone(horn,494);
    }
    else if(value == 'x'){
        noTone(horn);
    }

    else if(value == 'Y'){    //자율주행
      
      
      if (distance_f > 30) {
        forward();
      }
      
      else {
        stop();
        caution();
        Klaxon();
      }
    }
    
    else if(value == 'y'){
        stop();
        caution();
        Klaxon();
    }
    
    else {
      stop();
      
    }
  }
}

void forward() {
  digitalWrite(LEFT_A1, LOW);
  digitalWrite(LEFT_B1, HIGH);
  digitalWrite(RIGHT_A2, LOW);
  digitalWrite(RIGHT_B2, HIGH);
  analogWrite(ENB, 195);
  analogWrite(ENA, 130);
}

void backward() {
  digitalWrite(LEFT_A1, HIGH);
  digitalWrite(LEFT_B1, LOW);
  digitalWrite(RIGHT_A2, HIGH);
  digitalWrite(RIGHT_B2, LOW);
  analogWrite(ENB, 195);
  analogWrite(ENA, 130);
}

void right() {
  digitalWrite(LEFT_A1, LOW);
  digitalWrite(LEFT_B1, HIGH);
  digitalWrite(RIGHT_A2, HIGH);
  digitalWrite(RIGHT_B2, LOW);
  analogWrite(ENB, 195);
  analogWrite(ENA, 130);
}

void left() {
  digitalWrite(LEFT_A1, HIGH);
  digitalWrite(LEFT_B1, LOW);
  digitalWrite(RIGHT_A2, LOW);
  digitalWrite(RIGHT_B2, HIGH);
  analogWrite(ENB, 195);
  analogWrite(ENA, 130);
}

void stop() {
  digitalWrite(LEFT_A1, HIGH);
  digitalWrite(LEFT_B1, HIGH);
  digitalWrite(RIGHT_A2, HIGH);
  digitalWrite(RIGHT_B2, HIGH);
  analogWrite(ENB, 0);
  analogWrite(ENA, 0);
}

void caution(){
  analogWrite(LED1,255);
  analogWrite(LED2,255);
  delay(100);
  analogWrite(LED1,0);
  analogWrite(LED2,0);
}
void Klaxon(){
  tone(horn,494);
  delay(20);
  noTone(horn);
}
long howclose_f() //초음파 센서 거리측정 함수
{
  long duration = 0, distance = 0;  //echo펄스 도달시간 변수와 거리 변수 선언
  digitalWrite(tPin_f, HIGH);  //Trig 핀 HIGH로 변경하여 신호 발생
  delayMicroseconds(10);            //10us 유지
  digitalWrite(tPin_f, LOW);   //Trig 핀 LOW로 초기화
  duration = pulseIn(ePin_f, HIGH);  //pulseIn함수가 호출되고 펄스가 입력될 때까지의 시간. us단위로 값을 리턴.
  distance = duration / 29 / 2;     //센치미터로 환산
  return distance;                  //측정 거리값 리턴
}

long howclose_b() //초음파 센서 거리측정 함수
{
  long duration = 0, distance = 0;  //echo펄스 도달시간 변수와 거리 변수 선언
  digitalWrite(tPin_b, HIGH);  //Trig 핀 HIGH로 변경하여 신호 발생
  delayMicroseconds(10);            //10us 유지
  digitalWrite(tPin_b, LOW);   //Trig 핀 LOW로 초기화
  duration = pulseIn(ePin_b, HIGH);  //pulseIn함수가 호출되고 펄스가 입력될 때까지의 시간. us단위로 값을 리턴.
  distance = duration / 29 / 2;     //센치미터로 환산
  return distance;                  //측정 거리값 리턴
}
