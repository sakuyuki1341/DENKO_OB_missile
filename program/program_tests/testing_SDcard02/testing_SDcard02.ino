#include <SPI.h>
#include <SD.h>

const int chipSelect = 10;
const String CountFile_Name = "Count.txt";

void setup() {
  /* ----- シリアルモニタを開いてから処理開始 ----- */   
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  /* ----- Initialisation of SD card ----- */
  Serial.println("\nInitializing SD card ...");
  pinMode(10, OUTPUT);
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not to exist");
    return; //don't do anything
  }
  Serial.println("SDcard initialized.");

  /* ----- Count.txtを用意するためだけに使用 ----- */
  if (SD.exists(CountFile_Name)) {
    SD.remove(CountFile_Name);
  }
  File CountFile = SD.open(CountFile_Name, FILE_WRITE);
  CountFile.print("123");
  CountFile.close();

  /* ----- Countファイルから最新の番号を取得 ----- */
  int count = 0;  // 最新の番号
  if (SD.exists(CountFile_Name)) { // Countファイルの存在確認
    /*存在する場合の処理*/ 
    File CountFile = SD.open(CountFile_Name, FILE_READ);
    for (int i = 0; i < 3; i++) {
      char tmp = CountFile.read();
      Serial.println(tmp);
      if (tmp != -1) {
        switch (i){
          case 0:
            count += 100*atoi(&tmp);
            break;
          case 1:
            count += 10*atoi(&tmp);
            break;
          case 2:
            count += atoi(&tmp);
            break;
          default:
            Serial.println("メッセージはでないはずだよ");
        }
      }
    }
    //読取りが正常に行えなかった場合の処理 
    if (count == 0) {
      Serial.println("Can't read CountFile");
    }
  } else {
    /*Countファイルが存在しない場合*/  
    Serial.println("CountFile doesn't existing");
  }

  Serial.print("Count: ");
  Serial.println(count);

  CountFile.close();
}

void loop(void) {
}
