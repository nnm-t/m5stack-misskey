#include "note-state.hpp"

void NoteState::show_current_note()
{
	if (_current_note != nullptr)
	{
		_current_note->show(_canvas);
	}

	_footer.show(_canvas);
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
	if (to_note_create_state != nullptr)
	{
		to_note_create_state(nullptr);
	}
}

void NoteState::on_button_b_pressed()
{
	delete _current_note;
	_current_note = _misskey.get_home_timeline();

	show_current_note();
}

void NoteState::on_button_c_pressed()
{
}

void NoteState::on_key_pressed(const uint8_t keycode)
{
	if (keycode == 0x6E)
	{
		// n (左)
		Note* const next_note = _misskey.get_after_note(_current_note);
		delete _current_note;
		_current_note = next_note;

		show_current_note();
		return;
	}

	if (keycode == 0x24)
	{
		// $ (右)
		Note* const next_note = _misskey.get_before_note(_current_note);
		delete _current_note;
		_current_note = next_note;

		show_current_note();
		return;
	}

	if (keycode == 0x6B)
	{
		// k (上)
		if (_current_note != nullptr)
		{
			_current_note->scroll_up(_canvas);
			_footer.show(_canvas);
		}
		return;
	}

	if (keycode == 0x6D)
	{
		// m (下)
		if (_current_note != nullptr)
		{
			_current_note->scroll_down(_canvas);
			_footer.show(_canvas);
		}
		return;
	}

	if (keycode == 0x72)
	{
		// r
		// Reply
		if (_current_note != nullptr)
		{
			if (to_note_create_state != nullptr)
			{
				to_note_create_state(_current_note);
			}
		}
		return;
	}

	if (keycode == 0x52)
	{
		// R
		// Renote
		if (_current_note != nullptr)
		{
			String renote_id = _current_note->get_id();
			_misskey.renote(renote_id);

			on_button_b_pressed();
		}
		return;
	}
}