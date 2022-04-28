
// pin no. connected to segment
int segpin[7] = {2,3,4,5,6,7,8}; 
//                a, b, c,  d,  e,  f, g

// pin no. connected to digit
int dpin[4] = {10, 11, 12, 13};
//       pin  d4,d3,d2,d1

//          segment        a, b, c, d, e, f, g    number
const int arr[10][7] = {  {1, 1, 1, 1, 1, 1, 0},   //0
                          {0, 1, 1, 0, 0, 0, 0},   //1
                          {1, 1, 0, 1, 1, 0, 1},   //2
                          {1, 1, 1, 1, 0, 0, 1},   //3
                          {0, 1, 1, 0, 0, 1, 1},   //4
                          {1, 0, 1, 1, 0, 1, 1},   //5
                          {1, 0, 1, 1, 1, 1, 1},   //6
                          {1, 1, 1, 0, 0, 0, 0},   //7
                          {1, 1, 1, 1, 1, 1, 1},   //8
                          {1, 1, 1, 1, 0, 1, 1} //9
                  };

int timer=100;

void setup() 
{                
  Serial.begin(9600);     // baud rate = 9600
  
  for (int i=0; i<7; i++)
  { pinMode(segpin[i], OUTPUT); }
  
  for(int j=0;j<4;j++)
  { pinMode(dpin[j], OUTPUT); }
}

void loop()
{
  Serial.print("Enter number to be displayed: ");
  
  while(Serial.available()== 0) { }
  
  int num = (Serial.parseInt());
  Serial.println(num); 
  
  int d0 = num %10 ;              //digit at ones place
  int d1 = (num % 100) / 10 ;     //digit at tens place
  int d2 = (num % 1000) / 100;    //digit at hundreds place
  int d3 = num / 1000;            //digit at thousands place

  for(int k=0; k<timer; k++)
  {
  digitalWrite(dpin[0], LOW);
  digitalWrite(dpin[1], HIGH);
  digitalWrite(dpin[2], HIGH);
  digitalWrite(dpin[3], HIGH);
  
  for (int i= 0 ; i<7 ; i++)  
  { digitalWrite(segpin[i], arr[d3][i]); }
  delay(5);

  digitalWrite(dpin[0], HIGH);
  digitalWrite(dpin[1], LOW);
  digitalWrite(dpin[2], HIGH);
  digitalWrite(dpin[3], HIGH);

  for (int i= 0 ; i<7 ; i++)  
  { digitalWrite(segpin[i], arr[d2][i]); }
  delay(5);

  digitalWrite(dpin[0], HIGH);
  digitalWrite(dpin[1], HIGH);
  digitalWrite(dpin[2], LOW);
  digitalWrite(dpin[3], HIGH);

  for (int i= 0 ; i<7 ; i++)  
  { digitalWrite(segpin[i], arr[d1][i]); }
  delay(5); 

  digitalWrite(dpin[0], HIGH);
  digitalWrite(dpin[1], HIGH);
  digitalWrite(dpin[2], HIGH);
  digitalWrite(dpin[3], LOW);
  

  for (int i= 0 ; i<7 ; i++)  
  { digitalWrite(segpin[i], arr[d0][i]); }
  delay(5); 
  }
   for(int j=0;j<4;j++)
  { digitalWrite(dpin[j], HIGH); }
  if(Serial.available())  // PC로부터 받은 데이터가 있나요~?
  {
    char recv_data = Serial.read(); // 수신받은 데이터 중 1byte를 읽어요~!
  
      }
    }
