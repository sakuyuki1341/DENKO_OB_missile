#include <SPI.h>
#include <SD.h>

const int chipSelect = 10;
const String countFile_name = "count.txt";
File logFile;

/***********************************************
  SDカードの初期設定
  返り値は成否(true or false)
  成功時：
  ・SDカードが認識されている
  失敗時：
  ・SDカードが認識されていない
 ***********************************************/
bool init_SDcard(void) {
  Serial.println("\nInitializing SD card ...");
  pinMode(10, OUTPUT);
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not to exist.");
    return false;
  }
  Serial.println("SDcard initialized.");
  return true;
}


/***********************************************
  SD内のcount.txtを読み取り、ファイルを更新
  返り値は成否(true or false)
  成功時：
  ・count.txtを読みとる
  ・読取り内容を引数countに入れる
  ・count.txtを削除して新しい内容のものを作成
  失敗時：
  ・count.txtを読み取ろうとするができない
  ・引数countは0になる
  ・count.txtはそのまま維持
 ***********************************************/
bool init_countFile(int* count) {
  // 読み込みバグを回避するため1秒ディレイ
  for (int i = 0; i < 1000; i++) {
    delay(1);
  }
  *count = 0;
  File countFile;
  if (SD.exists(countFile_name)) { // countファイルの存在確認
    /*存在する場合*/
    countFile = SD.open(countFile_name, FILE_READ);

    for (int i = 0; i < 3; i++) { // 読取り＋countへ代入
      char tmp = countFile.read();
      if (tmp != -1) {
        switch (i) {
          case 0:
            *count += 100*atoi(&tmp);
            break;
          case 1:
            *count += 10*atoi(&tmp);
            break;
          case 2:
            *count += atoi(&tmp);
            break;
          default:
            Serial.println("メッセージは出ないはずだよ"); // don't do anything
        }
      }
    }

    // 読取りが正常に行われたかどうかの判断
    if (*count != 0) {
      Serial.println("Compleat reading countFile.");
    } else {
      Serial.println("Can't read countFile.");
      return false;
    }

  } else {
    /*countファイルが存在しない場合*/
    Serial.println("countFile doesn't existing");
    return false;
  }

  /* ----- 以下は読取りが成功したときのみ実行される ----- */
  // 読み込みバグを回避するため1秒ディレイ
  for (int i = 0; i < 1000; i++) {
    delay(1);
  }
  Serial.print("Count: ");
  Serial.println(*count);
  countFile.close();

  // 旧count.txtを削除して新しいものを作成
  SD.remove(countFile_name);
  countFile = SD.open(countFile_name, FILE_WRITE);
  // 書き込むデータを整形
  String printStr;
  if (*count < 9) {
    printStr = String("00"+String(*count + 1));
  } else if (*count < 99) {
    printStr = String("0"+String(*count + 1));
  } else {
    printStr = String(*count + 1);
  }
  countFile.print(printStr);
  countFile.close();
  return true;
}

/***********************************************
  logFileを開く
 ***********************************************/
void init_logFile(int count) {
  // 読み込みバグを回避するため1秒ディレイ
  for (int i = 0; i < 1000; i++) {
    delay(1);
  }
  // ファイルの名前の決定
  String logFile_name;
  if (count != 0) {
    logFile_name = String("Log" + String(count) + ".CSV");
  } else {
    logFile_name = String("Log_default.CSV");
  }
  logFile = SD.open(logFile_name, FILE_WRITE);
  Serial.println("Complete initializing logFile");
}

/***********************************************
  logFileにデータを書き込む
  data[11]:
    data[0] :TimeStamp(h)
    data[1] :TimeStamp(m)
    data[2] :TimeStamp(s)
    data[3] :TimeStamp(s小数点)
    data[4] :加速度1
    data[5] :加速度2
    data[6] :加速度3
    data[7] :サーボ1
    data[8] :サーボ2
    data[9] :サーボ3
    data[10]:サーボ4
 ***********************************************/
void write_log(int data[11]) {
  // 出力データを整形
  String dataStr = String(String(data[0])+":"+String(data[1])+":"+String(data[2])+"."+String(data[3])+","+
    String(data[4])+","+String(data[5])+","+String(data[6])+","+String(data[7])+","+String(data[8])+","+
    String(data[9])+","+String(data[10]));
  logFile.println(dataStr);
  // 基本的に処理軽減のため下の行はコメントアウト
//  Serial.println(String("Write to SDcard \n"+dataStr));
}

/***********************************************
  setup
 ***********************************************/
void setup() {
  /* ----- シリアルモニタを開いてから処理開始 ----- */
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial port to connect.
  }

  int count;
  init_SDcard();
  init_countFile(&count);
  init_logFile(count);

  Serial.print("Start time: ");
  long startTime = millis();
  Serial.println(startTime);

  for (int i = 0; i < 1000; i++) {
    int test[11] = {i,i,i,i,i,i,i,i,i,i,i};
    write_log(test);
  }
  logFile.close();

  long endTime = millis();
  Serial.println(endTime);
  Serial.println("Successed!!");
}

/***********************************************
  loop
 ***********************************************/
void loop() {
}
