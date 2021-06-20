///
/// サーボモータを単純に駆動してみる
///
/****************************************************
 * マクロ部
 ****************************************************/
#include <Servo.h>

/****************************************************
 * グローバル変数/配列 宣言部
 ****************************************************/
int ServoPin = 9;

Servo myservo;


/****************************************************
 * Arduino 要求関数部
 ****************************************************/
void setup() {
	myservo.attach(ServoPin, 600, 2300);
  myservo.write(0);
}

void loop() {
/*  delay(1000);
  myservo.write(0);
  delay(1000);
  myservo.write(180);*/
}

/****************************************************
 * 独自関数部
 ****************************************************/