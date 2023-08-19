#pragma once

#include <Arduino.h>

#include <M5Unified.hpp>

#include "color.hpp"

class Header
{
	M5Canvas& _canvas;

public:
	Header(M5Canvas& canvas) : _canvas(canvas)
	{

	}

	void begin();

	void update();

	void print(const char* text);

	void print(String& text);
};