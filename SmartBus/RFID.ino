void rfida()
{
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  delay(2000);
  {
    String msg = "Your ward ";
    //Show UID on serial monitor
    //    Serial.print("UID tag :");
    String content = "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
      //      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      //      Serial.print(mfrc522.uid.uidByte[i], HEX);
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    //    Serial.println();
    //    Serial.print("Message : ");
    content.toUpperCase();
    int i;
    for (i = 0; i < 2; i++) {
      if (content.substring(1) == rfid[i]) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(student[i]);
        msg += student[i];
        msg += " has";
        if (studentStatus[i]) {
          lcd.print(" Reached");
          msg += " Reached";
        }
        else {
          lcd.print(" Boarded");
          msg += " Boarded";
        }
        sendMessage(msg);
        studentStatus[i] = !studentStatus[i];
        delay(3000);
        Serial.write(i);
        break;
      }
    }
    if (i == 2) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("No Match Found!!");
      lcd.setCursor(0, 1);
      lcd.print("Try Again");
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Place RFID Card..");
  }
}
