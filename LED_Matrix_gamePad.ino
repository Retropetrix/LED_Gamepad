#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

#define pinCS 10 // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf <a href="<a href="<a href="http://arduino.cc/en/Reference/SPI" rel="nofollow">http://arduino.cc/en/Reference/SPI</a>" rel="nofollow"><a href="http://arduino.cc/en/Reference/SPI" rel="nofollow">http://arduino.cc/en/Reference/SPI</a></a>" title="<a href="<a href="http://arduino.cc/en/Reference/SPI" rel="nofollow">http://arduino.cc/en/Reference/SPI</a>" rel="nofollow"><a href="http://arduino.cc/en/Reference/SPI" rel="nofollow">http://arduino.cc/en/Reference/SPI</a></a>" rel="nofollow"><a href="<a href="http://arduino.cc/en/Reference/SPI" rel="nofollow">http://arduino.cc/en/Reference/SPI</a>" rel="nofollow"><a href="http://arduino.cc/en/Reference/SPI" rel="nofollow">http://arduino.cc/en/Reference/SPI</a></a></a> )
// Uno or Duemilanove DIN 11 (MOSI) CLK 13 (SCK)
#define BTN_COUNT 5
#define JOX 0 //axis OX on joystick, analog
#define JOY 1 //axis OY on joystick, analog
#define ZUMMER 9 //axis OY on joystick
#define CHAR_ZERO 48 //code of zero
#define BTN_POWER 7 //power for buttons from pin
#define FREEZE_MILISEC 500 //power for buttons from pin
#define PLAY_GUESS_THE_NUMBER 0
#define PLAY_MELODIES 1
#define YOU_WIN_GAME 2
#define YOU_LOSE_GAME 3
#define LAUNCH_SCREEEN 5

/////////////////////////////////////////////
/////////////////////////////////////////////
const byte COUNT_NOTES_PAROVOZ = 65; // Колличество нот
//частоты ноты
byte melodyNumber = 0;
int millisecCheckPointMusic=0;
int currentMillisecMusic; //count milisec;
byte currentNote=1;
int frequencesParovoz[COUNT_NOTES_PAROVOZ] = {
329, 329, 440, 391, 349, 293, 261, 246, 329, 293, 
261, 220, 391, 391, 261, 329, 391, 523, 493, 440, 
415, 329, 523, 493, 523, 493, 440, 329, 440, 440, 
391, 440, 391, 349, 349, 329, 391, 349, 329, 293, 
261, 246, 220, 329, 523, 493, 523, 493, 440, 329, 
440, 440, 391, 440, 391, 349, 349, 329, 391, 349, 
329, 293, 261, 246, 220 
};
//длительность нот
int durationsParovoz[COUNT_NOTES_PAROVOZ] = {
338, 1013, 169, 169, 675, 338, 338, 338, 675, 338, 
338, 675, 338, 506, 506, 338, 338, 338, 338, 338, 
1350, 338, 675, 338, 338, 338, 675, 338, 338, 338, 
338, 338, 338, 675, 338, 675, 338, 338, 338, 338, 
338, 338, 1350, 338, 675, 338, 338, 338, 675, 338, 
338, 338, 338, 338, 338, 675, 338, 675, 338, 338, 
338, 338, 338, 338, 1350
};
int durationsParovozWithPause[COUNT_NOTES_PAROVOZ] = {
417, 1250, 208, 208, 833, 417, 417, 417, 833, 417, 
417, 833, 417, 625, 625, 417, 417, 417, 417, 417, 
2917, 417, 833, 417, 417, 417, 833, 417, 417, 417, 
417, 417, 417, 833, 417, 833, 417, 417, 417, 417, 
417, 417, 2917, 417, 833, 417, 417, 417, 833, 417, 
417, 417, 417, 417, 417, 833, 417, 833, 417, 417, 
417, 417, 417, 417, 1500
};
const byte COUNT_NOTES_STARWARS = 39; // Колличество нот
int frequencesSTARWARS[COUNT_NOTES_STARWARS] = {
  392, 392, 392, 311, 466, 392, 311, 466, 392,
  587, 587, 587, 622, 466, 369, 311, 466, 392,
  784, 392, 392, 784, 739, 698, 659, 622, 659,
  415, 554, 523, 493, 466, 440, 466,
  311, 369, 311, 466, 392
};
//длительность нот
int durationsSTARWARS[COUNT_NOTES_STARWARS] = {
  350, 350, 350, 250, 100, 350, 250, 100, 700,
  350, 350, 350, 250, 100, 350, 250, 100, 700,
  350, 250, 100, 350, 250, 100, 100, 100, 450,
  150, 350, 250, 100, 100, 100, 450,
  150, 350, 250, 100, 750
};
int durationsSTARWARSWithPause[COUNT_NOTES_STARWARS] = {
  400, 400, 400, 300, 150, 400, 300, 150, 750, 
  400, 400, 400, 300, 150, 400, 300, 150, 750, 
  400, 300, 150, 400, 300, 150, 150, 150, 500, 
  200, 400, 300, 150, 150, 150, 500, 200, 400, 
  300, 150, 800
};
const byte COUNT_NOTES_JingleBells = 53; // Колличество нот
int frequencesJingleBells[COUNT_NOTES_JingleBells] =
{
  493, 493, 493, 493, 493, 493, 493, 587, 391, 440, 
  493, 523, 523, 523, 523, 523, 493, 493, 493, 493, 
  493, 440, 440, 493, 440, 587, 493, 493, 493, 493, 
  493, 493, 493, 587, 391, 440, 493, 523, 523, 523, 
  523, 523, 493, 493, 493, 493, 587, 587, 523, 440, 
  391, 587, 783  
  };
