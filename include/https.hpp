#pragma once

#include <Arduino.h>
#include <HTTPClient.h>

#include "settings.hpp"
#include "header.hpp"

class HTTPS
{
	Settings& _settings;
	Header& _header;

public:
	HTTPS(Settings& settings, Header& header) : _settings(settings), _header(header)
	{

	}

	String post(String& url, String& content_type, String& content);

	String http_get(String& url);
};