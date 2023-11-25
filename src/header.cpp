#include "header.hpp"

void Header::begin()
{
	update();
}

void Header::update()
{
	_canvas.fillRect(0, 0, 240, 16, accent_color);

	_canvas.setTextColor(foreground_color, accent_color);
	_canvas.setFont(&fonts::lgfxJapanGothic_16);

	_canvas.drawBmpFile(SD, _settings.get_icon(), 0, 0);

	_canvas.drawString(_settings.get_title(), 16, 0);
	_canvas.drawString("%", 232, 0);

	_canvas.fillRect(208, 0, 24, 16, accent_color);

	const int32_t battery_level = M5.Power.getBatteryLevel();

	_canvas.drawString(String(battery_level), 208, 0);

	_canvas.setFont(&fonts::lgfxJapanGothic_16);
}

void Header::print(const char* text)
{
	_canvas.fillRect(16, 0, 192, 16, accent_color);
	_canvas.setTextColor(foreground_color, accent_color);
	_canvas.setFont(&fonts::lgfxJapanGothic_16);

	_canvas.drawString(text, 16, 0);
}

void Header::print(String& text)
{
	_canvas.fillRect(16, 0, 192, 16, accent_color);
	_canvas.setTextColor(foreground_color, accent_color);
	_canvas.setFont(&fonts::lgfxJapanGothic_16);

	_canvas.drawString(text, 16, 0);
}