int durationsJingleBells[COUNT_NOTES_JingleBells] =
{
  208, 208, 417, 208, 208, 417, 208, 208, 312, 104, 
  833, 208, 208, 312, 104, 208, 208, 208, 104, 104, 
  208, 208, 208, 208, 417, 417, 208, 208, 417, 208, 
  208, 417, 208, 208, 312, 104, 833, 208, 208, 312, 
  104, 208, 208, 208, 104, 104, 208, 208, 208, 208, 
  208, 208, 208 
};

int durationsJingleBellsWithPause[COUNT_NOTES_JingleBells] =
{
  231, 231, 463, 231, 231, 463, 231, 231, 347, 116, 
  926, 231, 231, 347, 116, 231, 231, 231, 116, 116, 
  231, 231, 231, 231, 463, 463, 231, 231, 463, 231, 
  231, 463, 231, 231, 347, 116, 926, 231, 231, 347, 
  116, 231, 231, 231, 116, 116, 231, 231, 231, 231, 
  231, 231, 231
};

String melodyName[3];
/////////////////////////////////////////////
/////////////////////////////////////////////
byte pinBtns[BTN_COUNT]={6,5,4,3,2}; //Simple Buttons in the joystick 
byte numberOfHorizontalDisplays = 1;
byte numberOfVerticalDisplays = 4;
int currentMilisec; //count milisec;

byte menuValue; //can select functions of gampad
byte nextMenuValue;//user choose menu, its parameter then go to be menuValue
bool stateJOX=false; //neeeds to reset control action
bool stateJOY=false; //neeeds to reset control action
Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);
String tape = "";
byte spacer = 1; // Промежуток между символами (кол-во точек)
byte widthLetter = 5 + spacer; // The font widthLetter is 5 pixels 
/////////////////////////////////////////////
/////////////////////////////////////////////
byte ledOutPositionIteration; //value adds when needs to shift text
int checkPointMilisecForLEDOut; //milisec at the moment
int checkPointMilisecForFreeze; //milisec to stop all movemets for a while
byte failsCount; //when fals will 8 GAME OWER
bool moveText = true; //if true then position of text shifted
bool anyBtnState = false;
String gameName[4];
bool dificalt_1 = 2;
int delayForMoveText = 420; // In milliseconds
/////////////////////////////////////////////
/////////////////////////////////////////////
int messageLenght; //message lenght to sent

///////////////////////////////////////////
//returns true when needed number of milisecs gone
///////////////////////////////////////////
bool haveCheckPointForLEDOut(int timeDelay)
{
bool retVal = false;
currentMilisec=millis();
if (currentMilisec-checkPointMilisecForLEDOut>timeDelay)
   {
    checkPointMilisecForLEDOut=currentMilisec;
    retVal = true;
    }  
return retVal;
}
///////////////////////////////////////////
//returns true when needed number of milisecs gone
///////////////////////////////////////////
bool haveCheckPointForFREEZE(int timeDelay) 
{
bool retVal = false;
currentMilisec=millis();
if (currentMilisec-checkPointMilisecForFreeze>=timeDelay)
   {
    checkPointMilisecForFreeze=currentMilisec;
    retVal = true;
    }  
return retVal;
}
/////////////////////////////////////////////////
//change value by Joystick axies OX
/////////////////////////////////////////////////
int changeJOX()
{
  int changeOn = 0;
  int valueJOX = analogRead(JOX);
  if (valueJOX>300 && valueJOX<700)
  {
    stateJOX = false;
    }
  else   
    if (valueJOX>700)
      {
        if (!stateJOX)
        {
        changeOn = -1; 
        stateJOX=true;
        }
      }  
  else
    if (valueJOX<300)
      {
        if (!stateJOX)
        {
        changeOn = 1; 
        stateJOX=true;
        }
      }  
  return changeOn;
  }
