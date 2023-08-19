#pragma once

#include <Arduino.h>
#include <SD.h>

#include <M5Unified.hpp>

#include "color.hpp"
#include "settings.hpp"

class Header
{
	Settings& _settings;
	M5Canvas& _canvas;

public:
	Header(Settings& settings, M5Canvas& canvas) : _settings(settings), _canvas(canvas)
	{

	}

	void begin();

	void update();

	void print(const char* text);

	void print(String& text);
};