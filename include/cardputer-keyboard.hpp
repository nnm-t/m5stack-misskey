#pragma once

#include <functional>

#include <Arduino.h>
#include <Wire.h>

#include <M5Unified.hpp>

class CardputerKeyboard
{

public:
	std::function<void(const uint8_t)> on_key_pressed = nullptr;

	void begin();

	void update();
};