#include "header.hpp"

void Header::begin()
{
	_canvas.fillRect(0, 0, 320, 24, accent_color);

	_canvas.setTextColor(foreground_color, accent_color);
	_canvas.setFont(&fonts::lgfxJapanGothic_24);

	_canvas.drawString("Misskey.io", 24, 0);
	_canvas.drawString("%", 308, 0);

	_canvas.setFont(&fonts::lgfxJapanGothic_20);
}

void Header::update()
{
	_canvas.fillRect(272, 0, 36, 24, accent_color);

	_canvas.setTextColor(foreground_color, accent_color);
	_canvas.setFont(&fonts::lgfxJapanGothic_24);

	const int32_t battery_level = M5.Power.getBatteryLevel();

	_canvas.drawString(String(battery_level), 272, 0);

	_canvas.setFont(&fonts::lgfxJapanGothic_20);
}

void Header::print(const char* text)
{
	_canvas.fillRect(24, 0, 248, 24, accent_color);
	_canvas.setTextColor(foreground_color, accent_color);
	_canvas.setFont(&fonts::lgfxJapanGothic_24);

	_canvas.drawString(text, 24, 0);
}

void Header::print(String& text)
{
	_canvas.fillRect(24, 0, 248, 24, accent_color);
	_canvas.setTextColor(foreground_color, accent_color);
	_canvas.setFont(&fonts::lgfxJapanGothic_24);

	_canvas.drawString(text, 24, 0);
}