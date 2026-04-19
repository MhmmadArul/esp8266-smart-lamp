#include <ESP8266WiFi.h>
#include <SinricPro.h>
#include <SinricProSwitch.h>

#define WIFI_SSID         "SSID_WIFI"
#define WIFI_PASS         "PASS_WIFI"

#define APP_KEY           "APP_KEY FROM SINRIC PRO"
#define APP_SECRET        "APP_SECRET FROM SINRIC PRO"
#define DEVICE_ID         "DEVICE_ID FROM SINRIC PRO"

#define RELAY_PIN D1

bool onPowerState(const String &deviceId, bool &state) {
  Serial.printf("Device %s turned %s\r\n", deviceId.c_str(), state ? "ON" : "OFF");

  digitalWrite(RELAY_PIN, state ? LOW : HIGH); // relay aktif LOW
  return true;
}

void setupWiFi() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
}

void setupSinricPro() {
  SinricProSwitch &mySwitch = SinricPro[DEVICE_ID];

  mySwitch.onPowerState(onPowerState);

  SinricPro.begin(APP_KEY, APP_SECRET);
}

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // default mati

  setupWiFi();
  setupSinricPro();
}

void loop() {
  SinricPro.handle();
}
