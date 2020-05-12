//#########################################################
//  リモコンの IR 送信データマスター
//#########################################################

const int codeLength = 8;

/*
  リモコンコードデータ形式
*/
struct REMOTE {
  String name;
  uint64_t command;
};

/*
  リモコンコード定義
*/
REMOTE remote[codeLength] = {
  { "FULL", 0xDE41280C },
  { "OFF", 0x8840540C },
  { "LIGHTER", 0x5692E662 },
  { "DARKER", 0x5387F862 },
  { "NIGHTLIGHTER", 0xE2724B84 },
  { "NIGHTDARKER", 0xF4FEEE5E },
  { "SAVE30", 0x8791B76C },
  { "SAVE50", 0x90CC35DE }
};
