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

	M5Canvas& _canvas;

	IState* _current_state = nullptr;

public:
	StateManager(Header& header, NoteState& note_state, NoteCreateState& note_create_state, M5Canvas& canvas) : _header(header), _note_state(note_state), _note_create_state(note_create_state), _canvas(canvas)
	{

	}

	void begin();

	void update();

	void on_button_a_pressed();

	void on_button_b_pressed();

	void on_button_c_pressed();

	void on_key_pressed(const uint8_t keycode);

	void to_note_state();

	void to_note_create_state(Note* reply_note = nullptr);
};