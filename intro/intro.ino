/*
 * IntroOnOled
 * Программа для интро канала RootTool
 * Работаем по простому алгоритму
 * SW1 -> SW2 -> SW3 -> SW4 -> SW5
 * Создал: RootTool
 * https://www.youtube.com/@roottool0
 *
 * Видео
 * https://www.youtube.com/
 */

#include <GyverOLED.h> //Подключаем библиотеку дисплея
#include <RTPinBoard.h> //Подключаем библиотеку клавиатуры

GyverOLED<SSD1306_128x64, OLED_BUFFER> oled; //Подключаем дисплей
RTPinBoard board(0); //Подключаем клавиатуру на контакте А0

void setup(){
  oled.init(); //Инициализируем и очищаем дисплей
  oled.clear();
}

bool img1 = true; //Перемменная для цикла первого кадра
bool img2 = false; //Перемменная для цикла второго кадра

void loop() {
  if(img1){
    //KEYBOARD
    //Если нажали на какую нибудь клавишу, то выводим звездочку
    //Код:
    //SW1 - 1
    //SW2 - 2
    //SW3 - 3
    //SW4 - 4
    oled.setScale(4);
    board.update();
    if(board.isRelease(1)) {
      oled.setCursorXY(12, 18);
      oled.print("*");
    }
    if(board.isRelease(2)) {
      oled.setCursorXY(40, 18);
      oled.print("*");
    }
    if(board.isRelease(3)) {
      oled.setCursorXY(68, 18);
      oled.print("*");
    }
    if(board.isRelease(4)) {
      oled.setCursorXY(96, 18);
      oled.print("*");
    }
    
    //DISPLAY
    //Рисуем рамку для звездочек и рамку вокруг экрана
    oled.roundRect(0, 0, 127, 63, OLED_STROKE);
    for(int i = 0; i < 4; i++){
      oled.roundRect(i * 28 + 10, 19, 
                     i * 28 + 33, 44, OLED_STROKE);
    }
    
    oled.update();
    //OUT
    //Если нажали SW5, то делаем красивую анимацию очистки
    //и выходим из цикла
    if(board.isRelease(5)){
      delay(500);
      for(int i = 0; i < 18; i++){
        oled.rect(0, 0, i*8, 64, OLED_CLEAR);
        oled.update((i-1) * 8, 0, i*8, 64);
        delay(5);
      }
      oled.clear();
      oled.update(126, 0, 129, 64);
      img1 = false;
      img2 = true;
    }
  }
  //Кадр второй
  if(img2){
    //Пишем Root Tool
    oled.setScale(2);
    oled.setCursorXY(11, 16);
    oled.print("Root Tool");
    oled.roundRect(0, 0, 127, 63, OLED_STROKE); //Не забываем про рамку вокруг экрана.
    oled.update();
    //И через секунду пишем Приятного Просмотра
    delay(1000);
    oled.setScale(1);
    oled.setCursorXY(8, 34);
    oled.print("Приятного Просмотра");
    oled.update();
  }
  //На этом все :)
}
