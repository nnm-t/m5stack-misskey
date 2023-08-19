#include "note-create-state.hpp"

void NoteCreateState::show()
{
	_canvas.fillRect(0, 24, 320, 192, background_color);
	_canvas.setCursor(0, 48);
	_canvas.setTextColor(foreground_color, background_color);
	_canvas.setFont(&fonts::lgfxJapanGothic_24);

	_canvas.print(_text);

	if (_is_japanese)
	{
		// 日本語入力モード
		_canvas.fillRect(0, 192, 320, 24, foreground_color);
		_canvas.setTextColor(background_color, foreground_color);

		_canvas.setCursor(0, 192);
		_canvas.print(_text_japanese);
		_canvas.print(_text_japanese_temp);

		_canvas.setTextColor(foreground_color, background_color);
	}

	// Visibility Icon
	switch (_visibility)
	{
		case NoteVisibility::Public:
			_canvas.drawBmpFile(SD, "/public.bmp", 272, 24);
			break;
		case NoteVisibility::Home:
			_canvas.drawBmpFile(SD, "/home.bmp", 272, 24);
			break;
		case NoteVisibility::Followers:
			_canvas.drawBmpFile(SD, "/followers.bmp", 272, 24);
			break;
	}

	if (!_local_only)
	{
		_canvas.drawBmpFile(SD, "/federate.bmp", 296, 24);
	}
	else
	{
		_canvas.drawBmpFile(SD, "/de_federate.bmp", 296, 24);
	}

	_footer.show(_canvas);
}

void NoteCreateState::begin()
{
	_canvas.fillRect(0, 24, 320, 216, background_color);

	_visibility = NoteVisibility::Public;
	_local_only = true;

	_text.clear();

	show();
}

void NoteCreateState::update()
{

}

void NoteCreateState::on_key_pressed(const uint8_t keycode)
{
	if (keycode == 0xAF)
	{
		// Alt + 0
		// Visibility
		switch (_visibility)
		{
			case NoteVisibility::Public:
				_visibility = NoteVisibility::Home;
				break;
			case NoteVisibility::Home:
				_visibility = NoteVisibility::Followers;
				break;
			default:
				_visibility = NoteVisibility::Public;
				break;
		}
	}
	else if (keycode == 0x9D)
	{
		// Alt + F
		// Federate
		_local_only = !_local_only;
	}
	else if (keycode == 0x08)
	{
		// BackSpace
		if (_is_japanese)
		{
			_is_translate = false;

			if (_text_japanese_temp.length() > 0)
			{
				_text_japanese_temp.remove(_text_japanese_temp.length() - 1);
			}
			else if (_text_japanese.length() > 0)
			{
				// UTF-8対応
				remove_utf8(_text_japanese);
			}
		}
		else
		{
			// UTF-8対応
			remove_utf8(_text);
		}
	}
	else if (keycode == 0x0D || keycode == 0x0A)
	{
		if (_is_japanese && (!_text_japanese.isEmpty() || !_text_japanese_temp.isEmpty()))
		{
			// 確定 (変換確定を含む)
			_is_translate = false;
			_text += _text_japanese;
			_text += _text_japanese_temp;
			_text_japanese.clear();
			_text_japanese_temp.clear();
		}
		else
		{
			// Enter (CR or LF)
			_text += "\n";
		}
	}
	else if (keycode == 0x20)
	{
		// Space
		if (!_is_japanese)
		{
			// 英数字
			_text += " ";
		}
		else if (!_text_japanese.isEmpty() || !_text_japanese_temp.isEmpty())
		{
			String translate_text = _text_japanese + _text_japanese_temp;
			_text_japanese_temp.clear();

			if (!_is_translate)
			{
				// 変換開始
				_text_japanese = _input_method.request(translate_text);
				_is_translate = true;
			}
			else
			{
				// 次候補
				_text_japanese = _input_method.next();
			}
		}
	}
	else if (keycode > 0x20 && keycode < 0x7F)
	{
		if (_is_translate)
		{
			// 変換中は無効
		}
		else if (_is_japanese)
		{
			add_kana(static_cast<char>(keycode));
		}
		else
		{
			// 英数字
			_text += static_cast<char>(keycode);
		}
	}

	show();
}

