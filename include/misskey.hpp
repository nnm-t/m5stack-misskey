#pragma once

#include <Arduino.h>

#include <M5Unified.hpp>
#include <ArduinoJson.h>

#include "settings.hpp"
#include "https.hpp"
#include "note.hpp"
#include "note-visibility.hpp"

class Misskey
{
    static constexpr const char* misskey_host = "https://misskey.io";
    static constexpr const char* misskey_api = "/api";
    static constexpr const char* misskey_api_notes_timeline = "/notes/timeline";
    static constexpr const char* misskey_api_notes_create = "/notes/create";
    static constexpr const char* content_type_json = "application/json";


	Settings& _settings;
	HTTPS& _https;

    StaticJsonDocument<4096> _json_request;
    StaticJsonDocument<16384> _json_response;

	const DeserializationError get_note();

	String submit_note();

public:
	Misskey(Settings& settings, HTTPS& https) : _settings(settings), _https(https), _json_request(StaticJsonDocument<4096>()), _json_response(StaticJsonDocument<16384>())
	{

	}

	String create_note(String& text, const NoteVisibility visibility = NoteVisibility::Public, bool local_only = false);

	Note* get_home_timeline();

	Note* get_before_note(Note* note);

	Note* get_after_note(Note* note);
};