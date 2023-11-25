#include "cardputer-keyboard.hpp"

void CardputerKeyboard::output_row(const uint8_t row)
{
	digitalWrite(a0_pin, row & 0x01 ? HIGH : LOW);
	digitalWrite(a1_pin, row & 0x02 ? HIGH : LOW);
	digitalWrite(a2_pin, row & 0x04 ? HIGH : LOW);
}

void CardputerKeyboard::send_keycode(const uint8_t single, const uint8_t caps, const uint8_t func, const uint8_t ctrl, const uint8_t opt, const uint8_t alt)
{
	_is_key_release = false;

	if (_is_key_pressing)
	{
		return;
	}

	_is_key_pressing = true;

	if (on_key_pressed == nullptr)
	{
		return;
	}

	if (_is_func_press)
	{
		on_key_pressed(func);
		return;
	}

	if (_is_ctrl_press)
	{
		on_key_pressed(ctrl);
		return;
	}

	if (_is_opt_press)
	{
		on_key_pressed(opt);
		return;
	}

	if (_is_alt_press)
	{
		on_key_pressed(alt);
		return;
	}

	if (_is_caps_press)
	{
		on_key_pressed(caps);
		return;
	}

	on_key_pressed(single);
}

void CardputerKeyboard::begin()
{
	pinMode(a0_pin, OUTPUT);
	pinMode(a1_pin, OUTPUT);
	pinMode(a2_pin, OUTPUT);

	pinMode(c0_pin, INPUT_PULLUP);
	pinMode(c1_pin, INPUT_PULLUP);
	pinMode(c2_pin, INPUT_PULLUP);
	pinMode(c3_pin, INPUT_PULLUP);
	pinMode(c4_pin, INPUT_PULLUP);
	pinMode(c5_pin, INPUT_PULLUP);
	pinMode(c6_pin, INPUT_PULLUP);
}

void CardputerKeyboard::scan_modifier_key()
{
	output_row(0x00);

	if (digitalRead(c0_pin) == LOW)
	{
		// Opt
		_is_opt_press = true;
	}

	output_row(0x01);

	if (digitalRead(c0_pin) == LOW)
	{
		// Caps
		_is_caps_press = true;
	}

	output_row(0x04);

	if (digitalRead(c0_pin) == LOW)
	{
		// Ctrl
		_is_ctrl_press = true;
	}

	if (digitalRead(c1_pin) == LOW)
	{
		// Alt
		_is_alt_press = true;
	}

	output_row(0x05);

	if (digitalRead(c0_pin) == LOW)
	{
		// Func
		_is_func_press = true;
	}
}

void CardputerKeyboard::scan_r0()
{
	output_row(0x00);

	if (digitalRead(c1_pin) == LOW)
	{
		// Z
		send_keycode('z', 'Z');
		return;
	}

	if (digitalRead(c2_pin) == LOW)
	{
		// C
		send_keycode('c', 'C');
		return;
	}

	if (digitalRead(c3_pin) == LOW)
	{
		// B
		send_keycode('b', 'B');
		return;
	}

	if (digitalRead(c4_pin) == LOW)
	{
		// M
		send_keycode('m', 'M');
		return;
	}

	if (digitalRead(c5_pin) == LOW)
	{
		// .
		send_keycode('.', '>', 0xC0);
		return;
	}

	if (digitalRead(c6_pin) == LOW)
	{
		// Space
		send_keycode(' ', ' ');
		return;
	}
}

void CardputerKeyboard::scan_r1()
{
	output_row(0x01);

	if (digitalRead(c1_pin) == LOW)
	{
		// S
		send_keycode('s', 'S');
		return;
	}

	if (digitalRead(c2_pin) == LOW)
	{
		// F
		send_keycode('f', 'F', 0x9D);
		return;
	}

	if (digitalRead(c3_pin) == LOW)
	{
		// H
		send_keycode('h', 'H');
		return;
	}

	if (digitalRead(c4_pin) == LOW)
	{
		// K
		send_keycode('k', 'K');
		return;
	}

	if (digitalRead(c5_pin) == LOW)
	{
		// ;
		send_keycode(';', ':', 0xB7);
		return;
	}

	if (digitalRead(c6_pin) == LOW)
	{
		// Enter
		send_keycode('\n', '\r');
		return;
	}
}

void CardputerKeyboard::scan_r2()
{
	output_row(0x02);

	if (digitalRead(c0_pin) == LOW)
	{
		// Q
		send_keycode('q', 'Q');
		return;
	}

	if (digitalRead(c1_pin) == LOW)
	{
		// E
		send_keycode('e', 'E');
		return;
	}

	if (digitalRead(c2_pin) == LOW)
	{
		// T
		send_keycode('t', 'T');
		return;
	}

	if (digitalRead(c3_pin) == LOW)
	{
		// U
		send_keycode('u', 'U');
		return;
	}

	if (digitalRead(c4_pin) == LOW)
	{
		// O
		send_keycode('o', 'O');
		return;
	}

	if (digitalRead(c5_pin) == LOW)
	{
		// [
		send_keycode('[', '{');
		return;
	}

	if (digitalRead(c6_pin) == LOW)
	{
		// Back Slash
		send_keycode('\\', '|');
		return;
	}
}

