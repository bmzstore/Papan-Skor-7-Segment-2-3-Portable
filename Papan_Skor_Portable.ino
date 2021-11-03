#include "Wire.h"
#include "EEPROM.h"
#define Data 5
#define Clk  6
#define Ser  7

byte digit1[11] = {0xFC, 0x50  , 0xBA, 0xDA, 0x56, 0xCE, 0xEE, 0x58, 0xFE, 0xDE};//2,3 Inch

int UpKiri     = A0;
int DownKiri   = A1;
int UpKanan    = A3;
int DownKanan  = A5;
int Reset      = A2;
int Buzzer = 12;
int Satuan1,Puluhan1,Satuan2,Puluhan2;
int SkorKiri,SkorKanan;

unsigned long Angka = 0;

void setup(){
  pinMode(Data, OUTPUT);
  pinMode(Clk, OUTPUT);
  pinMode(Ser, OUTPUT);
  pinMode(UpKiri, INPUT_PULLUP);
  pinMode(DownKiri, INPUT_PULLUP);
  pinMode(UpKanan, INPUT_PULLUP);
  pinMode(DownKanan, INPUT_PULLUP);
  pinMode(Reset, INPUT_PULLUP);
  pinMode(Buzzer, OUTPUT);
  SkorKiri = EEPROM.read(0);
  SkorKanan = EEPROM.read(1);
   EEPROM.write(0,SkorKiri);
   EEPROM.write(1,SkorKanan);

  digitalWrite(Buzzer, HIGH);
  delay(100);
  digitalWrite(Buzzer, LOW);
  delay(100);
  digitalWrite(Buzzer, HIGH);
  delay(100);
  digitalWrite(Buzzer, LOW);
  delay(100);
  
}

void loop(){
    Satuan1      = SkorKiri % 10/1;        
    Puluhan1     = SkorKiri % 100/10;        
    Satuan2      = SkorKanan % 10/1;
    Puluhan2     = SkorKanan % 100/10;

    if(digitalRead(UpKiri)==LOW){
      digitalWrite(Buzzer, HIGH);
      delay(500);
      SkorKiri++;
      EEPROM.write(0,SkorKiri);
       }else{
        digitalWrite(Buzzer, LOW);
       }

    if(digitalRead(DownKiri)==LOW){
      digitalWrite(Buzzer, HIGH);
      delay(500);
      SkorKiri--;
      EEPROM.write(1,SkorKiri);
       }else{
        digitalWrite(Buzzer, LOW);
       }


   if(digitalRead(UpKanan)==LOW){
    digitalWrite(Buzzer, HIGH);
      delay(500);
      SkorKanan++;
      EEPROM.write(1,SkorKanan);
       }else{
        digitalWrite(Buzzer, LOW);
       }

       
    if(digitalRead(DownKanan)==LOW){
      digitalWrite(Buzzer, HIGH);
      delay(500);
      SkorKanan--;
      EEPROM.write(0,SkorKanan);
       }else{
        digitalWrite(Buzzer, LOW);
       }

       
     if(digitalRead(Reset)==LOW ){
      digitalWrite(Buzzer, HIGH);
    delay(1000);
      SkorKiri=0;
      SkorKanan=0;
        EEPROM.write(0,SkorKiri);
        EEPROM.write(1,SkorKanan);
    }else{
        digitalWrite(Buzzer, LOW);
       }
       
    if(SkorKiri>99){
    SkorKiri=99;
   }
   if(SkorKiri<00){
    SkorKiri=00;
   }
   if(SkorKanan>99){
    SkorKanan=99;
   }
   if(SkorKanan<00){
    SkorKanan=00;
   }
   
    {           
    digitalWrite(Ser, LOW);
    shiftOut(Data, Clk, MSBFIRST, digit1[Satuan2]);
    shiftOut(Data, Clk, MSBFIRST, digit1[Puluhan2]);
    shiftOut(Data, Clk, MSBFIRST, digit1[Satuan1]);
    shiftOut(Data, Clk, MSBFIRST, digit1[Puluhan1]);
    digitalWrite(Ser, HIGH);
    
        }
      }
