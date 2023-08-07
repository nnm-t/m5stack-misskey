#include "faces-keyboard.hpp"

void FacesKeyboard::begin()
{
	switch (M5.getBoard())
	{
		case m5::board_t::board_M5Stack:
			_wire = &Wire;
			_interrupt_pin = 5;
			break;
		case m5::board_t::board_M5StackCore2:
			_wire = &Wire1;
			_interrupt_pin = 33;
			break;
		case m5::board_t::board_M5StackCoreS3:
			_wire = &Wire1;
			_interrupt_pin = 1;
			break;
		default:
			return;
	}

	pinMode(_interrupt_pin, INPUT_PULLUP);
}

void FacesKeyboard::update()
{
	if (_wire == nullptr)
	{
		return;
	}

	if (digitalRead(_interrupt_pin) == HIGH)
	{
		return;
	}

	_wire->requestFrom(i2c_address, 1);

	while (_wire->available())
	{
		const uint8_t keycode = Wire.read();

		if (on_key_pressed != nullptr)
		{
			on_key_pressed(keycode);
		}
	}
}