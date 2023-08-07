#include "header.hpp"

void Header::begin()
{
	M5.Lcd.fillRect(0, 0, 320, 24, accent_color);

	M5.Lcd.setTextColor(foreground_color, accent_color);
	M5.Lcd.setFont(&fonts::lgfxJapanGothic_24);

	M5.Lcd.drawString("Misskey.io", 24, 0);
	M5.Lcd.drawString("%", 308, 0);

	M5.Lcd.setFont(&fonts::lgfxJapanGothic_20);
}

void Header::update()
{
	M5.Lcd.fillRect(272, 0, 36, 24, accent_color);

	M5.Lcd.setTextColor(foreground_color, accent_color);
	M5.Lcd.setFont(&fonts::lgfxJapanGothic_24);

	const int32_t battery_level = M5.Power.getBatteryLevel();

	M5.Lcd.drawString(String(battery_level), 272, 0);

	M5.Lcd.setFont(&fonts::lgfxJapanGothic_20);
}