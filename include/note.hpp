#pragma once

#include <Arduino.h>

#include <M5Unified.hpp>
#include <ArduinoJson.h>

#include "color.hpp"

class Note
{
	JsonVariant _json;

public:
	Note(JsonVariant& json) : _json(json)
	{

	}

	void show(M5Canvas& canvas);

	const char* get_id();
};