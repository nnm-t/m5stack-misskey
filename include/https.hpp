#pragma once

#include <Arduino.h>
#include <HTTPClient.h>

#include "color.hpp"
#include "settings.hpp"

class HTTPS
{
	Settings& _settings;
public:
	HTTPS(Settings& settings) : _settings(settings)
	{

	}

	String post(String& url, String& content_type, String& content);

	String http_get(String& url);
};