void NoteCreateState::on_button_b_pressed()
{
	// 日本語切り替え
	_is_japanese = !_is_japanese;

	if (_is_japanese)
	{
		_footer.set_center("かな");
	}
	else
	{
		_footer.set_center("英数");
		_is_translate = false;
		_text_japanese.clear();
		_text_japanese_temp.clear();
	}

	_footer.show(_canvas);

	show();
}

void NoteCreateState::on_button_c_pressed()
{
	_misskey.create_note(_text, _visibility, _local_only);
}

void NoteCreateState::add_kana(const char c)
{
	_text_japanese_temp += c;

	// 3文字
	kana_from_temp("xya", "ゃ");
	kana_from_temp("xyu", "ゅ");
	kana_from_temp("xyo", "ょ");
	kana_from_temp("xtu", "っ");
	kana_from_temp("xwa", "ゎ");
	kana_from_temp("lya", "ゃ");
	kana_from_temp("lyu", "ゅ");
	kana_from_temp("lyo", "ょ");
	kana_from_temp("ltu", "っ");
	kana_from_temp("lwa", "ゎ");
	kana_from_temp("chi", "ち");
	kana_from_temp("kya", "きゃ");
	kana_from_temp("kyu", "きゅ");
	kana_from_temp("kyo", "きょ");
	kana_from_temp("sya", "じゃ");
	kana_from_temp("syu", "しゅ");
	kana_from_temp("syo", "しょ");
	kana_from_temp("sha", "じゃ");
	kana_from_temp("shu", "しゅ");
	kana_from_temp("sho", "しょ");
	kana_from_temp("tya", "ちゃ");
	kana_from_temp("tyu", "ちゅ");
	kana_from_temp("tyo", "ちょ");
	kana_from_temp("nya", "にゃ");
	kana_from_temp("nyu", "にゅ");
	kana_from_temp("nyo", "にょ");
	kana_from_temp("hya", "ひゃ");
	kana_from_temp("hyu", "ひゅ");
	kana_from_temp("hyo", "ひょ");
	kana_from_temp("mya", "みゃ");
	kana_from_temp("myu", "みゅ");
	kana_from_temp("myo", "みょ");
	kana_from_temp("rya", "りゃ");
	kana_from_temp("ryu", "りゅ");
	kana_from_temp("ryo", "りょ");
	kana_from_temp("gya", "ぎゃ");
	kana_from_temp("gyu", "ぎゅ");
	kana_from_temp("gyo", "ぎょ");
	kana_from_temp("zya", "じゃ");
	kana_from_temp("zyu", "じゅ");
	kana_from_temp("zyo", "じょ");
	kana_from_temp("dya", "ぢゃ");
	kana_from_temp("dyu", "ぢゅ");
	kana_from_temp("dyo", "ぢょ");
	kana_from_temp("bya", "びゃ");
	kana_from_temp("byu", "びゅ");
	kana_from_temp("byo", "びょ");
	kana_from_temp("pya", "ぴゃ");
	kana_from_temp("pyu", "ぴゅ");
	kana_from_temp("pyo", "ぴょ");
	kana_from_temp("kka", "っか");
	kana_from_temp("kki", "っき");
	kana_from_temp("kku", "っく");
	kana_from_temp("kke", "っけ");
	kana_from_temp("kko", "っこ");
	kana_from_temp("ssa", "っさ");
	kana_from_temp("ssi", "っし");
	kana_from_temp("ssu", "っす");
	kana_from_temp("sse", "っせ");
	kana_from_temp("sso", "っそ");
	kana_from_temp("tta", "った");
	kana_from_temp("tti", "っち");
	kana_from_temp("ttu", "っつ");
	kana_from_temp("tte", "って");
	kana_from_temp("tto", "っと");
	kana_from_temp("hha", "っは");
	kana_from_temp("hhi", "っひ");
	kana_from_temp("hhu", "っふ");
	kana_from_temp("ffu", "っふ");
	kana_from_temp("hhe", "っへ");
	kana_from_temp("hho", "っほ");
	kana_from_temp("mma", "っま");
	kana_from_temp("mmi", "っみ");
	kana_from_temp("mmu", "っむ");
	kana_from_temp("mme", "っめ");
	kana_from_temp("mmo", "っも");
	kana_from_temp("yya", "っや");
	kana_from_temp("yyu", "っゆ");
	kana_from_temp("yyo", "っよ");
	kana_from_temp("rra", "っら");
	kana_from_temp("rri", "っり");
	kana_from_temp("rru", "っる");
	kana_from_temp("rre", "っれ");
	kana_from_temp("rro", "っろ");
	kana_from_temp("wwa", "っわ");
	kana_from_temp("wwo", "っを");
	kana_from_temp("gga", "っが");
	kana_from_temp("ggi", "っぎ");
	kana_from_temp("ggu", "っぐ");
	kana_from_temp("gge", "っげ");
	kana_from_temp("ggo", "っご");
	kana_from_temp("zza", "っざ");
	kana_from_temp("zzi", "っじ");
	kana_from_temp("zzu", "っず");
	kana_from_temp("zze", "っぜ");
	kana_from_temp("zzo", "っぞ");
	kana_from_temp("dda", "っだ");
	kana_from_temp("ddi", "っぢ");
	kana_from_temp("ddu", "っづ");
	kana_from_temp("dde", "っで");
	kana_from_temp("ddo", "っど");
	kana_from_temp("bba", "っば");
	kana_from_temp("bbi", "っび");
	kana_from_temp("bbu", "っぶ");
	kana_from_temp("bbe", "っべ");
	kana_from_temp("bbo", "っぼ");
	kana_from_temp("ppa", "っぱ");
	kana_from_temp("ppi", "っぴ");
	kana_from_temp("ppu", "っぷ");
	kana_from_temp("ppe", "っぺ");
	kana_from_temp("ppo", "っぽ");
	// 2文字
	kana_from_temp("ka", "か");
	kana_from_temp("ki", "き");
	kana_from_temp("ku", "く");
	kana_from_temp("ke", "け");
	kana_from_temp("ko", "こ");
	kana_from_temp("sa", "さ");
	kana_from_temp("si", "し");
	kana_from_temp("su", "す");
	kana_from_temp("se", "せ");
	kana_from_temp("so", "そ");
	kana_from_temp("ta", "た");
	kana_from_temp("ti", "ち");
	kana_from_temp("tu", "つ");
	kana_from_temp("te", "て");
	kana_from_temp("to", "と");
	kana_from_temp("na", "な");
	kana_from_temp("ni", "に");
	kana_from_temp("nu", "ぬ");
	kana_from_temp("ne", "ね");
	kana_from_temp("no", "の");
	kana_from_temp("ha", "は");
	kana_from_temp("hi", "ひ");
	kana_from_temp("hu", "ふ");
	kana_from_temp("fu", "ふ");
	kana_from_temp("he", "へ");
	kana_from_temp("ho", "ほ");
	kana_from_temp("ma", "ま");
	kana_from_temp("mi", "み");
	kana_from_temp("mu", "む");
	kana_from_temp("me", "め");
	kana_from_temp("mo", "も");
	kana_from_temp("ya", "や");
	kana_from_temp("yu", "ゆ");
	kana_from_temp("yo", "よ");
	kana_from_temp("ra", "ら");
	kana_from_temp("ri", "り");
	kana_from_temp("ru", "る");
	kana_from_temp("re", "れ");
	kana_from_temp("ro", "ろ");
	kana_from_temp("wa", "わ");
	kana_from_temp("wo", "を");
	kana_from_temp("nn", "ん");
	kana_from_temp("ga", "が");
	kana_from_temp("gi", "ぎ");
	kana_from_temp("gu", "ぐ");
	kana_from_temp("ge", "げ");
	kana_from_temp("go", "ご");
	kana_from_temp("za", "ざ");
	kana_from_temp("zi", "じ");
	kana_from_temp("ji", "じ");
	kana_from_temp("zu", "ず");
	kana_from_temp("ze", "ぜ");
	kana_from_temp("zo", "ぞ");
	kana_from_temp("da", "だ");
	kana_from_temp("di", "ぢ");
	kana_from_temp("du", "づ");
	kana_from_temp("de", "で");
	kana_from_temp("do", "ど");
	kana_from_temp("ba", "ば");
	kana_from_temp("bi", "び");
	kana_from_temp("bu", "ぶ");
	kana_from_temp("be", "べ");
	kana_from_temp("bo", "ぼ");
	kana_from_temp("pa", "ぱ");
	kana_from_temp("pi", "ぴ");
	kana_from_temp("pu", "ぷ");
	kana_from_temp("pe", "ぽ");
	kana_from_temp("po", "ぽ");
	kana_from_temp("va", "ゔぁ");
	kana_from_temp("vi", "ゔぃ");
	kana_from_temp("vu", "ゔ");
	kana_from_temp("ve", "ゔぇ");
	kana_from_temp("vo", "ゔぉ");
	kana_from_temp("ja", "じゃ");
	kana_from_temp("ju", "じゅ");
	kana_from_temp("je", "じぇ");
	kana_from_temp("jo", "じょ");
	kana_from_temp("fa", "ふぁ");
	kana_from_temp("fi", "ふぃ");
	kana_from_temp("fe", "ふぇ");
	kana_from_temp("fo", "ふぉ");
	kana_from_temp("xa", "ぁ");
	kana_from_temp("xi", "ぃ");
	kana_from_temp("xu", "ぅ");
	kana_from_temp("xe", "ぇ");
	kana_from_temp("xo", "ぉ");
	// 母音: 最後
	kana_from_temp("a", "あ");
	kana_from_temp("i", "い");
	kana_from_temp("u", "う");
	kana_from_temp("e", "え");
	kana_from_temp("o", "お");
	// 数字
	kana_from_temp("0", "０");
	kana_from_temp("1", "１");
	kana_from_temp("2", "２");
	kana_from_temp("3", "３");
	kana_from_temp("4", "４");
	kana_from_temp("5", "５");
	kana_from_temp("6", "６");
	kana_from_temp("7", "７");
	kana_from_temp("8", "８");
	kana_from_temp("9", "９");
	// 記号
	kana_from_temp(" ", "　");
	kana_from_temp("\"", "”");
	kana_from_temp("#", "＃");
	kana_from_temp("$", "＄");
	kana_from_temp("%", "％");
	kana_from_temp("&", "＆");
	kana_from_temp("'", "’");
	kana_from_temp("*", "＊");
	kana_from_temp("+", "＋");
	kana_from_temp(",", "、");
	kana_from_temp(".", "。");
	kana_from_temp(":", "：");
	kana_from_temp(";", "；");
	kana_from_temp("<", "＜");
	kana_from_temp(">", "＞");
	kana_from_temp("@", "＠");
	kana_from_temp("^", "＾");
	kana_from_temp("`", "｀");
	kana_from_temp("-", "ー");
	kana_from_temp("~", "～");
	kana_from_temp("=", "＝");
	kana_from_temp("!", "！");
	kana_from_temp("?", "？");
	kana_from_temp("/", "・");
	kana_from_temp("\\", "￥");
	kana_from_temp("|", "｜");
	kana_from_temp("_", "＿");
	kana_from_temp("(", "（");
	kana_from_temp(")", "）");
	kana_from_temp("[", "「");
	kana_from_temp("]", "」");
	kana_from_temp("{", "｛");
	kana_from_temp("}", "｝");
}

void NoteCreateState::kana_from_temp(const char* temp, const char* kana)
{
	if (_text_japanese_temp == temp)
	{
		_text_japanese += kana;
		_text_japanese_temp.clear();
	}
}

void NoteCreateState::remove_utf8(String& text)
{
	for (size_t i = text.length() - 1; i >= 0; i--)
	{
		// 最後からなめて 0x00-0x7F or 0xC2-0xF4 を探す
		const uint8_t code = static_cast<uint8_t>(text[i]);
		if (code < 0x7F || (code > 0xC2 && code < 0xF4))
		{
			// ここから末尾まで除去
			text.remove(i, text.length() - i);
			break;
		}
	}
}