int valueJOX()
{
  int changeOn = 0;
  int valueJOX = analogRead(JOX);
    if (valueJOX>700)
      {
        changeOn = -1; 
        stateJOX=true;
      }  
  else
    if (valueJOX<300)
      {
        changeOn = 1; 
        stateJOX=true;
      }  
  return changeOn;
  }  
int valueJOY()
{
  int changeOn = 0;
  int valueJOY = analogRead(JOY);
    if (valueJOY>700)
      {
        changeOn = 1; 
        stateJOY=true;
      }  
  else
    if (valueJOY<300)
      {
        changeOn = -1; 
        stateJOY=true;
      }  
  return changeOn;
  }  
/////////////////////////////////////////////////
//change value by Joystick axies OY
/////////////////////////////////////////////////
int changeJOY()
{
  int changeOn = 0;
  int valueJOY = analogRead(JOY);
  if (valueJOY>300 && valueJOY<700)
  {
    stateJOY = false;
    }
  else   
    if (valueJOY>700)
      {
        if (!stateJOY)
        {
        changeOn = -1; 
        stateJOY=true;
        }
      }  
  else
    if (valueJOY<300)
      {
        if (!stateJOY)
        {
        changeOn = 1; 
        stateJOY=true;
        }
      }  
  return changeOn;
  }
//////////////////////////////////////////////////////////
/* Recode russian fonts from UTF-8 to Windows-1251 */
//////////////////////////////////////////////////////////
String utf8rus(String source)
{
  int i,k;
  String target;
  unsigned char n;
  char m[2] = { '0', '\0' };

  k = source.length(); i = 0;
  while (i < k) {
    n = source[i]; i++;
    if (n >= 0xC0) {
      switch (n) {
        case 0xD0: {
          n = source[i]; i++;
          if (n == 0x81) { n = 0xA8; break; }
          if (n >= 0x90 && n <= 0xBF) n = n + 0x2F;
          break;
        }
        case 0xD1: {
          n = source[i]; i++;
          if (n == 0x91) { n = 0xB7; break; }
          if (n >= 0x80 && n <= 0x8F) n = n + 0x6F;
          break;
        }
      }
    }
    m[0] = n; target = target + String(m);
  }
return target;
}
/////////////////////////////////////////////////
//return number of first pressed button
/////////////////////////////////////////////////
int getBtnPushed(byte* btnMass, int count)
{
  int thatBtn=0;
  int btnState;
  for (int i=0;i<count; i++)
  {
    btnState = digitalRead(btnMass[i]);
   if (btnState){
      thatBtn = i+1;
     }
  }

return thatBtn;
}
////////////////////////////////////////
//game "Guess the number"
////////////////////////////////////////
void guessTheNumber()
{
  int btnPressedNumber; //first pressed button, if no one pressed then value is 0
int N = widthLetter * tape.length() + matrix.width() - 1 - spacer - 12; //widthLetter output screen
  if (ledOutPositionIteration>=N) 
  {
    ledOutPositionIteration=0;
    failsCount++;
  }
  delayForMoveText = changeJOY()*50 + delayForMoveText;
  delayForMoveText = constrain(delayForMoveText,20,420);
  btnPressedNumber = getBtnPushed(pinBtns,BTN_COUNT);
 
   matrix.fillScreen(LOW);
   drawFails(failsCount);
   //stop move if pressed right number
   if (failsCount==8)
    {
      menuValue=YOU_LOSE_GAME;
      tape = gameName[YOU_LOSE_GAME];
      matrix.fillScreen(LOW);
      failsCount=4;
      }
   if (failsCount==0)
    {
      menuValue=YOU_WIN_GAME;
      tape = gameName[YOU_WIN_GAME];
      matrix.fillScreen(LOW);
      failsCount=4;
      }
      
   if (btnPressedNumber == 0)
   {
    anyBtnState = false;
    }
   else
      {
        if (!anyBtnState)
        {
          if (btnPressedNumber==tape.toInt() )
          {
          moveText = false;
          anyBtnState=  true;
          checkPointMilisecForFreeze = millis();
          failsCount--;
          }
        else
        {
            ledOutPositionIteration = ledOutPositionIteration + widthLetter*dificalt_1;
          } 
        anyBtnState = true;  
        }
      }
      
   //*******************   
   int letterNumber = ledOutPositionIteration / widthLetter; // номер символа выводимого на матрицу 
    
    int x = (matrix.width() - 1) - ledOutPositionIteration % widthLetter;  
    int y = 0;//(matrix.height() - 8) / 2; // center the text vertically
    while ( x + widthLetter - spacer >= 0 && letterNumber >= 0 ) {
      if ( letterNumber < tape.length() ) {
        matrix.drawChar(x, y, tape[letterNumber], HIGH, LOW,1);
      }
      letterNumber--;
      x -= widthLetter;
    }
    matrix.write(); // Send bitmap to display
   
   if (haveCheckPointForLEDOut(delayForMoveText) && moveText) 
   {
    ledOutPositionIteration++;  
   }
   if (!moveText and haveCheckPointForFREEZE(FREEZE_MILISEC))
   {
    moveText = true;
    ledOutPositionIteration = 0;
    tape = random(1,5);
    } 
  
}
/////////////////////////////////////////////
//Draw Line of ERRORs
////////////////////////////
void drawFails(int count)
{
  int maxErrors = 9;
  int y1=0;
  int y2=7;
  for (int i=0;i<count;i++)
    matrix.drawLine(i,y1,i,y2,HIGH);
  for (int i=count;i<maxErrors;i++)
    matrix.drawLine(i,y1,i,y2,LOW);
  
 }
