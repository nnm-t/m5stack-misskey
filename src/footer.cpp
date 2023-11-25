#include "footer.hpp"

void Footer::show(M5Canvas& canvas)
{
	canvas.fillRect(0, 119, 240, 16, accent_color);

	canvas.setTextDatum(TC_DATUM);
	canvas.setFont(&fonts::lgfxJapanGothic_16);

	canvas.setTextColor(foreground_color, accent_color);

	canvas.drawString(_left, 40, 119);
	canvas.drawRect(10, 119, 60, 16, foreground_color);

	canvas.drawString(_center, 120, 119);
	canvas.drawRect(90, 119, 60, 16, foreground_color);

	canvas.drawString(_right, 200, 119);
	canvas.drawRect(170, 119, 60, 16, foreground_color);

	canvas.setTextDatum(TL_DATUM);
	canvas.setFont(&fonts::lgfxJapanGothic_16);
}

void Footer::set_left(const char* text)
{
	_left = text;
}

void Footer::set_center(const char* text)
{
	_center = text;
}

void Footer::set_right(const char* text)
{
	_right = text;
}