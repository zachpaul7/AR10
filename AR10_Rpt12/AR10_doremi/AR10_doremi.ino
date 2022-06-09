/*
 예제 9.1
 피에조 부저를 이용한 소리 출력
*/
int pin_switch[] = {13 ,12, 11};
int buzzerPin = 9;
int frequencies[] = {262,330,392};

void setup() 
{
  for(int i = 0; i<3; ++i){
    pinMode(pin_switch[i],INPUT_PULLUP);
  }
  // 부저핀을 출력으로 설정한다
  pinMode(buzzerPin, OUTPUT);
}


void loop() 
{
  for (int i = 0; i < 3; ++i){
    if (!digitalRead(pin_switch[i])){
      // 맞는 값을 찾았을 경우 이 값을 회신한다
      tone(buzzerPin,frequencies[i],100);
    };
  };
}
