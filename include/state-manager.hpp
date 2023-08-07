#pragma once

#include <Arduino.h>

#include <M5Unified.hpp>

#include "i-state.hpp"
#include "note-state.hpp"
#include "header.hpp"

class StateManager
{
	NoteState& _note_state;

	Header _header = Header();

	IState* _current_state = nullptr;

public:
	StateManager(NoteState& note_state) : _note_state(note_state)
	{

	}

	void begin();

	void update();

	void on_button_a_pressed();

	void on_button_b_pressed();

	void on_button_c_pressed();

	void on_key_pressed(const uint8_t keycode);
};