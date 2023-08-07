#include "note-state.hpp"

void NoteState::show_current_note()
{
	M5.Lcd.clear();
	M5.Lcd.setCursor(0, 0);

	if (_current_note != nullptr)
	{
		_current_note->show();
	}
}

void NoteState::begin()
{
	on_button_b_pressed();
}

void NoteState::update()
{

}

void NoteState::on_button_a_pressed()
{
	Note* const next_note = _misskey.get_after_note(_current_note);
	delete _current_note;
	_current_note = next_note;

	show_current_note();
}

void NoteState::on_button_b_pressed()
{
	delete _current_note;
	_current_note = _misskey.get_home_timeline();

	show_current_note();
}

void NoteState::on_button_c_pressed()
{
	Note* const next_note = _misskey.get_before_note(_current_note);
	delete _current_note;
	_current_note = next_note;

	show_current_note();
}