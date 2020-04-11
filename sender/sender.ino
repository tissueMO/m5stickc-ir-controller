#include <M5StickC.h>
#include <IRsend.h>
#include <IRremoteESP8266.h>
#include <WiFi.h>
#include <WiFiServer.h>
#include "remote.h"

// 定数定義
#include "settings.h"
// #define SSID {SSID}
// #define PASSWORD {PASSWORD}
const char* ssid = SSID;
const char* password = PASSWORD;
const int port = 80;
const char* requestPattern = "GET /send?button=";

// 関数プロトタイプ宣言
void sendIR(String &button);

// IR トランスミッター
// M5StickC は GPIO 9 に IRトランスミッター が内蔵されている
const uint16_t kIrLed = 9;
IRsend irsend(kIrLed);

// Wi-Fi モジュール
WiFiServer server(port);


/*
  初回処理
*/
void setup() {
  // M5StickC 初期化
  M5.begin();

  // LCD スクリーン初期化
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(1);
  M5.Lcd.println("TV Remote Controller");

  // IR モジュール初期化
  irsend.begin();

  // Wi-Fi 接続
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    // 接続待ち
    delay(500);
    Serial.print(".");
  }

  // 接続成功後
  Serial.println();
  Serial.println("Wi-Fi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  M5.Lcd.print("IP address: ");
  M5.Lcd.println(WiFi.localIP());

  // HTTPサーバー起動
  server.begin();
}

/*
  ループ処理
*/
void loop() {
  // クライアントからの接続を Listen する
  WiFiClient client = server.available();
  if (!client) {
    // クライアントからの接続無し
    return;
  }

  String httpHeader = "";
  String currentLine = "";
  Serial.println();
  Serial.println("New client.");

  while (client.connected()) {
    if (!client.available()) {
      continue;
    }

    // クライアントからのリクエスト文字列を受け取る
    char c = client.read();
    Serial.write(c);
    httpHeader += c;
    if (c == '\r') {
      // 読み取らない文字
      continue;
    } else if (c != '\n') {
      // 引き続き送られてきた文字を読み進める
      currentLine += c;
      continue;
    } else if (currentLine.length() > 0) {
      // 改行コードを目印に、次の行に続く
      currentLine = "";
      continue;
    }

    // 空行が現れたら終端とみなす
    // レスポンスを返す
    client.println("HTTP/1.1 200 OK");
    client.println("Connection: close");
    client.println();

    // パラメーターの解析を行い、IR送信を実行
    if (httpHeader.indexOf(requestPattern) != -1) {
      int beginpos = httpHeader.indexOf("=") + 1;
      int endpos = httpHeader.substring(beginpos).indexOf(" ");
      String buttonName = httpHeader.substring(beginpos, beginpos + endpos);
      sendIR(buttonName);
    } else {
      char* message = "parameter is not found.";
      client.println(message);
      Serial.println(message);
      break;
    }

    // 一定時間経過後に画面クリア
    delay(1000);
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.println("TV Remote Controller");
    M5.Lcd.print("IP address: ");
    M5.Lcd.println(WiFi.localIP());

    break;
  }
}


/*
  赤外線を送信
*/
void sendIR(String &button) {
  Serial.print("Button Name '");
  Serial.print(button);
  Serial.print("'");
  M5.Lcd.print("[");
  M5.Lcd.print(button);
  M5.Lcd.print("] ");

  // ボタン名と合致するコードを探す
  uint64_t command = 0x0;
  for (int i = 0; i < codeLength; i++) {
    if (remote[i].name == button) {
      command = remote[i].command;
      break;
    }
  }
  if (command == 0x0) {
    // 合致するコードが見つからなかった
    Serial.println(" is not found.");
    M5.Lcd.println(" is not found.");
    return;
  }

  // 見つかったコードを送信
  irsend.sendNEC(command);
  Serial.printf("Send IR: 0x%08LX", command);
  M5.Lcd.println();
  M5.Lcd.printf("Send IR: 0x%08LX", command);
  M5.Lcd.println();
}
