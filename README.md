# Misskey on M5Stack

M5Stackから[Misskey](https://misskey-hub.net/) APIを実行してノートの閲覧や投稿が行えます。

## 必要なもの

- M5Stack
  - Fire または Core2
    - PSRAMを使用するため
  - Faces Bottom
    - Faces II Bottomでも可
    - 生産終了品
  - Faces Keyboard Panel
    - 生産終了品

## 開発環境

PlatformIO

### 使用ライブラリ

- [M5Unified](https://github.com/m5stack/M5Unified): MIT License
  - [M5GFX](https://github.com/m5stack/M5GFX): MIT License
- [ArduinoJson](https://github.com/bblanchon/ArduinoJson): MIT License
- [UrlEncoder](https://github.com/plageoj/urlencode): MIT License

## SDカード

以下のファイルをルートディレクトリ上に配置します。

- 設定ファイル `misskey_settings.json`
- ルートCA証明書 (チェーン)
- アイコン (Windows Bitmap)
  - タイトルに表示するアイコン (24x24)
  - `public.bmp`: パブリック (24x24)
  - `home.bmp`: ホーム (24x24)
  - `followers.bmp`: フォロワー (24x24)
  - `federate.bmp`: 連合 (24x24)
  - `de_federate.bmp`: 連合なし (24x24)

### `misskey_settings.json`

JSON形式で次の内容を記載します。

```json
{
  "ssid": "Wi-Fi SSID",
  "password": "Wi-Fi パスワード",
  "host": "接続先のMisskeyサーバーのURL (最後のスラッシュは付けない)",
  "root_ca": "ルートCA証明書 (チェーン) のファイルパス",
  "api_token": "MisskeyのAPIトークン",
  "title": "タイトルに表示する文字列",
  "icon": "タイトルに表示するアイコン (24x24 Windows Bitmap) のファイルパス"
}
```
