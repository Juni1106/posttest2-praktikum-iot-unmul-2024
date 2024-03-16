#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Define pins
const int BUZZER_PIN = D2;
const int LED_PIN = D1;
const int BUTTON_PIN_PLUS = D7;
const int BUTTON_PIN = D6;
const int BUTTON_PIN_MIN = D5;

// Define variables
int buttonState = 0;
int buttonPlus = 0;
int buttonMin = 0;

int light = 0;
int buzzer = 100;
String mode = "lampu";

const char* ssid = "AL";
const char* password = "112345678";

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());

  server.on("/", handle);
  server.begin();

  // Initialize pins
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUTTON_PIN_PLUS, INPUT_PULLUP);
  pinMode(BUTTON_PIN_MIN, INPUT_PULLUP);
}

void loop() {
  mainProgram();
  server.handleClient();
}

void handle() {
  String strLed = String(light);
  String strBuzzer = String(buzzer);
  String response = "<html><body><h1><center>Posttest 2 IoT</center></h1><h2>LED State: " + strLed + "</h2><br><h2>Buzzer State: " + strBuzzer + "</h2></body></html>";
  server.send(200, "text/html", response);
}

void mainProgram(){
  // Check button state
  buttonState = digitalRead(BUTTON_PIN);
  buttonPlus = digitalRead(BUTTON_PIN_PLUS);
  buttonMin = digitalRead(BUTTON_PIN_MIN);

  // If button is pressed, turn on LED and buzzer
  if (buttonState == LOW) {
    if (mode == "lampu") {
      mode = "buzzer";
      delay(200);
    } else {
      mode = "lampu";
      delay(200);
    }
  }
  if (buttonPlus == LOW) {
    if (mode == "lampu") {
      if (light > 246) {
        light = 249;
        analogWrite(LED_PIN, light);
        delay(200);
      } else {
        light += 3;
        analogWrite(LED_PIN, light);
        delay(200);
      }
    } else {
      if (buzzer > 2490) {
        buzzer = 2500;
        tone(BUZZER_PIN, buzzer);
        delay(200);
      } else {
        buzzer += 10;
        tone(BUZZER_PIN, buzzer);
        delay(200);
      }
    }
  }
  if (buttonMin == LOW) {
    if (mode == "lampu") {
      if (light > 3) {
        light -= 3;
        analogWrite(LED_PIN, light);
        delay(200);
      } else {
        light = 0;
        analogWrite(LED_PIN, light);
        delay(200);
      }
    } else {
      if (buzzer > 110) {
        buzzer -= 10;
        tone(BUZZER_PIN, buzzer);
        delay(200);
      } else {
        buzzer = 100;
        tone(BUZZER_PIN, buzzer);
        delay(200);
      }
    }
  }
}