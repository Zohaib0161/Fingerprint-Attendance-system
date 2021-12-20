

//---------------------------------------------
//           INCLUDING LIBRARIES 
//---------------------------------------------

#include "Adafruit_Fingerprint.h"         //Library for fingure print sensor
#include<EEPROM.h>                       //library to store data in arduino 
#include <LiquidCrystal_I2C.h>               //Library for LCD
#include <SoftwareSerial.h>            //Libary to start serial communication 
#include <Wire.h>                     //Library for serial wire communication
#include <Servo.h>

//----------------------------------------------
//           INITIALIZE LIBRARIES 
//----------------------------------------------


LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);                                 //Initialise LCD pins
SoftwareSerial fingerPrint(2, 3);                                   //initialize fingureprint sensor pins
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fingerPrint);  //fingure print library initialization
                                                  
 
uint8_t MY_ID;

//---------------------------------------------
//            DEFINING PIN NUBERS 
//---------------------------------------------
#define MTC 5       
#define indFinger 7

#define R_B 13      //A0
#define DLT_ok 12   //A1
#define FWD 8      //A2
#define REV 7      //A3

 
#define records 10 // 10 for 10 no of users
int user1,user2,user3,user4,user5,user6,user7,user8,user9,user10;
 


 //---------------------------------------------
//               SETUP
//---------------------------------------------
void setup()
{
delay(1000);
lcd.begin(16, 2);    //begining lcd
lcd.backlight();
Serial.begin(9600); //begining serial monitor

//---------------------------------------------
//            DEFINING PIN MODES
//---------------------------------------------
pinMode(R_B, INPUT_PULLUP);
pinMode(FWD, INPUT_PULLUP);
pinMode(REV, INPUT_PULLUP);
pinMode(DLT_ok, INPUT_PULLUP);
pinMode(MTC, INPUT_PULLUP);

pinMode(indFinger, OUTPUT);


// CONDITION TO CHECK IF USER IS ENROLLED OR NOT
if(digitalRead(R_B) == 0)
{

lcd.clear();
lcd.print("Wait!!...");
lcd.setCursor(0,1);
lcd.print("Extracting Data");
 
Serial.println("Wait!!...");
Serial.println("Extracting Data");
Serial.println();
 
Serial.print("Serial No:");
for(int i=0;i<records;i++)
{

Serial.print("  ID:");
Serial.print(i+1);
Serial.print(" ");
}
Serial.println();
int eepIndex=0;           
for(int i=0;i<30;i++)         //LOOOP RUNINNG FOR 30 TIMES O CHECK ALL THE INDEXES FOR ID
{
if(i+1<10)
Serial.print('0');
Serial.print(i+1);
Serial.print(" ");
eepIndex=(i*7);
download(eepIndex);
eepIndex=(i*7)+210;
download(eepIndex);
eepIndex=(i*7)+420;
download(eepIndex);
eepIndex=(i*7)+630;
download(eepIndex);
eepIndex=(i*7)+840;
download(eepIndex);
eepIndex=(i*7)+1050;
download(eepIndex);
eepIndex=(i*7)+1260;
download(eepIndex);
eepIndex=(i*7)+1470;
download(eepIndex);
eepIndex=(i*7)+1680;
download(eepIndex);
Serial.println();
}
}
if(digitalRead(DLT_ok) == 0)             //CONDITION TO DELETE THE ID
{
lcd.clear();
lcd.print("Wait!!!");
lcd.setCursor(0,1);
lcd.print("Reseting.....");
for(int i=1000;i<1005;i++)
EEPROM.write(i,0);                  //WRITING ON EPROM MEMORY
for(int i=0;i<841;i++)
EEPROM.write(i, 0xff);
lcd.clear();
lcd.print("RESET DONE");
delay(1000);
}
 
lcd.clear();
lcd.print(" Fingerprint ");
lcd.setCursor(0,1);
lcd.print("COLLECTION SYSTEM");
delay(2000);
lcd.clear();
 

//comparing it with our current records
for(int i=1000;i<1000+records;i++)

{
if(EEPROM.read(i) == 0xff)
EEPROM.write(i,0);
}
 
finger.begin(57600);
Serial.begin(9600);
lcd.clear();
lcd.print("Finding Sensor..");
lcd.setCursor(0,1);
delay(2000);
if (finger.verifyPassword())
{
Serial.println("Sensor Found..");
lcd.clear();
lcd.print("Sensor Found");
delay(2000);
}
else
{
Serial.println("Did not find fingerprint sensor :(");
lcd.clear();
lcd.print("SENSOR Not Found");
lcd.setCursor(0,1);
lcd.print("Check Wiring!");
while (1);
}
 
lcd.setCursor(0,0);
lcd.print(" Press Match to ");
lcd.setCursor(0,1);
lcd.print(" Start System");
delay(3000);
 //reading the arduino eeprom memmory
user1=EEPROM.read(1000);
user2=EEPROM.read(1001);
user3=EEPROM.read(1002);
user4=EEPROM.read(1003);
user5=EEPROM.read(1004);
lcd.clear();
digitalWrite(indFinger, HIGH);
 
}

