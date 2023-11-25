#pragma once

#include <Arduino.h>
#include <SD.h>

#include <M5Unified.h>
#include <ArduinoJson.h>

class Settings
{
    StaticJsonDocument<1024> _json_settings;
    String _root_ca;

	const char* get_root_ca_name();

public:
	Settings() : _json_settings(StaticJsonDocument<1024>()), _root_ca(String())
	{

	}

	void begin(const uint8_t sd_pin = 12);

	const char* get_ssid();

	const char* get_password();

	const char* get_api_token();

	const char* get_host();

	String& get_root_ca();

	const char* get_title();

	const char* get_icon();
};