#include <ESP8266WiFi.h>
#include<ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>

#define ssid "shivam"
#define password "shivam123"
#define server_ssid "ESP8266 WiFi"
#define server_password ""

ESP8266WebServer server(80);

int sdata = 3;
#define totalStudent 5
String logBuffer = "", attendanceBuffer = "";
String student[totalStudent] = {"Shivam", "Harshit", "Rahul", "Manjul", "Harsh"};
boolean studentStatus[totalStudent] = {false, false, false, false, false};
boolean studentAttendance[totalStudent] = {false, false, false, false, false};
byte attendanceCounter[totalStudent] = {0, 0, 0, 0, 0};
void connect_WiFi()
{
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  int count = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
    count++;
    if (count > 60)
      break;
  }
  Serial.println("\nWiFi Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void create_hotspot()
{
  WiFi.softAP(server_ssid, server_password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("\nLocal Server IP address: ");
  Serial.println(myIP);
  Serial.println("HTTP server started");
}

void attendance() {
  attendanceBuffer = "Absent: \n";
  for (int i = 0; i < totalStudent; i++) {
    if (studentAttendance[i] == false) {
      attendanceBuffer += student[i];
      attendanceBuffer += "\n";
    }
  }
  attendanceBuffer += "\nPresent: \n";
  for (int i = 0; i < totalStudent; i++) {
    if (studentAttendance[i]) {
      attendanceBuffer += student[i];
      attendanceBuffer += "\n";
    }
  }
}

void setup()
{
  Serial.begin(115200);
  connect_WiFi();
  create_hotspot();
  digitalWrite(LED_BUILTIN, HIGH);
  server.on("/", []() {
    server.send(200, "text/plain", logBuffer);
  });
  server.on("/attendance", []() {
    server.send(200, "text/plain", attendanceBuffer);
  });
  server.begin();
  attendance();
}

void loop()
{
  if (Serial.available()) {
    int sdata = Serial.read();
    logBuffer += sdata;
    logBuffer += " \t";
    if (sdata >= 0 && sdata <= 1) {

      attendanceCounter[sdata]++;
      if (attendanceCounter[sdata] == 2) {
        attendanceCounter[sdata] = 0;
        studentAttendance[sdata] = !studentAttendance[sdata];
      }

      logBuffer += student[sdata];
      if (studentStatus[sdata]) {
        logBuffer += " has Reached\n";
        attendanceCounter[sdata]++;
      }
      else {
        logBuffer += " has boarded the bus\n";
      }
      studentStatus[sdata] = !studentStatus[sdata];
    }
    attendance();
  }
  server.handleClient();
}
