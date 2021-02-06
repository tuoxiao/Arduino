/*
 * MC猜数字 （Ver. 1.0）
 * 
 * 本程序用于太极创客制作的《零基础入门学用Arduino教程》中
 * MC猜数字小制作。通过学习和搭建这个小装置，我们希望您能够
 * 学会以下内容：
 * 
 *  - LED数码管的原理和使用
 *  - if...else if的概念和应用
 *  - while循环的概念和应用
 *  - switch case控制语句
 *  - random函数的使用
 *  - 建立和使用自定义函数（三种形式：无参数无返回值，有参数无返回值，有参数有返回值）
 *  - 通过串口监视器观察调试程序运行状况
 *  
 *  电路连接：
 *  有关本制作的详细电路连接资料，请参阅太极创客网站的《零基础入门学用Arduino教程》相关网页。
 *  
 *  
 *  太极创客网站地址：
 *  www.taichi-maker.com
 *  
 *  如您对我们有任何建议或意见，请发邮件至：
 *  taichimaker@163.com
 *  
 *  同时您也可以通过我们的微信公众号以及微博获得更多太极创客的最新信息。
 *  
 *  This example code is in the public domain.
 *  
 *  2017-04-23
 *
 *  注：
 *  目前科学技术尚无法实现意念控制。
 *  科技可以改变世界,但也有心怀不轨的人会利用科技制作
 *  我们不宜察觉的装置。而这些装置会被用于赌博或诈骗。
 *  我们一定要远离赌博，相信科学。：）
*/


int thisResult;  //存储按键按下以后显示在数码管的数字。
int nextResult;  //存储作弊数字，也就是下一次按键按下后即将显示的数字。

void setup() {
  pinMode(2, INPUT_PULLUP); //2号引脚上连接有按键开关，将2号引脚设置为输入上拉模式
  int pinNumber = 3;        //设置3-9号引脚为输出模式
  while(pinNumber <= 9){
    pinMode(pinNumber, OUTPUT);
    pinNumber = pinNumber + 1;
  }
  randomSeed(analogRead(A0)); //为了每一次复位或断电后产生不同顺序的随机数字
}

// the loop function runs over and over again forever
void loop() {
  if (!digitalRead(2)){      //读取2号引脚电平状态
    getRandomNumber(0,10);   //用户按下按键后，开始新一次猜数字游戏
  }
  displayNumber(thisResult); //将猜数字游戏"结果"显示在数码管中
}

/*
用户在每一次按下按键后，随机产生的数字将存储于nextResult变量中。
而实际显示在数码管上的数字是thisResult变量。
当thisResult即将显示在数码管前，程序会将下一次显示的数字通过
图形暗示的形式显示在数码管上。具体程序如何显示暗示图形，
请参阅displayCheat()函数说明。
*/
void getRandomNumber(int minNumber, int maxNumber){
  thisResult = nextResult; 
  int i; 
  while(i < 15){
    i = i + 1;
    nextResult = random(0, 10);
    displayRandom();         //显示随机图案，混淆注意力
    delay(50 + i * 10);      //让随机图案显示时间由快到慢，增加混淆
    displayClear();
  }
  displayCheat(nextResult);  //显示作弊图案，用户可通过此函数所显示的图案
                             //获知下次按键后将要出现在LED数码管上的数字。  
                             //此图案是在用户每次按下按键后显示新的数字
                             //前的最后一次图案显示
  delay(500);
  displayClear();
}

//根据参数数值在LED数码管上显示数字
void displayNumber(int ledNumber){     
  switch(ledNumber){
    case 1:  //显示1
      digitalWrite(4, HIGH);
      digitalWrite(7, HIGH); 
      break;   
    case 2:  //显示2
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH); 
      digitalWrite(5, HIGH); 
      digitalWrite(8, HIGH); 
      digitalWrite(9, HIGH); 
      break;   
    case 3:   //显示3
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH); 
      digitalWrite(5, HIGH); 
      digitalWrite(7, HIGH); 
      digitalWrite(8, HIGH); 
      break;   
    case 4:  //显示4
      digitalWrite(4, HIGH); 
      digitalWrite(5, HIGH); 
      digitalWrite(6, HIGH); 
      digitalWrite(7, HIGH); 
      break;  
    case 5:  //显示5
      digitalWrite(3, HIGH);
      digitalWrite(5, HIGH); 
      digitalWrite(6, HIGH); 
      digitalWrite(7, HIGH); 
      digitalWrite(8, HIGH); 
      break;
    case 6:  //显示6
      digitalWrite(3, HIGH);
      digitalWrite(5, HIGH); 
      digitalWrite(6, HIGH); 
      digitalWrite(7, HIGH); 
      digitalWrite(8, HIGH); 
      digitalWrite(9, HIGH); 
      break;    
    case 7:  //显示7
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH); 
      digitalWrite(7, HIGH);  
      break;
    case 8:  //显示8
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(5, HIGH); 
      digitalWrite(6, HIGH); 
      digitalWrite(7, HIGH); 
      digitalWrite(8, HIGH); 
      digitalWrite(9, HIGH); 
      break;
    case 9:  //显示9
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(5, HIGH); 
      digitalWrite(6, HIGH); 
      digitalWrite(7, HIGH); 
      digitalWrite(8, HIGH); 
      break;
    case 0:  //显示默认
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(6, HIGH); 
      digitalWrite(7, HIGH); 
      digitalWrite(8, HIGH); 
      digitalWrite(9, HIGH); 
      break;
    default:
        digitalWrite(4, HIGH); 
        digitalWrite(5, HIGH); 
        digitalWrite(7, HIGH); 
        digitalWrite(8, HIGH);  
        digitalWrite(9, HIGH);   
    }
}

//清理显示内容
void displayClear(){
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW); 
  digitalWrite(6, LOW); 
  digitalWrite(7, LOW); 
  digitalWrite(8, LOW); 
  digitalWrite(9, LOW); 
}

//显示随机图案以混淆注意力
//使作弊图案显示时不易察觉。
void displayRandom(){
  int randomPin = random(3,9);
  digitalWrite(randomPin, HIGH);  
}

//显示作弊图案。
void displayCheat(int number){
  switch(number){
    case 1:  // 显示数字1作弊图案
      digitalWrite(3, HIGH);
      break;   
    case 2:  // 显示数字2作弊图案
      digitalWrite(6, HIGH); 
      break;   
    case 3:  // 显示数字3作弊图案
      digitalWrite(4, HIGH); ;
      break;   
    case 4:  // 显示数字4作弊图案
      digitalWrite(5, HIGH); 
      break;  
    case 5:  // 显示数字5作弊图案
      digitalWrite(9, HIGH); 
      break;
    case 6:  // 显示数字6作弊图案
      digitalWrite(7, HIGH);   
      break;    
    case 7: // 显示数字7作弊图案
      digitalWrite(8, HIGH);
      break;
    case 8: // 显示数字8作弊图案
      digitalWrite(6, HIGH);
      digitalWrite(4, HIGH);
      break;
    case 9: // 显示数字9作弊图案
      digitalWrite(9, HIGH);
      digitalWrite(7, HIGH);
      break;
    case 0: // 显示数字0作弊图案
      digitalWrite(3, HIGH);
      digitalWrite(8, HIGH); 
      break;
    }
}
