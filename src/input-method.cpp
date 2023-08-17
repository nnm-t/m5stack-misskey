#include "input-method.hpp"

String InputMethod::request(String& text)
{
	String url = api_url + urlEncode(text) + ",";
	Serial.println(url);

	// APIへGET
	String response = _https.http_get(url);
	Serial.println(response);

	// デシリアライズ
	deserializeJson(_json_response, response);
	// 候補数を取得
	_result_number = _json_response[0][1].size();
	// 最初の候補を返す
	return _json_response[0][1][0];
}

String InputMethod::next()
{
	// 次候補
	if (_json_response.isNull())
	{
		return String();
	}

	if (++_index > _result_number - 1)
	{
		_index = 0;
	}

	return _json_response[0][1][_index];
}