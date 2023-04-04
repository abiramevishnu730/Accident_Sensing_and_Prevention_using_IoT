#include <SoftwareSerial.h>
/* LCD RS pin to digital pin 8
 * LCD Enable pin to digital pin 9
 * LCD D4 pin to digital pin 10
 * LCD D5 pin to digital pin 11
 * LCD D6 pin to digital pin 12
 * LCD D7 pin to digital pin 13
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V*/
#include <LiquidCrystal.h>
const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
int m11=2;   // rear motor
int m12=3;
int m21=4;    // front motor
int m22=5;

int sen=0;

void backward()
{
   digitalWrite(m11, HIGH);
   digitalWrite(m12, LOW);
   digitalWrite(A3,HIGH);
   digitalWrite(A4,LOW);

}

void forward()
{
   digitalWrite(m11, LOW);
   digitalWrite(m12, HIGH);
   digitalWrite(A3,LOW);
   digitalWrite(A4,HIGH);
   
}

void Stop()
{
   digitalWrite(m11, LOW);
   digitalWrite(m12, LOW);
   digitalWrite(A3,LOW);
   digitalWrite(A4,LOW);

}

SoftwareSerial gsm(6,7);
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() 
{
  
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("SMART ALCOHOL");
  lcd.setCursor(0,1);
  lcd.print("DETECTION");
  delay(3000);
  gsm.begin(9600);
  Serial.begin(9600);
  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
  pinMode(m21, OUTPUT);
  pinMode(m22, OUTPUT);
  delay(5000);
  deviceInitialise();
}
void serialdata()
{
  while(gsm.available())
  {
    Serial.print(gsm.read());
  }
}
void loop() {
 sen=analogRead(A0);
 Serial.println(sen);
 delay(1000);
 
 
 
 if(sen>=400)
 { 
 
 Stop();
  lcd.clear();
   lcd.setCursor(0,0);
  lcd.print("DRIVER CONSUMING");
  lcd.setCursor(0,1);
  lcd.print("ALCOHOL");
  delay(1000);
  gsm.println("AT+HTTPPARA=\"URL\",\"http://www.isquaresoftware.com/hcc/alupdate.php?flag=1\"");
  delay(5000);
  serialData();
  gsm.println("AT+HTTPPARA=\"CID\",1");
  delay(5000);
  serialData();
  gsm.println("AT+HTTPACTION=0");
  delay(1000);
  delay(10000);

 }
 
// Serial.println(analogRead(A2));
 if(analogRead(A5)<=750)
 {
 
 forward();
 
  delay(1000);
 
 }
  
  
 //Serial.println(analogRead(A5)); 
 if(analogRead(A2)<=750)
 {
 
backward();
 
  delay(1000);
 
 }
  Stop();
}
void deviceInitialise()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("INITIALISING....");
  delay(5000);
  gsm.println("AT");
  delay(10000);
  serialData();
  gsm.println("AT+CGATT=1");
  delay(5000);
  serialData();
  gsm.println("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
  delay(5000);
  serialData();
  gsm.println("AT+SAPBR=3,1,\"APN\",\"internet\"");
  delay(5000);
  serialData();
  gsm.println("AT+SAPBR=1,1");
  delay(5000);
  serialData();
  gsm.println("AT+SAPBR=2,1");
  delay(5000);
  serialData();
  gsm.println("AT+HTTPINIT");
  delay(5000);
  serialData();
  lcd.setCursor(0,1);
  lcd.print("  READY TO USE  ");
}
void serialData()
{
  while(gsm.available()!=0)
  Serial.write(gsm.read());
}
