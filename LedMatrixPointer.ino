
#include "LedControl.h"
LedControl lc = LedControl(12,11,10,0);
int VRx = A0;
int VRy = A1;
int SW = 2;

int i = 0;
int j = 0;
int adr = 3;

int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
int mapX = 0;
int sp = 200;
int mapY = 0;

void setup() {
  Serial.begin(9600); 
  for(int index=0;index<lc.getDeviceCount();index++) {
        lc.shutdown(index,false); 
        lc.setIntensity(index,6);
    } 
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP); 
  sp = 200;
}

void loop() {
  
  
  //int adr = 3;
  lc.setLed(adr,i,j,true);
  
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
   SW_state = digitalRead(SW);
  
  
  SW_state = digitalRead(SW);
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);
  lc.setLed(adr,i,j,false);
   if(mapY>100)
  {
    lc.setLed(adr,i,j,false);
    j--;
    
    if(j==-1)
    {
      if(adr<4 && adr>=0)
      {
        adr++;
        j=7;
        }

       if(adr>3)
       {
        //j=7;
        adr=3;
        j=0;
        } 
    }
    }
    lc.setLed(adr,i,j,true);
    
if(mapY<-100)
  {
    lc.setLed(adr,i,j,false);
    j++;
    if(j==8)
    {
      if(adr<4 && adr>0)
      {
        adr--;
        j=0;
      }
        else
       {
        adr=0;
        j=7;
       } 

       
    }

   
    }
    lc.setLed(adr,i,j,true);

  
if(mapX>50)
  {
    lc.setLed(adr,i,j,false);
    i++;
    if(i==8)
    {
      i=7;
    }
    }
    lc.setLed(adr,i,j,true);

    if(mapX<-50)
  {
    lc.setLed(adr,i,j,false);
    i--;
    if(i==-1)
    {
      i=0;
    }
    }
    lc.setLed(adr,i,j,true);
  
  Serial.print("X: ");
  Serial.print(mapX);
  Serial.print(" | Y: ");
  Serial.print(mapY);
  Serial.print("\n");
  

  delay(30);
  
}
