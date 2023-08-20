#pragma once

#include <time.h>

#include <Arduino.h>
#include <SD.h>

#include <M5Unified.hpp>
#include <ArduinoJson.h>

#include "color.hpp"
#include "https.hpp"

class Note
{
	JsonVariant _json;

	int32_t _y = 24;

	void show_name(M5Canvas& canvas, String& name, String& user_name, const uint32_t color);
	void show_text(M5Canvas& canvas, String& text);
	void show_date_time(M5Canvas& canvas, String& date_time);
	void show_visibility(M5Canvas& canvas, String& visibility);

public:
	Note(JsonVariant& json) : _json(json)
	{

	}

	void show(HTTPS& https, M5Canvas& canvas);

	void scroll_up(HTTPS& https, M5Canvas& canvas);

	void scroll_down(HTTPS& https, M5Canvas& canvas);

	const char* get_id();

	const char* get_username();
};