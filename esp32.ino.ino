#include <WiFi.h>
#include <LiquidCrystal.h>

const char* ssid = "ENTER YOUR WIFI SSID";
const char* password = "ENTER YOUR WIFI PASSWORD";
WiFiServer server(9050);
LiquidCrystal lcd(22,21,5,18,23,19);

void setup() {
  lcd.begin(8, 2); 
  lcd.clear();
  lcd.print("Connecting...");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    lcd.clear();
    lcd.print("ConnectingWiFi");
  }

  server.begin();

  lcd.clear();
  lcd.print("WiFi connected!");
  lcd.setCursor(0, 1);
  lcd.print("IP:");
  lcd.print(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    while (client.connected()) {
      if (client.available()) {
        String request = client.readStringUntil('\r');
        lcd.setCursor(0, 0);
        lcd.clear();
        lcd.print("Reads: ");
        lcd.print(request);
      } else {
        lcd.print("NoClientReq");  
      }
    }
  }
}