//---------------------------------------------
//            loop
//---------------------------------------------
void loop()
{


lcd.setCursor(0,0);
lcd.print("PRESS....     ");
lcd.setCursor(0,1);
lcd.print("BUTTONS TO START   ");
//get fingure print data
int result=getFingerprintIDez();
if(result>0)
{
digitalWrite(indFinger, LOW);

lcd.clear();
lcd.print("ID:");
lcd.print(result);
lcd.setCursor(0,1);
lcd.print("Please Wait....");
delay(1000);
attendance(result);
lcd.clear();
lcd.print("Attendance ");
lcd.setCursor(0,1);
lcd.print("Registered");
delay(1000);
digitalWrite(indFinger, HIGH);
return;
}
checkKeys();
delay(300);
}
 
//---------------------------------------------
//            ATTENDACE FUNCTION 
//---------------------------------------------
void attendance(int MY_ID)
{
int user=0,eepLoc=0;

//CHECK ID AND WRITE YOUR ID ON REGISTORS FOR 10 USERS
if(MY_ID == 1)
{
eepLoc=0;
user=user1++;
}
else if(MY_ID == 2)
{
eepLoc=210;
user=user2++;
}
else if(MY_ID == 3)
{
eepLoc=420;
user=user3++;
}
else if(MY_ID == 4)
{
eepLoc=630;
user=user4++;
}
else if(MY_ID == 5)
{
eepLoc=0;
user=user5++;
}
else if(MY_ID == 6)
{
eepLoc=840;
user=user5++;
}
else if(MY_ID == 7)
{
eepLoc=1050;
user=user7++;
}
else if(MY_ID == 8)
{
eepLoc=1260;
user=user8++;
}
else if(MY_ID == 9)
{
eepLoc=1470;
user=user9++;
}
else if(MY_ID == 10)
{
eepLoc=1680;
user=user8++;
}

else
return;


 //WRITING USER IDS ON ARDUINO EMROM MEMMORY
EEPROM.write(1000,user1);
EEPROM.write(1001,user2);
EEPROM.write(1002,user3);
EEPROM.write(1003,user4);

}


 //FUNCTION TO CHECK IF YOUR IS IA MATCHED OR NOT
void checkKeys()
{
if(digitalRead(R_B) == 0)
{
lcd.clear();
lcd.print("Please Wait");
delay(1000);
while(digitalRead(R_B) == 0);
Enroll();
}
 
else if(digitalRead(DLT_ok) == 0)
{
lcd.clear();
lcd.print("Please Wait");
delay(1000);
delet();
}
}
 //FUNCTION TO ENROLL THE ID OF NEW USER
 
void Enroll()
{
int count=1;
lcd.clear();
lcd.print("Enter Finger ID:");
 
while(1)
{
lcd.setCursor(0,1);
lcd.print(count);
if(digitalRead(FWD) == 0)
{
count++;
if(count>records)
count=1;
delay(500);
}
 
else if(digitalRead(REV) == 0)
{
count--;
if(count<1)
count=records;
delay(500);
}
else if(digitalRead(DLT_ok) == 0)
{
MY_ID=count;
getFingerprintEnroll();
for(int i=0;i<records;i++)
{
if(EEPROM.read(i) != 0xff)
{
EEPROM.write(i, MY_ID);
break;
}
}
return;
}
 
else if(digitalRead(R_B) == 0)
{
return;
}
}
}


