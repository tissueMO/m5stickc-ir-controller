//#########################################################
//  リモコンの IR 送信データマスター
//#########################################################

const int codeLength = 128;

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
  { "POWER", 0xC9E408F7 },
  { "MUTE", 0xC9E4F807 },
  { "INPUTSELECT", 0xC9E47887 },
  { "TERRESTRIALDIGITAL", 0xC9E49C63 },
  { "OFFTIMER", 0xC9E46C93 },
  { "3DIGIT", 0xC9E454AB },
  { "DISPLAY", 0xC9E4D42B },
  { "SIZE", 0xC9E42CD3 },
  { "SAVEENERGY", 0xC9E47C83 },
  { "DDATA", 0xC9E422DD },
  { "1CH", 0xC9E48877 },
  { "2CH", 0xC9E448B7 },
  { "3CH", 0xC9E4C837 },
  { "4CH", 0xC9E428D7 },
  { "5CH", 0xC9E4A857 },
  { "6CH", 0xC9E46897 },
  { "7CH", 0xC9E4E817 },
  { "8CH", 0xC9E418E7 },
  { "9CH", 0xC9E49867 },
  { "10CH", 0xC9E458A7 },
  { "11CH", 0xC9E4D827 },
  { "12CH", 0xC9E438C7 },
  { "PROGRAMTABLE", 0xC9E434CB },
  { "PROGRAMINFO", 0xC9E4B44B },
  { "RECORDLIST", 0xC9E4728D },
  { "RESERVELIST", 0xC9E4F20D },
  { "VOLUMEUP", 0xC9E404FB },
  { "VOLUMEDOWN", 0xC9E4847B },
  { "CHANNELUP", 0xC9E414EB },
  { "CHANNELDOWN", 0xC9E4946B },
  { "MENU", 0xC9E4B847 },
  { "RETURN", 0xC9E4EC13 },
  { "RECORD", 0xC9E48A75 },
  { "RECORDSTOP", 0xC9E46A95 },
  { "UP", 0xC9E444BB },
  { "DOWN", 0xC9E4C43B },
  { "LEFT", 0xC9E424DB },
  { "RIGHT", 0xC9E4A45B },
  { "DECIDE", 0xC9E4649B },
  { "BLUE", 0xC9E402FD },
  { "RED", 0xC9E4827D },
  { "GREEN", 0xC9E442BD },
  { "YELLOW", 0xC9E4C23D },
  { "PLAYPAUSE", 0xC9E4D22D },
  { "STOP", 0xC9E4CA35},
  { "FASTREWIND", 0xC9E42AD5 },
  { "FASTFORWARD", 0xC9E432CD },
  { "AUDIOSELECT", 0xC9E44CB3 },
  { "SUBTITLES", 0xC9E4CC33 },
  { "PREVIOUS", 0xC9E4B24D },
  { "NEXT", 0xC9E4AA55 }
};
