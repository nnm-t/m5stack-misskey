#include "note-create-state.hpp"

void NoteCreateState::show()
{
	M5.Lcd.fillRect(0, 24, 320, 192, background_color);
	M5.Lcd.setCursor(0, 48);
	M5.Lcd.setTextColor(foreground_color, background_color);
	M5.Lcd.setFont(&fonts::lgfxJapanGothic_20);

	M5.Lcd.print(_text);
}

void NoteCreateState::begin()
{
	M5.Lcd.fillRect(0, 24, 320, 216, background_color);

	_footer.show();

	_text.clear();
}

void NoteCreateState::update()
{

}

void NoteCreateState::on_key_pressed(const uint8_t keycode)
{
	if (keycode == 0x08)
	{
		// BackSpace
		if (_text.length() > 0)
		{
			_text.remove(_text.length() - 1);
		}
	}
	else if (keycode < 0x7F)
	{
		// 英数字
		_text += static_cast<char>(keycode);
	}

	show();
}

void NoteCreateState::on_button_c_pressed()
{
	_misskey.create_note(_text, NoteVisibility::Public, true);
}