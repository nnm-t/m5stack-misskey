#include "misskey.hpp"

const DeserializationError Misskey::get_note()
{
    String request;
    serializeJson(_json_request, request);

    String url = misskey_host + String(misskey_api) + misskey_api_notes_timeline;
	String content_type(content_type_json);
    String response = _https.post(url, content_type, request);

    Serial.println(response);

    return deserializeJson(_json_response, response);
}

Note* Misskey::get_home_timeline()
{
    _json_request.clear();

    _json_request["i"] = _settings.get_api_token();
    _json_request["limit"] = 1;

    if (get_note() != DeserializationError::Ok)
    {
        M5.Lcd.println("Response deserialize failed.");
        return nullptr;
    }
    
    JsonVariant json_note = _json_response[0];

    return new Note(json_note);
}

Note* Misskey::get_before_note(Note* note)
{
    _json_request.clear();

    _json_request["i"] = _settings.get_api_token();
    _json_request["limit"] = 1;
	_json_request["untilId"] = note->get_id();

    if (get_note() != DeserializationError::Ok)
    {
        M5.Lcd.println("Response deserialize failed.");
        return nullptr;
    }
    
    JsonVariant json_note = _json_response[0];

    return new Note(json_note);
}

Note* Misskey::get_after_note(Note* note)
{
    _json_request.clear();

    _json_request["i"] = _settings.get_api_token();
    _json_request["limit"] = 1;
	_json_request["sinceId"] = note->get_id();

    if (get_note() != DeserializationError::Ok)
    {
        M5.Lcd.println("Response deserialize failed.");
        return nullptr;
    }
    
    JsonVariant json_note = _json_response[0];

    return new Note(json_note);
}