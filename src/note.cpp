#include "note.hpp"

void Note::show_name(M5Canvas& canvas, String& name, String& user_name, const uint32_t color)
{
	canvas.setCursor(0, _y);
	canvas.setTextWrap(false);
	canvas.setTextColor(color, background_color);
	canvas.println(name);

	canvas.setCursor(0, _y + 16);
	canvas.print("@");
	canvas.println(user_name);
	canvas.setTextWrap(true);
}

void Note::show_text(M5Canvas& canvas, String& text)
{
	canvas.setCursor(0, _y + 32);
	canvas.setTextColor(foreground_color, background_color);
	canvas.println(text);
}

void Note::show_date_time(M5Canvas& canvas, String& date_time)
{
	canvas.setTextColor(gray_color, background_color);

	// 文字列からtm構造体へ変換
	struct tm tm;
	strptime(date_time.c_str(), "%Y-%m-%dT%H:%M:%S", &tm);
	// time_tを取得
	time_t time = mktime(&tm);
	// 9時間進める
	time += 9 * 60 * 60;

	// 描画
	struct tm* tm2 = localtime(&time);
	canvas.printf("%d/%d/%d %d:%02d:%02d\n", tm2->tm_year + 1900, tm2->tm_mon + 1, tm2->tm_mday, tm2->tm_hour, tm2->tm_min, tm2->tm_sec);
}

void Note::show_visibility(M5Canvas& canvas, String& visibility)
{
	if (visibility == "home")
	{
		canvas.drawBmpFile(SD, "/home_16.bmp", 224, _y + 16);
		return;
	}

	if (visibility == "followers")
	{
		canvas.drawBmpFile(SD, "/followers_16.bmp", 224, _y + 16);
		return;
	}
}

void Note::show(HTTPS& https, M5Canvas& canvas)
{
	canvas.fillRect(0, 16, 240, 103, background_color);
	canvas.setCursor(0, _y);
	canvas.setFont(&fonts::lgfxJapanGothic_16);

	if (_json.containsKey("renote"))
	{
		// Renote
		JsonVariant json_renote = _json["renote"];

		JsonVariant json_user = json_renote["user"];
		String name = json_user["name"];
		String user_name = json_user["username"];
		if (!json_user["host"].isNull())
		{
			user_name += "@";
			user_name += json_user["host"].as<const char*>();
		}
		String avatar_url = json_renote["avatarUrl"];

		String text = json_renote["text"];
		String date_time = json_renote["createdAt"];
		String visibility = json_renote["visibility"];

		show_name(canvas, name, user_name, accent2_color);
		show_text(canvas, text);
		show_date_time(canvas, date_time);
		show_visibility(canvas, visibility);

		canvas.print("\n");
		return;
	}

	JsonVariant json_user = _json["user"];
	String name = json_user["name"];
	String user_name = json_user["username"];
	if (!json_user["host"].isNull())
	{
		user_name += "@";
		user_name += json_user["host"].as<const char*>();
	}
	String avatar_url = json_user["avatarUrl"];

	String text = _json["text"];
	String date_time = _json["createdAt"];
	String visibility = _json["visibility"];

	show_name(canvas, name, user_name, accent_color);
	show_text(canvas, text);
	show_date_time(canvas, date_time);
	show_visibility(canvas, visibility);
	
	canvas.print("\n");
}

const char* Note::get_id()
{
	return _json["id"].as<const char*>();
}

const char* Note::get_username()
{
	return _json["user"]["username"].as<const char*>();
}

void Note::scroll_up(HTTPS& https, M5Canvas& canvas)
{
	_y += 16;
	show(https, canvas);
}

void Note::scroll_down(HTTPS& https, M5Canvas& canvas)
{
	_y -= 16;
	show(https, canvas);
}