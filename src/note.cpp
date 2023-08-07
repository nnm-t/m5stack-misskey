#include "note.hpp"

void Note::show()
{
	M5.Lcd.clear();
	M5.Lcd.setCursor(0, 24);

	if (_json.containsKey("renote"))
	{
		// Renote
		JsonVariant json_renote = _json["renote"];

		JsonVariant json_user = json_renote["user"];
		String name = json_user["name"];
		String user_name = json_user["username"];

		String text = json_renote["text"];
		String date_time = json_renote["createdAt"];

		M5.Lcd.setTextColor(accent2_color, background_color);
		M5.Lcd.print(name);
		M5.Lcd.print(" @");
		M5.Lcd.println(user_name);

		M5.Lcd.setTextColor(foreground_color, background_color);
		M5.Lcd.println(text);
		
		M5.Lcd.setTextColor(gray_color, background_color);
		M5.Lcd.println(date_time);
		M5.Lcd.print("\n");
		return;
	}

	JsonVariant json_user = _json["user"];
	String name = json_user["name"];
	String user_name = json_user["username"];

	String text = _json["text"];
	String date_time = _json["createdAt"];

	M5.Lcd.setTextColor(accent_color, background_color);
	M5.Lcd.print(name);
	M5.Lcd.print(" @");
	M5.Lcd.println(user_name);

	M5.Lcd.setTextColor(foreground_color, background_color);
	M5.Lcd.println(text);
	
	M5.Lcd.setTextColor(gray_color, background_color);
	M5.Lcd.println(date_time);
	M5.Lcd.print("\n");
}

const char* Note::get_id()
{
	return _json["id"].as<const char*>();
}