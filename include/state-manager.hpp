#pragma once

#include <Arduino.h>

#include <M5Unified.hpp>

#include "i-state.hpp"
#include "note-state.hpp"
#include "note-create-state.hpp"
#include "header.hpp"

class StateManager
{
	Header& _header;
	NoteState& _note_state;
	NoteCreateState& _note_create_state;

	IState* _current_state = nullptr;

public:
	StateManager(Header& header, NoteState& note_state, NoteCreateState& note_create_state) : _header(header), _note_state(note_state), _note_create_state(note_create_state)
	{

	}

	void begin();

	void update();

	void on_button_a_pressed();

	void on_button_b_pressed();

	void on_button_c_pressed();

	void on_key_pressed(const uint8_t keycode);
};