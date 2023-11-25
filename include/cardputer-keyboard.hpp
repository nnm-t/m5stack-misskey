#pragma once

#include <functional>

#include <Arduino.h>
#include <Wire.h>

#include <M5Unified.hpp>

class CardputerKeyboard
{
	static constexpr const uint8_t a0_pin = 8;
	static constexpr const uint8_t a1_pin = 9;
	static constexpr const uint8_t a2_pin = 11;

	static constexpr const uint8_t c0_pin = 13;
	static constexpr const uint8_t c1_pin = 15;
	static constexpr const uint8_t c2_pin = 3;
	static constexpr const uint8_t c3_pin = 4;
	static constexpr const uint8_t c4_pin = 5;
	static constexpr const uint8_t c5_pin = 6;
	static constexpr const uint8_t c6_pin = 7;

	bool _is_key_pressing = false;
	bool _is_key_release = true;
	bool _is_caps_press = false;
	bool _is_func_press = false;
	bool _is_ctrl_press = false;
	bool _is_opt_press = false;
	bool _is_alt_press = false;

	void output_row(const uint8_t row);

	void send_keycode(const uint8_t single, const uint8_t caps, const uint8_t func = 0xFF, const uint8_t ctrl = 0xFF, const uint8_t opt = 0xFF, const uint8_t alt = 0xFF);

	void scan_modifier_key();

	void scan_r0();
	void scan_r1();
	void scan_r2();
	void scan_r3();
	void scan_r4();
	void scan_r5();
	void scan_r6();
	void scan_r7();

public:
	std::function<void(const uint8_t)> on_key_pressed = nullptr;

	void begin();

	void update();
};