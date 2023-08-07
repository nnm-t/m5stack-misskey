#pragma once

#include <functional>

#include <Arduino.h>
#include <Wire.h>

#include <M5Unified.hpp>

class FacesKeyboard
{
	static constexpr const uint8_t i2c_address = 0x08;

	TwoWire* _wire = nullptr;
	uint8_t _interrupt_pin = 0;

public:
	std::function<void(const uint8_t)> on_key_pressed = nullptr;

	void begin();

	void update();
};