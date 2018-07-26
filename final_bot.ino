#include<Servo.h>
Servo S[10];         //array of servos

int error[10] = {0,15,0,-15,55,-30,25,60,45,0};              //physical error in snake bot
int i, j = 5;

#include <SoftwareSerial.h>                   //for UART Serial communications

#include <TinyGPS.h> 
float lat = 28.5458,lon = 77.1703;            // create variable for latitude and longitude object  
SoftwareSerial gpsSerial(3,4);                //rx,tx 
int smokeA0 = A5;                             //Analog input of gas sensor
// Your threshold value                      
int sensorThres = 400;                        //minimum amount of gas safe for us
TinyGPS gps; // create gps object                 
void mov(int motor, int angle)
{
  S[motor].write(angle - error[motor]);         //movement of snake along a curve
}

void straight()                                //movement of snake along a straight line
{
  for(i=0;i<10;i++)
    {
      S[i].write(90-error[i]);
    }
          delay(250);
}

void wave()                                 //movement of snake along a wave curve
{
  
  for(i=35;i<120;i+=10)
  {
  mov(9,20+i);
  mov(7,40+i);
  mov(5,60+i);
  mov(3,90+i);
  delay(300);
  }
  straight();  
  delay(2000);
}

void zigzag()                               //zig zag movement
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
void stopbot(){                               //to stop the bot in its position
  for(int i=0;i<10;i++){
    S[i].detach();
  }
}
void setup(){ 
  pinMode(smokeA0, INPUT);
Serial.begin(9600); // connect serial 
Serial1.begin(9600);
Serial2.begin(9600);
//Serial.println("The GPS Received Signal:"); 
gpsSerial.begin(9600); // connect gps sensor 

//Attaching Pins.

S[0].attach(2);

for(int i = 1 ; i<10 ; i++)
  S[i].attach(i+4);
} 

void attachRefresh(){
  //Attaching Pins.

S[0].attach(2);

for(int i = 1 ; i<10 ; i++)
  S[i].attach(i+4);
}

void loop(){ 
  int analogSensor = analogRead(smokeA0);                   //analog value of gas sensor
  while(gpsSerial.available()){                            // check for gps data 
  if(gps.encode(gpsSerial.read()))                        // encode gps data 
  {  
  gps.f_get_position(&lat,&lon);                        // get latitude and longitude 
  // display position 
  
  Serial.println("GPS Signal"); 
  
  Serial.print("LAT:"); 
  Serial.println(lat); 

  Serial.print(",LON:"); 
  Serial.println(lon); 
 }
}
String latitude = String(lat,6);                                      //variable of latitude 
  String longitude = String(lon,6);                                  //variable of longitude
Serial.println("LATITUDE-"+latitude+";"+"LONGITUDE-"+longitude);      //to display the latitude on SERIAL MONITOR
delay(1000); 
if(Serial.available()>0){                                           //checking for the bluetooth to give command of any movement
char  d=Serial.read();
  Serial.println(d);
  if(d=='B'){                                                    //here B is the bit sent by the mobile to the bluetooth module
    while(d=='B'){
    zigzag();
  straight();                                                   //all the movements
  wave();
  fang();
  Serial.println("MOVING");
  }
  }
  else if(d=='D'){                                            //checking the SENT bit id 'D' or not
    while(d=='D'){
    stopbot();
    attachRefresh();                                          //stops the snake bot
    Serial.println("STOP");
  }
  }
}
Serial.print("Pin A0: "+analogSensor);                
if (analogSensor > sensorThres)
  {
    Serial.println("DANGER");                                   //tells that gas there are more than expected,so its DANGER to stay there
    
  }
  else
  {
    Serial.println("SAFE");                                   //Normal or under amount of gass in the atmosphere
    
  }
  delay(100);
} 