//FUNCTION TO DELETE THE USER
 
void delet()
{
int count=1;
lcd.clear();
lcd.print("Enter Finger ID");
 
while(1)
{
lcd.setCursor(0,1);
lcd.print(count);
if(digitalRead(FWD) == 0)
{
count++;
if(count>records)
count=1;
delay(500);
}
 
else if(digitalRead(REV) == 0)
{
count--;
if(count<1)
count=records;
delay(500);
}
else if(digitalRead(DLT_ok) == 0)
{
MY_ID=count;
deleteFingerprint(MY_ID);
for(int i=0;i<records;i++)
{
if(EEPROM.read(i) == MY_ID)
{
EEPROM.write(i, 0xff);
break;
}
}
return;
}
 
else if(digitalRead(R_B) == 0)
{
return;
}
}
}
 
uint8_t getFingerprintEnroll()
{
int p = -1;
lcd.clear();
lcd.print("finger ID:");
lcd.print(MY_ID);
lcd.setCursor(0,1);
lcd.print("Place Finger");
delay(2000);
while (p != FINGERPRINT_OK)
{
p = finger.getImage();
switch (p)
{
case FINGERPRINT_OK:
Serial.println("Image taken");
lcd.clear();
lcd.print("Image taken");
break;
case FINGERPRINT_NOFINGER:
Serial.println("No Finger");
lcd.clear();
lcd.print("No Finger Found");
break;
case FINGERPRINT_PACKETRECIEVEERR:
Serial.println("Communication error");
lcd.clear();
lcd.print("Comm Error");
break;
case FINGERPRINT_IMAGEFAIL:
Serial.println("Imaging error");
lcd.clear();
lcd.print("Imaging Error");
break;
default:
Serial.println("Unknown error");
lcd.clear();
lcd.print("Unknown Error");
break;
}
}
 
// OK success!
 
p = finger.image2Tz(1);
switch (p) {
case FINGERPRINT_OK:
Serial.println("Image converted");
lcd.clear();
lcd.print("Image converted");
break;
case FINGERPRINT_IMAGEMESS:
Serial.println("Image too messy");
lcd.clear();
lcd.print("Image too messy");
return p;
case FINGERPRINT_PACKETRECIEVEERR:
Serial.println("Communication error");
lcd.clear();
lcd.print("Comm Error");
return p;
case FINGERPRINT_FEATUREFAIL:
Serial.println("Could not find fingerprint features");
lcd.clear();
lcd.print("Feature Not Found");
return p;
case FINGERPRINT_INVALIDIMAGE:
Serial.println("Could not find fingerprint features");
lcd.clear();
lcd.print("Feature Not Found");
return p;
default:
Serial.println("Unknown error");
lcd.clear();
lcd.print("Unknown Error");
return p;
}
 
Serial.println("Remove finger");
lcd.clear();
lcd.print("Remove Finger");
delay(2000);
p = 0;
while (p != FINGERPRINT_NOFINGER) {
p = finger.getImage();
}
Serial.print("ID "); Serial.println(MY_ID);
p = -1;
Serial.println("Place same finger again");
lcd.clear();
lcd.print("Place Finger");
lcd.setCursor(0,1);
lcd.print(" Again");
while (p != FINGERPRINT_OK) {
p = finger.getImage();
switch (p) {
case FINGERPRINT_OK:
Serial.println("Image taken");
break;
case FINGERPRINT_NOFINGER:
Serial.print(".");
break;
case FINGERPRINT_PACKETRECIEVEERR:
Serial.println("Communication error");
break;
case FINGERPRINT_IMAGEFAIL:
Serial.println("Imaging error");
break;
default:
Serial.println("Unknown error");
return;
}
}
 
// OK success!
 
p = finger.image2Tz(2);
switch (p) {
case FINGERPRINT_OK:
Serial.println("Image converted");
break;
case FINGERPRINT_IMAGEMESS:
Serial.println("Image too messy");
return p;
case FINGERPRINT_PACKETRECIEVEERR:
Serial.println("Communication error");
return p;
case FINGERPRINT_FEATUREFAIL:
Serial.println("Could not find fingerprint features");
return p;
case FINGERPRINT_INVALIDIMAGE:
Serial.println("Could not find fingerprint features");
return p;
default:
Serial.println("Unknown error");
return p;
}
 
// OK converted!
Serial.print("Creating model for #"); Serial.println(MY_ID);
 
p = finger.createModel();
if (p == FINGERPRINT_OK) {
Serial.println("Prints matched!");
} else if (p == FINGERPRINT_PACKETRECIEVEERR) {
Serial.println("Communication error");
return p;
} else if (p == FINGERPRINT_ENROLLMISMATCH) {
Serial.println("Fingerprints did not match");
return p;
} else {
Serial.println("Unknown error");
return p;
}
 
Serial.print("ID "); Serial.println(MY_ID);
p = finger.storeModel(MY_ID);
if (p == FINGERPRINT_OK) {
Serial.println("Stored!");
lcd.clear();
lcd.print(" Finger Stored!");
delay(2000);
} else if (p == FINGERPRINT_PACKETRECIEVEERR) {
Serial.println("Communication error");
return p;
} else if (p == FINGERPRINT_BADLOCATION) {
Serial.println("Could not store in that location");
return p;
} else if (p == FINGERPRINT_FLASHERR) {
Serial.println("Error writing to flash");
return p;
}
else {
Serial.println("Unknown error");
return p;
}
}
 //FUNCTION TO DIPLAY THE ENROLMENT PROCEDURE
