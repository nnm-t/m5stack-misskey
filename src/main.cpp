#include <Arduino.h>
#include <SD.h>
#include <WiFi.h>
#include <HTTPClient.h>

#include <M5Unified.h>
#include <ArduinoJson.h>

#include "settings.hpp"
#include "https.hpp"
#include "note.hpp"
#include "misskey.hpp"

namespace {

    Settings settings;
    HTTPS https(settings);
    Misskey misskey(settings, https);

    Note* current_note = nullptr;
}

void setup()
{
    auto config = M5.config();
    M5.begin(config);

    settings.begin();

    M5.Lcd.setFont(&fonts::lgfxJapanGothic_16);
    M5.Lcd.println("Misskey on M5Stack");

    // JSONからSSID, PASS読み込んでWi-Fi接続
    WiFi.begin(settings.get_ssid(), settings.get_password());

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

    M5.Lcd.clear();
    M5.Lcd.setCursor(0, 0);
}

void loop()
{
    M5.update();

    if (M5.BtnA.wasPressed())
    {
        Note* next_note = misskey.get_after_note(current_note);
        delete current_note;
        current_note = next_note;

        M5.Lcd.clear();
        M5.Lcd.setCursor(0, 0);
        if (current_note != nullptr)
        {
            current_note->show();
        }
    }

    if (M5.BtnB.wasPressed())
    {
        delete current_note;
        current_note = misskey.get_home_timeline();

        M5.Lcd.clear();
        M5.Lcd.setCursor(0, 0);
        if (current_note != nullptr)
        {
            current_note->show();
        }
    }

    if (M5.BtnC.wasPressed())
    {
        Note* next_note = misskey.get_before_note(current_note);
        delete current_note;
        current_note = next_note;

        M5.Lcd.clear();
        M5.Lcd.setCursor(0, 0);
        if (current_note != nullptr)
        {
            current_note->show();
        }
    }

    delay(50);
}