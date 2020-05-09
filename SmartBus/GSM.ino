void sendMessage(String msg)
{
  gsmSerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  gsmSerial.println("AT+CMGS=\"+918700311344\"\r"); // Replace x with mobile number
  delay(1000);
  gsmSerial.println(msg);// The SMS text you want to send
  delay(1000);
  gsmSerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

void RecieveMessage()
{
  gsmSerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(1000);
}

