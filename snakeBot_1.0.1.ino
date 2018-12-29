//SNAKE BOT
#include<Servo.h>
Servo S[10];

int error[10] = {0,15,0,45,35,-45,-25,60,55,0};
int i=0, j = 5;


void mov(int motor, int angle)
{
  S[motor].write(angle - error[motor]);  
}

void straight()
{
  for(i=0;i<10;i++)
    {
      S[i].write(90-error[i]);
    }
          delay(250);
}

void wave()
{
  
  for(i=35;i<120;i+=25)
  {
  mov(9,20+i);
  mov(7,40+i);
  mov(5,60+i);
  mov(3,90+i);
  delay(300);
  }
  straight();  
  delay(500);
}

void zigzag()
{
  for(i=0;i<10;i++)
  {
    if(i%2)
      mov(i,30);
    else 
    mov(i,150);
  }
delay(300);
}

void fang()
{
  mov(7,0);
  mov(9,170);
  delay(100);
  for(i=0;i<150;i+=5)
  {
    mov(8,i);
    mov(6,160-i);
    delay(1000);
  }
 straight();
}

void setup() {
    for(i=2;i<12;i++)
    S[i-2].attach(i);
}

void loop() 
{
//  zigzag();
  straight();
//  wave();
//  fang();
}
