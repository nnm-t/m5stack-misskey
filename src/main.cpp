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
#include "faces-keyboard.hpp"
#include "note-state.hpp"
#include "note-create-state.hpp"
#include "state-manager.hpp"

namespace {
    Settings settings;
    HTTPS https(settings);
    Misskey misskey(settings, https);

    FacesKeyboard keyboard;

    NoteState note_state(misskey);
    NoteCreateState note_create_state(misskey);
    StateManager state_manager(note_state, note_create_state);
}

void setup()
{
    auto config = M5.config();
    M5.begin(config);

    settings.begin();

    keyboard.on_key_pressed = [&](const uint8_t keycode){ state_manager.on_key_pressed(keycode); };
    keyboard.begin();

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

    state_manager.begin();
}

void loop()
{
    M5.update();

    if (M5.BtnA.wasPressed())
    {
        state_manager.on_button_a_pressed();
    }

    if (M5.BtnB.wasPressed())
    {
        state_manager.on_button_b_pressed();
    }

    if (M5.BtnC.wasPressed())
    {
        state_manager.on_button_c_pressed();
    }

    keyboard.update();
    state_manager.update();

    delay(50);
}