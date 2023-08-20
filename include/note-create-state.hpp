#pragma once

#include <functional>

#include <Arduino.h>
#include <SD.h>

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

	Footer _footer = Footer("戻る", "英数", "投稿");

	String _text;
	String _text_japanese;
	String _text_japanese_temp;

	bool _is_japanese = false;
	bool _is_translate = false;

	NoteVisibility _visibility = NoteVisibility::Public;
	bool _local_only = true;

	Note* _reply_note = nullptr;

	void show();

	void add_kana(const char c);

	void kana_from_temp(const char* temp, const char* kana);

	void remove_utf8(String& text);

public:
	std::function<void()> to_note_state = nullptr;

	NoteCreateState(Misskey& misskey, InputMethod& input_method, M5Canvas& canvas) : _misskey(misskey), _input_method(input_method), _canvas(canvas), _text(String()), _text_japanese(String()), _text_japanese_temp(String())
	{

	}

	void begin() override;

	void update() override;
	
	void on_button_a_pressed() override;

	void on_button_b_pressed() override;

	void on_button_c_pressed() override;

	void on_key_pressed(const uint8_t keycode) override;

	void set_reply_note(Note* note);
};