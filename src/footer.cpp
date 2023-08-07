#include "footer.hpp"

void Footer::show()
{
	M5.Lcd.fillRect(0, 216, 320, 24, accent_color);

	M5.Lcd.setTextDatum(TC_DATUM);
	M5.Lcd.setFont(&fonts::lgfxJapanGothic_24);

	M5.Lcd.setTextColor(foreground_color, accent_color);

	M5.Lcd.drawString(_left, 60, 216);
	M5.Lcd.drawRect(20, 216, 80, 24, foreground_color);

	M5.Lcd.drawString(_center, 160, 216);
	M5.Lcd.drawRect(120, 216, 80, 24, foreground_color);

	M5.Lcd.drawString(_right, 260, 216);
	M5.Lcd.drawRect(220, 216, 80, 24, foreground_color);

	M5.Lcd.setTextDatum(TL_DATUM);
	M5.Lcd.setFont(&fonts::lgfxJapanGothic_20);
}