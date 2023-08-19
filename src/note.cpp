#include "note.hpp"

void Note::show(M5Canvas& canvas)
{
	canvas.fillRect(0, 24, 320, 192, background_color);
	canvas.setCursor(0, 24);
	canvas.setFont(&fonts::lgfxJapanGothic_24);

	if (_json.containsKey("renote"))
	{
		// Renote
		JsonVariant json_renote = _json["renote"];

		JsonVariant json_user = json_renote["user"];
		String name = json_user["name"];
		String user_name = json_user["username"];

		String text = json_renote["text"];
		String date_time = json_renote["createdAt"];

		canvas.setTextColor(accent2_color, background_color);
		canvas.println(name);
		canvas.print("@");
		canvas.println(user_name);

		canvas.setTextColor(foreground_color, background_color);
		canvas.println(text);
		
		canvas.setTextColor(gray_color, background_color);
		canvas.println(date_time);
		canvas.print("\n");
		return;
	}

	JsonVariant json_user = _json["user"];
	String name = json_user["name"];
	String user_name = json_user["username"];

	String text = _json["text"];
	String date_time = _json["createdAt"];

	canvas.setTextColor(accent_color, background_color);
	canvas.println(name);
	canvas.print("@");
	canvas.println(user_name);

	canvas.setTextColor(foreground_color, background_color);
	canvas.println(text);
	
	canvas.setTextColor(gray_color, background_color);
	canvas.println(date_time);
	canvas.print("\n");
}

const char* Note::get_id()
{
	return _json["id"].as<const char*>();
}