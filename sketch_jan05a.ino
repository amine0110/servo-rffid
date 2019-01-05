#include <SPI.h>
#include <MFRC522.h>


#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 
 
#define SS_PIN 10
#define RST_PIN 9




MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.


const int trigPin = 4;
const int echoPin = 3;
const int buzzer = 2;
const int Led_B = 5;
const int Led_G = 6;
const int Led_R = 7;

Servo servo;

long duration;
int distance;
int safetyDistance;
 
void setup()
{
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(buzzer, OUTPUT);
  pinMode(Led_B, OUTPUT);
  pinMode(Led_G, OUTPUT);
  pinMode(Led_R, OUTPUT);
  servo.attach(11);
  servo.write(0);

  
  Serial.begin(9600);   // Initiate a serial communication

  lcd.begin(16,2);//Defining 16 columns and 2 rows of lcd display
  lcd.backlight();//To Power ON the back light

  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  
  
 
  noTone(buzzer);
  Serial.println("Put your card to the reader...");
  Serial.println();

}
void loop() 
{
  digitalWrite(Led_G, LOW);
  digitalWrite(Led_B, HIGH);
  
  
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;

  safetyDistance = distance;
  
   
  if (safetyDistance <= 5){
      lcd.clear();
      digitalWrite(Led_B, LOW);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Enter your ID");
      lcd.setCursor(0,1);
      lcd.print("   in 5 ");
      digitalWrite(Led_R, HIGH);
      delay(700);
      lcd.clear();
      digitalWrite(Led_R, LOW);
      delay(300);

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Enter your ID");
      lcd.setCursor(0,1);
      lcd.print("   in 4 ");
      digitalWrite(Led_R, HIGH);
      delay(700);
      lcd.clear();
      digitalWrite(Led_R, LOW);
      delay(300);

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Enter your ID");
      lcd.setCursor(0,1);
      lcd.print("   in 3 ");
      digitalWrite(Led_R, HIGH);
      delay(700);
      lcd.clear();
      digitalWrite(Led_R, LOW);
      delay(300);

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Enter your ID");
      lcd.setCursor(0,1);
      lcd.print("   in 2 ");
      digitalWrite(Led_R, HIGH);
      delay(700);
      lcd.clear();
      digitalWrite(Led_R, LOW);
      delay(300);

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Enter your ID");
      lcd.setCursor(0,1);
      lcd.print("   in 1 ");
      digitalWrite(Led_R, HIGH);
      delay(700);
      lcd.clear();
      digitalWrite(Led_R, LOW);
      delay(300);
      digitalWrite(Led_B, LOW);
      tone(buzzer, 700);
      digitalWrite(Led_R, HIGH);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("We will call");
      lcd.setCursor(0,1);
      lcd.print("the Police");
    }

  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "10 68 E1 A4") //change here the UID of the card/cards that you want to give access
  {
      digitalWrite(Led_B, LOW);
      lcd.clear();
      lcd.print("Welcome Amine");
      noTone(buzzer);
      digitalWrite(Led_R, LOW);
      digitalWrite(Led_G, HIGH);
      delay(2000);
      digitalWrite(Led_G, LOW);
      servo.write(180);
      delay(1000); // you change your time here
      servo.write(0);
      
  
    Serial.println("Authorized access");
    Serial.println();
    
    
  }
 
 else   {
    Serial.println(" Access denied");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" stay away ");
    
  
    
  }
} 