/////////////////////////////////////////////
//Draw simple text
////////////////////////////  
void drawSimpleText(String text)     
{
    int letterNumber = matrix.width() / widthLetter; // номер символа выводимого на матрицу 
    int x = matrix.width() - 1;  
    int y = 0;//(matrix.height() - 8) / 2; // center the text vertically
    matrix.fillScreen(LOW);
    while ( x + widthLetter - spacer >= 0 && letterNumber >= 0 ) {
      if ( letterNumber < text.length() ) {
        matrix.drawChar(x, y, text[letterNumber], HIGH, LOW,1);
      }
      letterNumber--;
      x -= widthLetter;
    }
    matrix.write(); // Send bitmap to display
}    
/////////////////////////////////////////////
//First you saw hello screen
////////////////////////////  
void launchScreen(int nextMenuValue)
{
 if (!digitalRead(pinBtns[0])) anyBtnState = false;
 drawSimpleText(tape);
  if (digitalRead(pinBtns[0]))
    {
      menuValue = nextMenuValue;
      nextMenuValue = PLAY_GUESS_THE_NUMBER;
      matrix.fillScreen(LOW);
      delay(300);
      anyBtnState = true;
      switch(menuValue)
      {
       case PLAY_GUESS_THE_NUMBER:
          tape = random(1,5);
          ledOutPositionIteration=0;
        break;
        case PLAY_MELODIES:
          tape = melodyName[melodyNumber];
           drawSimpleText(tape);
        break;
        }
      }
  
  }
  //////////////////////////////////
  //
  ///////////////////////////////////  
void winGameScreen()
{
  if (!digitalRead(pinBtns[0])) anyBtnState = false;
  drawSimpleText(tape);
  if (digitalRead(pinBtns[0]) && !anyBtnState)
    {
      menuValue = LAUNCH_SCREEEN;
      tape = gameName[nextMenuValue];
      matrix.fillScreen(LOW);
      delay(300);
     anyBtnState = true;
      } 
  }
  //////////////////////////////////
  //Show screen if lose game
  ///////////////////////////////////
