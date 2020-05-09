void Gps()
{
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH)
  {
    // turn LED on:
    delay(500);
    digitalWrite(ledPin, HIGH);

    while (gpsSerial.available())
    { // check for gps data
      if (gps.encode(gpsSerial.read()))
      { // encode gps data
        gps.get_position(&lat, &lon); // get latitude and longitude
        // display position
        Serial.print("Position: ");
        Serial.print("lat: "); Serial.print(lat); Serial.print(" "); // print latitude
        Serial.print("lon: "); Serial.println(lon); // print longitude

        sendMessage("ËMERGENCY");
        lcd.setCursor(0, 0);
        lcd.print("ËMERGENCY");
        lcd.setCursor(0, 1);
        lcd.print("lat");
        lcd.setCursor(1, 1);
        lcd.print("lon");
      }
    }
  }
  else
  {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
}
