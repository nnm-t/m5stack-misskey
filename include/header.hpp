#pragma once

#include <Arduino.h>

#include <M5Unified.hpp>

#include "color.hpp"

class Header
{
public:
	Header()
	{

	}

	void begin();

	void update();
};