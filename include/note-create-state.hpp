#pragma once

#include <Arduino.h>

#include <M5Unified.hpp>

#include "color.hpp"
#include "i-state.hpp"
#include "misskey.hpp"
#include "input-method.hpp"
#include "footer.hpp"

class NoteCreateState : public IState
{
	Misskey& _misskey;
	InputMethod& _input_method;
	M5Canvas& _canvas;

	Footer _footer = Footer("戻る", "英数", "送信");

	String _text;
	String _text_japanese;
	String _text_japanese_temp;

	bool _is_japanese = false;
	bool _is_translate = false;

	void show();

	void add_kana(const char c);

	void kana_from_temp(const char* temp, const char* kana);

	void remove_utf8(String& text);

public:
	NoteCreateState(Misskey& misskey, InputMethod& input_method, M5Canvas& canvas) : _misskey(misskey), _input_method(input_method), _canvas(canvas), _text(String()), _text_japanese(String()), _text_japanese_temp(String())
	{

	}

	void begin() override;

	void update() override;
	
	void on_button_b_pressed() override;

	void on_button_c_pressed() override;

	void on_key_pressed(const uint8_t keycode) override;
};