# M5StickC専用 遠隔リモコン

## Summary

M5StickC の IR トランスミッターを利用したリモコンアプリです。  
実際の操作はスマホから行うことを想定しています。  


## Description

### アーキテクチャー概略

#### フロント部 [frontend]

- [HTTP/GET] スマホ (ブラウザ) => Web サーバー
    - 画面表示
- [HTTP/GET] スマホ (ブラウザ) => M5StickC
    - IR トランスミッターからの赤外線送信指示


### 赤外線送信部 [sender]

- [IR] M5StickC => テレビ等
    - IR トランスミッターから赤外線を送信


## Dependency

#### フロント部 [frontend]

- Node.js 12+
- Yarn
- Nodes.js パッケージ
    - Webpack
    - Babel
    - Chart.js
    - Sass
    - EJS
    - ESLint
    - その他については `/front/package.json` を参照


### 赤外線送信部 [sender]

- Arduino IDE
- M5StickC
- M5Stack用 赤外線送受信ユニット (Grove端子で接続)
    - 対応するリモコンの赤外線情報を取得するのに必要


## Setup

本リポジトリーから Clone してから実際に動かすまでの手順を示します。  

### フロント部 [frontend]

- コマンドライン上で `/frontend` に移動した状態で以下のコマンドで Node.js で使用する依存パッケージをインストールします。
    - `$ yarn`
- `/frontend/src/js/settings.example.js` をもとに環境依存する値 (APIサーバーのURL、末尾に / を含まないもの) を設定した `/frontend/src/js/settings.js` を作成します。
- 次節で取得する赤外線コード情報をもとに、対応するボタンの名前やレイアウト情報を `/frontend/src/json/buttons.json` に書き込みます。
- 以下のコマンドで公開ファイル群をビルドします。
    - `$ yarn run dev`
        - 本番モードでビルドするには `$ yarn run build` とします。
        - 本番モードでの出力には、map ファイルが含まれず、CSS および JavaScript ファイルが Minify されたものになります。
- `/frontend/public/` 以下に作られたファイルを、任意の Web サーバーの公開ディレクトリーに配置します。
    - 前掲アーキテクチャー概略のうち、 Web サーバー に相当します。


### 赤外線送信部 [sender]

#### 赤外線データの取り込み

- M5StickC に 赤外線送受信ユニット (IR ユニット) を接続します。
- M5StickC を USB 接続します。
- Arduino IDE のボードマネージャから M5StickC をインストールします。
- Arduino IDE から任意の受信プログラムを書き込みます。
    - Arduino のスケッチ例 `IRremoteESP8266/IRecvDumpV2` がお勧めです。
        - ライブラリ IRremoteESP8266 のインストールが必要です。
        - `const uint16_t kRecvPin = 14;` の行は `const uint16_t kRecvPin = 33;` に置き換える必要があります。
- Arduino IDE のシリアルモニターから M5StickC が起動していることを確認します。
- IR ユニットにリモコンの赤外線を照射し、コード情報を取得します。
    - Arduino IDE のシリアルモニターにコードの中身が表示されるので、これをどこかに控えておいて下さい。


#### 赤外線を発信するサーバーの構築

- M5StickC を USB 接続します。
    - IR ユニット は外して構いません。
- (再掲) Arduino IDE のボードマネージャから M5StickC をインストールします。
- Arduino IDE から `/sender/sender.ino` を開きます。
- `/sender/settings.example.h` をもとに適宜設定値を含めた `/sender/settings.h` を作成し、環境依存する値のマクロを定義します。
- 前節で取得した赤外線コード情報をもとに `/sender/remote.h` を更新します。
    - ボタンの名前は フロント部 [frontend] で定義した名前と一致するようにして下さい。
- コンパイル & M5StickC への書き込みを行います。


## Usage

### 赤外線送信部 [sender]

(Setup/赤外線送信部 [sender] での工程が完了している前提とします)

- M5StickC の電源を ON にします。
    - 必要に応じて USB 電源供給した状態にします。
- LCD ディスプレイに文字列が表示されることを確認します。
    - 赤外線送信部 [sender] のサーバーに送信指示があった際に 0.5 秒間だけ送信するボタン内容が表示されます。
- リモコン操作の対象となる機器のすぐ側に M5StickC を配置します。


### フロント部 [front]

(Usage/赤外線送信部 [sender]、Setup/フロント部 [front] での工程が完了している前提とします)

- ビルドしたフロント用コンテンツを配置している Web サーバーに疎通できるクライアント環境のブラウザーから、フロント用コンテンツの index.html にアクセスします。
    - リモコン画面が表示されます。
    - 非最新のブラウザーや Internet Explorer 等では正しく動作しない可能性があります。
- 任意のボタンを押下し、リモコン操作の対象となる機器を正常に操作できることを確認します。


## Reference

- [M5StickCで赤外線リモコンを使う - Lang-ship](https://lang-ship.com/blog/work/m5stickc-ir/)
- [crankyoldgit/IRremoteESP8266](https://github.com/crankyoldgit/IRremoteESP8266)
- [ICOOON MONO](https://icooon-mono.com/)
    - このリポジトリーで使用している favicon の著作権は上記サイトの TopeconHeroes 様に帰属します。
    

## License

[MIT](LICENSE.md)


## Author

[tissueMO](https://github.com/tissueMO)
