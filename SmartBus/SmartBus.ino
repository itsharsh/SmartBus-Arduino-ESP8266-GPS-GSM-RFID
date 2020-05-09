#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>

int baudRate = 115200;

SoftwareSerial gsmSerial(6, 7);
SoftwareSerial gpsSerial(4, 5); //tx,rx
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int buttonPin = 7;     // the number of the panic button pin
const int ledPin = 3;
boolean buttonState = false;
long lat, lon;

String rfid[2] = {"41 34 EB 09", "07 07 04 26"};
String student[2] = {"Shivam", "Harshit"};
boolean studentStatus[2] = {false, false};

int count = 0;
TinyGPS gps;
int sdata = 0;

void panic() {
  sendMessage("Emergency!! Location: https://www.google.co.in/maps/@28.6293377,77.3714301");
  for (int i = 0; i < 5; i++) {
    lcd.clear();
    delay(200);
    lcd.setCursor(0, 0);
    lcd.print("EMERGENCY");
    delay(500);
  }
}

void setup()
{
  pinMode(8, INPUT);
  lcd.init();
  lcd.backlight();
  gsmSerial.begin(115200);
  gpsSerial.begin(115200);
  Serial.begin(115200);
  lcd.print("Initializing...");
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.println("Done");
  delay(2000);

}

void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Place RFID Card..");
  delay(1000);
  rfida();
  //  Gps();
  if (digitalRead(8))
    panic();
}

