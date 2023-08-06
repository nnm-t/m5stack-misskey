#include <Arduino.h>
#include <SD.h>
#include <WiFi.h>
#include <HTTPClient.h>

#include <M5Unified.h>
#include <ArduinoJson.h>

namespace {
    constexpr const char* misskey_host = "https://misskey.io";
    constexpr const char* misskey_api = "/api";
    constexpr const char* misskey_api_notes_timeline = "/notes/timeline";

    StaticJsonDocument<1024> json_settings;
    StaticJsonDocument<4096> json_request;
    StaticJsonDocument<16384> json_response;

    String content_type_json("application/json");
    String target_page_notes_timeline = String(misskey_api) + misskey_api_notes_timeline;

    String root_ca;
}

String post_https(String& host, String& content_type, String& content);

void get_timeline();

void setup()
{
    auto config = M5.config();
    M5.begin(config);
    SD.begin(4);

    M5.Lcd.setFont(&fonts::lgfxJapanGothic_16);
    M5.Lcd.println("Misskey on M5Stack");

    // 設定ファイル開く
    File settings_file = SD.open("/misskey_settings.json");
    if (!settings_file) {
      M5.Lcd.println("Settings file open failed.");
      return;
    }

    // JSONデシリアライズ
    DeserializationError error = deserializeJson(json_settings, settings_file);
    if (error != DeserializationError::Ok)
    {
        M5.Lcd.println("JSON deserialize failed.");
        return;
    }

    // JSONからSSID, PASS読み込んでWi-Fi接続
    const char* ssid = json_settings["ssid"];
    const char* password = json_settings["password"];

    WiFi.begin(ssid, password);

    M5.Lcd.print("Wi-Fi connecting");
    while (WiFi.status() != WL_CONNECTED)
    {
        M5.Lcd.print(".");
        delay(500);
    }

    M5.Lcd.println("Success");
    M5.Lcd.print("IP: ");
    M5.Lcd.print(WiFi.localIP().toString());

    delay(2000);

    // ファイルからルート証明書読み込み
    const char* root_ca_name = json_settings["root_ca"];
    File root_ca_file = SD.open(root_ca_name);
    if (!root_ca_file)
    {
        M5.Lcd.println("Root CA file open failed.");
        return;
    }

    // String メモリ確保
    root_ca.reserve(root_ca_file.available());

    while (root_ca_file.available())
    {
        root_ca += static_cast<char>(root_ca_file.read());
    }

    M5.Lcd.clear();
    M5.Lcd.setCursor(0, 0);
}

void get_timeline()
{
    json_request.clear();

    json_request["i"] = json_settings["api_token"];
    json_request["limit"] = 3;

    String request;
    serializeJson(json_request, request);

    M5.Lcd.clear();
    M5.Lcd.setCursor(0, 0);

    String url = misskey_host + String(misskey_api) + "/notes/timeline";
    String response = post_https(url, content_type_json, request);

    Serial.println(response);

    DeserializationError error = deserializeJson(json_response, response);

    if (error != DeserializationError::Ok)
    {
        M5.Lcd.println("Response deserialize failed.");
        return;
    }
    
    for (uint8_t i = 0; i < 3; i++)
    {
        JsonVariant json_note = json_response[i];

        if (json_note.containsKey("renote"))
        {
            // Renote
            JsonVariant json_renote = json_note["renote"];

            JsonVariant json_user = json_renote["user"];
            String name = json_user["name"];
            String user_name = json_user["username"];

            String text = json_renote["text"];
            String date_time = json_renote["createdAt"];

            M5.Lcd.setTextColor(0x2463EDU, 0x000000U);
            M5.Lcd.print(name);
            M5.Lcd.print(" @");
            M5.Lcd.println(user_name);

            M5.Lcd.setTextColor(0xFFFFFFU, 0x000000U);
            M5.Lcd.println(text);
            
            M5.Lcd.setTextColor(0xCCCCCCU, 0x000000U);
            M5.Lcd.println(date_time);
            M5.Lcd.print("\n");
        }
        else
        {
            JsonVariant json_user = json_note["user"];
            String name = json_user["name"];
            String user_name = json_user["username"];

            String text = json_note["text"];
            String date_time = json_note["createdAt"];

            M5.Lcd.setTextColor(0x96CC30U, 0x000000U);
            M5.Lcd.print(name);
            M5.Lcd.print(" @");
            M5.Lcd.println(user_name);

            M5.Lcd.setTextColor(0xFFFFFFU, 0x000000U);
            M5.Lcd.println(text);
            
            M5.Lcd.setTextColor(0xCCCCCCU, 0x000000U);
            M5.Lcd.println(date_time);
            M5.Lcd.print("\n");
        }
    }
}

String post_https(String& url, String& content_type, String& content)
{
    HTTPClient http_client;
    String response;

    // 証明書セットして送信
    if (!http_client.begin(url, root_ca.c_str()))
    {
        M5.Lcd.println("HTTPS Connection failed");
        return response;
    }

    // POST組み立てる
    http_client.addHeader("Content-Type", content_type);
    int32_t status_code = http_client.POST(content);

    switch (status_code)
    {
        case 200:
            response = http_client.getString();
            break;
        default:
            M5.Lcd.println(http_client.errorToString(status_code));
            break;
    }

    http_client.end();
    return response;
}

void loop()
{
    M5.update();

    if (M5.BtnB.wasPressed())
    {
      get_timeline();
      delay(500);
    }

    delay(50);
}