int getFingerprintIDez()
{
uint8_t p = finger.getImage();
 
if (p != FINGERPRINT_OK)
return -1;
 
p = finger.image2Tz();
if (p != FINGERPRINT_OK)
return -1;
 
p = finger.fingerFastSearch();
if (p != FINGERPRINT_OK)
{
lcd.clear();
lcd.print("Finger Not Found");
lcd.setCursor(0,1);
lcd.print("Try Later");
delay(2000);
return -1;
}
// found a match!
Serial.print("stu");
Serial.print(finger.fingerID);
return finger.fingerID;
}
 
uint8_t deleteFingerprint(uint8_t MY_ID)
{
uint8_t p = -1;
lcd.clear();
lcd.print("Please wait");
p = finger.deleteModel(MY_ID);
if (p == FINGERPRINT_OK)
{
Serial.println("Deleted!");
lcd.clear();
lcd.print("Finger Deleted");
lcd.setCursor(0,1);
lcd.print("Successfully");
delay(1000);
}
 
else
{
Serial.print("Something Wrong");
lcd.clear();
lcd.print("Something Wrong");
lcd.setCursor(0,1);
lcd.print("Try Again Later");
delay(2000);
return p;
}
}
 //DOWNLOAD THE UPLOADED attendance data on serial monitor
void download(int eepIndex)
{
 
if(EEPROM.read(eepIndex) != 0xff)
{
Serial.print("T->");
if(EEPROM.read(eepIndex)<10)
Serial.print('0');
Serial.print(EEPROM.read(eepIndex++));
Serial.print(':');
if(EEPROM.read(eepIndex)<10)
Serial.print('0');
Serial.print(EEPROM.read(eepIndex++));
Serial.print(':');
if(EEPROM.read(eepIndex)<10)
Serial.print('0');
Serial.print(EEPROM.read(eepIndex++));
Serial.print(" D->");
if(EEPROM.read(eepIndex)<10)
Serial.print('0');
Serial.print(EEPROM.read(eepIndex++));
Serial.print('/');
if(EEPROM.read(eepIndex)<10)
Serial.print('0');
Serial.print(EEPROM.read(eepIndex++));
Serial.print('/');
Serial.print(EEPROM.read(eepIndex++)<<8 | EEPROM.read(eepIndex++));
}
else
{
Serial.print("---------------------------");
}
 
Serial.print(" ");
}