void  loseGameScreen()
{
 if (!digitalRead(pinBtns[0])) anyBtnState = false;
 drawSimpleText(tape);
  if (digitalRead(pinBtns[0]) && !anyBtnState)
    {
      menuValue = LAUNCH_SCREEEN;
      tape = gameName[nextMenuValue];
      matrix.fillScreen(LOW);
      delay(300);
      anyBtnState=true;
      } 
  }
  //////////////////////////////////
  //delay in playing notes
  /////////////////////////////////// 
  bool myDelayNote(int durability)
{
  bool isHave = false;
  currentMillisecMusic = millis();
  if (currentMillisecMusic-millisecCheckPointMusic>=durability)
    {
      millisecCheckPointMusic = currentMillisecMusic;
      isHave = true;
      }
  return isHave;    
  }
  //////////////////////////////////
  //play music by massiv
  ///////////////////////////////////    
  void playMusicByNotes(int* frequences, int* durations, int* durationsWithPause, int countNotes)
  {
    if (currentNote>=countNotes) currentNote=1;
    if (myDelayNote(durationsWithPause[currentNote-1]))
      {
      tone(ZUMMER, frequences[currentNote], durations[currentNote]); // Включаем звук, определенной частоты
       currentNote++;
      }
 }    
  //////////////////////////////////
  //play melodies
  ///////////////////////////////////  
  void playMelodies()
  {
    int oldMelodyNumber = melodyNumber;
    if (!digitalRead(pinBtns[0])) anyBtnState = false;
    switch (melodyNumber)
      {
        case 0:
              playMusicByNotes(frequencesParovoz,durationsParovoz,durationsParovozWithPause,COUNT_NOTES_PAROVOZ);
        break;
        case 1:
              playMusicByNotes(frequencesSTARWARS,durationsSTARWARS,durationsSTARWARSWithPause,COUNT_NOTES_STARWARS);
        break;
        case 2:
              playMusicByNotes(frequencesJingleBells,durationsJingleBells,durationsJingleBellsWithPause,COUNT_NOTES_JingleBells);
        break;        
        }
    
    melodyNumber = changeJOX() + melodyNumber; 
    melodyNumber = constrain(melodyNumber,0,2);
    if (oldMelodyNumber != melodyNumber) 
        {
        tape = melodyName[melodyNumber];
        drawSimpleText(tape);
        currentNote = 1;
        }  
    oldMelodyNumber = melodyNumber;
      if (digitalRead(pinBtns[0]) && !anyBtnState)
    {
      menuValue = LAUNCH_SCREEEN;
      tape = gameName[nextMenuValue];
      matrix.fillScreen(LOW);
      delay(300);
      anyBtnState=true;
      //analogWrite(ZUMMER,LOW);
      } 
    }
void setup() {
  Serial.begin(9600);
  matrix.setIntensity(5); // Use a value between 0 and 15 for brightness
  matrix.setRotation(matrix.getRotation()+3); //1 - 90  2 - 180   3 - 270
  matrix.fillScreen(LOW);
  pinMode(BTN_POWER, OUTPUT); //Power for buttons  
  digitalWrite(BTN_POWER, HIGH);  //sets 5v
for (int i=2;i<7;i++)
  pinMode(i, INPUT); //initial button pins

ledOutPositionIteration=0; //Text starts from right side and move left
currentMilisec = 0; //time start
currentMillisecMusic = 0;
checkPointMilisecForLEDOut = 0;//time start
menuValue = LAUNCH_SCREEEN;
nextMenuValue = PLAY_GUESS_THE_NUMBER;
failsCount = 4;
melodyName[0] = utf8rus("Паровоз");
melodyName[1] = utf8rus("StarWars");
melodyName[2] = utf8rus("Jingle");
gameName[0] = utf8rus("Игра1");
gameName[1] = utf8rus("Музыка");
gameName[2] = utf8rus("Победа");
gameName[3] = utf8rus("Неуд.");
tape = gameName[nextMenuValue]; //output value when started
messageLenght = 0;
}
////////////////////////////////////
//
///////////////////////////////////
void loop() {
  int oldMenuValue = nextMenuValue;
 switch (menuValue) 
 {
 case LAUNCH_SCREEEN:
      launchScreen(nextMenuValue);
      nextMenuValue = changeJOX() + nextMenuValue;
      nextMenuValue = constrain(nextMenuValue,0,1); 
      if (oldMenuValue != nextMenuValue)
        {
        tape = gameName[nextMenuValue];
        drawSimpleText(tape);
        }      
 break;
 case PLAY_GUESS_THE_NUMBER:
      guessTheNumber();
 break; 
 case YOU_WIN_GAME:
      winGameScreen();
 break; 
 case YOU_LOSE_GAME:
      loseGameScreen();
 break;     
 case PLAY_MELODIES:
      playMelodies(); 
 break;   
 }

}

