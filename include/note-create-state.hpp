#pragma once

#include <Arduino.h>

#include <M5Unified.hpp>

#include "color.hpp"
#include "i-state.hpp"
#include "misskey.hpp"
#include "footer.hpp"

class NoteCreateState : public IState
{
	Misskey& _misskey;

	Footer _footer = Footer("戻る", "英数", "送信");

	String _text;

	void show();

public:
	NoteCreateState(Misskey& misskey) : _misskey(misskey), _text(String())
	{

	}

	void begin() override;

	void update() override;

	void on_button_c_pressed() override;

	void on_key_pressed(const uint8_t keycode) override;
};