#include "footer.hpp"

void Footer::show(M5Canvas& canvas)
{
	canvas.fillRect(0, 216, 320, 24, accent_color);

	canvas.setTextDatum(TC_DATUM);
	canvas.setFont(&fonts::lgfxJapanGothic_24);

	canvas.setTextColor(foreground_color, accent_color);

	canvas.drawString(_left, 60, 216);
	canvas.drawRect(20, 216, 80, 24, foreground_color);

	canvas.drawString(_center, 160, 216);
	canvas.drawRect(120, 216, 80, 24, foreground_color);

	canvas.drawString(_right, 260, 216);
	canvas.drawRect(220, 216, 80, 24, foreground_color);

	canvas.setTextDatum(TL_DATUM);
	canvas.setFont(&fonts::lgfxJapanGothic_20);
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