/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  ESP32, Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build mobile and web interfaces for any
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: https://www.blynk.io
    Sketch generator:           https://examples.blynk.cc
    Blynk community:            https://community.blynk.cc
    Follow us:                  https://www.fb.com/blynkapp
                                https://twitter.com/blynk_app

  Blynk library is licensed under MIT license
 *************************************************************
  Blynk.Edgent implements:
  - Blynk.Inject - Dynamic WiFi credentials provisioning
  - Blynk.Air    - Over The Air firmware updates
  - Device state indication using a physical LED
  - Credentials reset using a physical Button
 *************************************************************/

/* Fill in information from your Blynk Template here */
/* Read more: https://bit.ly/BlynkInject */
#define BLYNK_TEMPLATE_ID "TMPL6a4Ginuzb"
#define BLYNK_TEMPLATE_NAME "Sensors"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "BlynkEdgent.h"
#define BLYNK_FIRMWARE_VERSION "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI




#define BLYNK_PRINT Serial

const int trig = D2;  // chân trig của HC-SR04
const int echo = D1;  // chân echo của HC-SR04
const int led = D3;
const int buz = D4;

unsigned long times = millis();
WidgetLED LEDCONNECT(V0);
WidgetLED LED1(V1);
WidgetLED LED2(V2);

void setup() {
  Serial.begin(115200);
  delay(100);
  pinMode(trig, OUTPUT);  // chân trig sẽ phát tín hiệu
  pinMode(led, OUTPUT);
  pinMode(buz, OUTPUT);
  pinMode(echo, INPUT);
  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();

  if (millis() - times > 1000) {
    Blynk.virtualWrite(V5, millis() / 1000);
    if (LEDCONNECT.getValue()) {
      LEDCONNECT.off();
    } else {
      LEDCONNECT.on();
    }
    times = millis();
  }

  unsigned long duration;  // biến đo thời gian
  int distance;            // biến lưu khoảng cách

  /* Phát xung từ chân trig */
  digitalWrite(trig, 0);  // tắt chân trig
  delayMicroseconds(2);
  digitalWrite(trig, 1);  // phát xung từ chân trig
  delayMicroseconds(5);   // xung có độ dài 5 microSeconds
  digitalWrite(trig, 0);  // tắt chân trig

  /* Tính toán thời gian */
  // Đo độ rộng xung HIGH ở chân echo.
  duration = pulseIn(echo, HIGH);
  // Tính khoảng cách đến vật.
  distance = int(duration / 2 / 29.412);
  if (distance <= 20) {
    digitalWrite(led, HIGH);  // bật đèn led sáng
    delay(500);               // dừng chương trình trong 1 giây => thây đèn sáng được 1 giây
    digitalWrite(led, LOW);   // tắt đèn led
    delay(500);
    Serial.print("On");

    digitalWrite(buz, HIGH);  // bật đèn led sáng
    delay(500);               // dừng chương trình trong 1 giây => thây đèn sáng được 1 giây
    digitalWrite(buz, LOW);   // tắt đèn led
    delay(500);
    Serial.print("On Buz");
  }
  /* In kết quả ra Serial Monitor */
  Serial.print(distance);
  Serial.println("cm");
  delay(200);
}
