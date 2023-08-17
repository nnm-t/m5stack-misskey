#pragma once

#include <Arduino.h>

#include <M5Unified.h>
#include <UrlEncode.h>

#include "https.hpp"

class InputMethod
{
	static constexpr const char* api_url = "http://www.google.com/transliterate?langpair=ja-Hira|ja&text=";

	HTTPS& _https;

    StaticJsonDocument<2048> _json_response;

	size_t _result_number = 0;
	size_t _index = 0;

public:
	InputMethod(HTTPS& https) : _https(https), _json_response(StaticJsonDocument<2048>())
	{

	}

	String request(String& text);

	String next();
};