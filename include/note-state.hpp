#pragma once

#include <memory>
#include <functional>

#include <Arduino.h>

#include <M5Unified.hpp>

#include "i-state.hpp"
#include "note.hpp"
#include "misskey.hpp"
#include "https.hpp"
#include "footer.hpp"

class NoteState : public IState
{
	Misskey& _misskey;
	HTTPS& _https;
	M5Canvas& _canvas;

	Footer _footer = Footer("ノート", "最新", "");

	Note* _current_note = nullptr;

	void show_current_note();

public:
	std::function<void(Note*)> to_note_create_state = nullptr;

	NoteState(Misskey& misskey, HTTPS& https, M5Canvas& canvas) : _misskey(misskey), _https(https), _canvas(canvas)
	{

	}

	void begin() override;

	void update() override;

	void on_button_a_pressed() override;

	void on_button_b_pressed() override;

	void on_button_c_pressed() override;

	void on_key_pressed(const uint8_t keycode) override;
};