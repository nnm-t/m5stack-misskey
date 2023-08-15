#pragma once

#include <Arduino.h>

#include <M5Unified.hpp>

#include "color.hpp"

class Footer
{
	String _left;
	String _center;
	String _right;

public:
	Footer(const char* left, const char* center, const char* right) : _left(String(left)), _center(String(center)), _right(String(right))
	{

	}

	Footer(String& left, String& center, String& right) : _left(left), _center(center), _right(right)
	{

	}

	void show();

	void set_left(const char* text);

	void set_center(const char* text);

	void set_right(const char* text);
};