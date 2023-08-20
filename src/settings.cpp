#include "settings.hpp"

void Settings::begin(const uint8_t sd_pin)
{
    SD.begin(sd_pin);

    // 設定ファイル開く
    File settings_file = SD.open("/misskey_settings.json");
    if (!settings_file) {
      M5.Lcd.println("Settings file open failed.");
      return;
    }

    // JSONデシリアライズ
    DeserializationError error = deserializeJson(_json_settings, settings_file);
    if (error != DeserializationError::Ok)
    {
        M5.Lcd.println("JSON deserialize failed.");
        return;
    }

    // ファイルからルート証明書読み込み
    const char* root_ca_name = get_root_ca_name();
    File root_ca_file = SD.open(root_ca_name);
    if (!root_ca_file)
    {
        M5.Lcd.println("Root CA file open failed.");
        return;
    }

    // String メモリ確保
    _root_ca.reserve(root_ca_file.available());

    while (root_ca_file.available())
    {
        _root_ca += static_cast<char>(root_ca_file.read());
    }
}

const char* Settings::get_ssid()
{
	return _json_settings["ssid"].as<const char*>();
}

const char* Settings::get_password()
{
	return _json_settings["password"].as<const char*>();
}

const char* Settings::get_root_ca_name()
{
	return _json_settings["root_ca"].as<const char*>();
}

const char* Settings::get_host()
{
	return _json_settings["host"].as<const char*>();
}

const char* Settings::get_api_token()
{
	return _json_settings["api_token"].as<const char*>();
}

const char* Settings::get_title()
{
	return _json_settings["title"].as<const char*>();
}

const char* Settings::get_icon()
{
	return _json_settings["icon"].as<const char*>();
}

String& Settings::get_root_ca()
{
	return _root_ca;
}