void CardputerKeyboard::scan_r3()
{
	output_row(0x03);

	if (digitalRead(c0_pin) == LOW)
	{
		// 1
		send_keycode('1', '!', 0x91);
		return;
	}

	if (digitalRead(c1_pin) == LOW)
	{
		// 3
		send_keycode('3', '#', 0x93);
		return;
	}

	if (digitalRead(c2_pin) == LOW)
	{
		// 5
		send_keycode('5', '%');
		return;
	}

	if (digitalRead(c3_pin) == LOW)
	{
		// 7
		send_keycode('7', '&');
		return;
	}

	if (digitalRead(c4_pin) == LOW)
	{
		// 9
		send_keycode('9', '(');
		return;
	}

	if (digitalRead(c5_pin) == LOW)
	{
		// _
		send_keycode('_', '-');
		return;
	}

	if (digitalRead(c6_pin) == LOW)
	{
		// Back Space
		send_keycode(0x08, 0x7F);
		return;
	}
}

void CardputerKeyboard::scan_r4()
{
	output_row(0x04);

	if (digitalRead(c2_pin) == LOW)
	{
		// X
		send_keycode('x', 'X');
		return;
	}

	if (digitalRead(c3_pin) == LOW)
	{
		// V
		send_keycode('v', 'V', 0xA9);
		return;
	}

	if (digitalRead(c4_pin) == LOW)
	{
		// N
		send_keycode('n', 'N');
		return;
	}

	if (digitalRead(c5_pin) == LOW)
	{
		// ,
		send_keycode(',', '<', 0xBF);
		return;
	}

	if (digitalRead(c6_pin) == LOW)
	{
		// /
		send_keycode('/', '?', 0xC1);
		return;
	}
}

void CardputerKeyboard::scan_r5()
{
	output_row(0x05);

	if (digitalRead(c1_pin) == LOW)
	{
		// A
		send_keycode('a', 'A');
		return;
	}

	if (digitalRead(c2_pin) == LOW)
	{
		// D
		send_keycode('d', 'D');
		return;
	}

	if (digitalRead(c3_pin) == LOW)
	{
		// G
		send_keycode('g', 'G');
		return;
	}

	if (digitalRead(c4_pin) == LOW)
	{
		// J
		send_keycode('j', 'J');
		return;
	}

	if (digitalRead(c5_pin) == LOW)
	{
		// L
		send_keycode('l', 'L');
		return;
	}

	if (digitalRead(c6_pin) == LOW)
	{
		// '
		send_keycode('\'', '\"');
		return;
	}
}

void CardputerKeyboard::scan_r6()
{
	output_row(0x06);

	if (digitalRead(c0_pin) == LOW)
	{
		// Tab
		send_keycode(0xFF, 0xFF);
		return;
	}

	if (digitalRead(c1_pin) == LOW)
	{
		// W
		send_keycode('w', 'W');
		return;
	}

	if (digitalRead(c2_pin) == LOW)
	{
		// R
		send_keycode('r', 'R');
		return;
	}

	if (digitalRead(c3_pin) == LOW)
	{
		// Y
		send_keycode('y', 'Y');
		return;
	}

	if (digitalRead(c4_pin) == LOW)
	{
		// I
		send_keycode('i', 'I');
		return;
	}

	if (digitalRead(c5_pin) == LOW)
	{
		// P
		send_keycode('p', 'P');
		return;
	}

	if (digitalRead(c6_pin) == LOW)
	{
		// ]
		send_keycode(']', '}');
		return;
	}
}

void CardputerKeyboard::scan_r7()
{
	output_row(0x07);

	if (digitalRead(c0_pin) == LOW)
	{
		// `
		send_keycode('`', '~');
		return;
	}

	if (digitalRead(c1_pin) == LOW)
	{
		// 2
		send_keycode('2', '@', 0x92);
		return;
	}

	if (digitalRead(c2_pin) == LOW)
	{
		// 4
		send_keycode('4', '$');
		return;
	}

	if (digitalRead(c3_pin) == LOW)
	{
		// 6
		send_keycode('6', '^');
		return;
	}

	if (digitalRead(c4_pin) == LOW)
	{
		// 8
		send_keycode('8', '*');
		return;
	}

	if (digitalRead(c5_pin) == LOW)
	{
		// 0
		send_keycode('0', ')');
		return;
	}

	if (digitalRead(c6_pin) == LOW)
	{
		// =
		send_keycode('=', '+');
		return;
	}
}

void CardputerKeyboard::update()
{
	_is_key_release = true;

	scan_modifier_key();

	scan_r0();
	scan_r1();
	scan_r2();
	scan_r3();
	scan_r4();
	scan_r5();
	scan_r6();
	scan_r7();

	if (_is_key_release)
	{
		_is_key_pressing = false;
	}
	
	_is_caps_press = false;
	_is_func_press = false;
	_is_ctrl_press = false;
	_is_opt_press = false;
	_is_alt_press = false;
}