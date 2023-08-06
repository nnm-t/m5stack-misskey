#pragma once

#include <Arduino.h>
#include <HTTPClient.h>

#include "settings.hpp"

class HTTPS
{
	Settings& _settings;
public:
	HTTPS(Settings& settings) : _settings(settings)
	{

	}

	String post(String& url, String& content_type, String& content);
};