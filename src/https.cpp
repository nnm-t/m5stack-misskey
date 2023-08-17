#include "https.hpp"

String HTTPS::post(String& url, String& content_type, String& content)
{
    HTTPClient http_client;
    String response;

    // 証明書セットして送信
    if (!http_client.begin(url, _settings.get_root_ca().c_str()))
    {
        M5.Lcd.println("HTTPS Connection failed");
        return response;
    }

    // POST組み立てる
    http_client.addHeader("Content-Type", content_type);
    const int32_t status_code = http_client.POST(content);

    switch (status_code)
    {
        case 200:
            response = http_client.getString();
            break;
        default:
            M5.Lcd.println(http_client.errorToString(status_code));
            break;
    }

    http_client.end();
    return response;
}

String HTTPS::http_get(String& url)
{
    HTTPClient http_client;
    String response;

    if (!http_client.begin(url))
    {
        M5.Lcd.println("HTTPS Connection failed");
        return response;
    }

    const int32_t status_code = http_client.GET();

    switch (status_code)
    {
        case 200:
            response = http_client.getString();
            break;
        default:
            M5.Lcd.println(http_client.errorToString(status_code));
            break;
    }

    http_client.end();
    return response;
}