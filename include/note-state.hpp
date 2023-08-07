#pragma once

#include <memory>

#include <Arduino.h>

#include <M5Unified.h>

#include "i-state.hpp"
#include "note.hpp"
#include "misskey.hpp"

class NoteState : public IState
{
	Misskey& _misskey;
	Note* _current_note = nullptr;

	void show_current_note();

public:
	NoteState(Misskey& misskey) : _misskey(misskey)
	{

	}

	void begin() override;

	void update() override;

	void on_button_a_pressed() override;

	void on_button_b_pressed() override;

	void on_button_c_pressed() override;
};