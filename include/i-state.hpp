#pragma once

#include <Arduino.h>

class IState
{
public:
	virtual void begin() = 0;

	virtual void update() = 0;

	virtual void on_button_a_pressed()
	{

	}

	virtual void on_button_b_pressed()
	{

	}

	virtual void on_button_c_pressed()
	{

	}
};