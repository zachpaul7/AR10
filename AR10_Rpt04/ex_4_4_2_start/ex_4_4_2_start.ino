/*
 예제 4.4.2
 74595를 이용하여 FND 제어 0~9까지 
 1초단위로 표시하기
*/
 
 // 0~9까지 LED 표시를 위한 상수 설정
const byte number[10] = {
//dot  gfedcba
  B11000000,    //0
  B11111001,    //1
  B10100100,    //2
  B10110000,    //3
  B10011001,    //4
  B10010010,    //5
  B10000010,    //6
  B11111000,    //7
  B10000000,    //8
  B10010000,	//9
};

int ds = 2;
int shcp = 3;
int stcp = 4;

 // 74595의 DS핀을 Arduino의 2번핀에 연결
  // 74595의 STCP핀을 Arduino의 3번핀에 연결
  // 74595의 SHSP핀을 Arduino의 4번핀에 연결

void setup()
{
  // 2~9번핀을 출력으로 초기화 시킨다.
  for(int i = 2; i <= 9; ++i){
    pinMode(i,OUTPUT);
  };
  digitalWrite(9,LOW);	// 점은 표시하지 않는다
}

void loop()
{
   // k값을 0~9로 변화시킨다.
  for(int k = 0; k <= 9; ++k){
   fndDisplay74595(k);  // k값을 출력한다
   delay(1000);         // 1초간 지연시킨다.         
  };
} 

// LED 점등
void fndDisplay74595(int displayValue){
  digitalWrite(stcp,LOW);// STCP에 LOW 신호를 보내서 74595로 데이터전송을 시작한다.
  
  shiftOut(ds,shcp,MSBFIRST,number[displayValue]);// shiftOut 명령어로 74595에 출력을 보낸다.
  
  digitalWrite(stcp,HIGH);// STCP에 HIGH 신호를 보내서 74595로 데이터전송을 종료한다.
  
}
