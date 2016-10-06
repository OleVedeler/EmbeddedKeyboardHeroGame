#define cs   10
#define dc   9
#define rst  8 

#include <Adafruit_GFX.h>    
#include <Adafruit_ST7735.h> 
#include <SPI.h>

Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, rst);
uint32_t time;
uint32_t gameTime;


//skjerm
const byte radius = 14;
byte NumberOfNotes = 0;
const byte MAX_NOTES_IN_LANE = 3;
short NotePos[MAX_NOTES_IN_LANE][2];
byte noteSpeed = 4;
byte laneSize = 32;

//Knapper
byte buttonPin[3];

byte buttonState[3];
const byte buttonCount = 3;


//Score
int score = 0;

void setup(){
  //knapper  
  for(byte i = 0; i < buttonCount; i++){
    buttonPin[i] = 2 + i;  
    pinMode(buttonPin[i], INPUT);
  }
  
  //skjerm
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK);
  drawLane();
  randomSeed(analogRead(0));
}

void loop(){
    //score
    printScore();
  
    //knapper
    for(byte i = 0; i < 3; i++){
      buttonState[i] = digitalRead(buttonPin[i]);
    }
    
    //Skjerm
    drawPlayerSpace();
    drawNotes();
     
    gameTime = millis() - gameTime;
    time += gameTime;
    
    if(time > 30000){
      addNote(random(3));
      time = 0;
    }
}

void drawPlayerSpace(){
   tft.drawFastHLine( 0 , tft.height() - radius * 2, tft.height(), ST7735_RED); 
}

void drawLane(){
    for (byte x = 0; x < 4; x++){
      // Todo: Finn en måte å regne ut nummeret 42
        tft.drawFastVLine(x * laneSize, 0, tft.height(), ST7735_RED);
    }
}

void addNote(byte lane){
  if(NumberOfNotes < MAX_NOTES_IN_LANE){
    NotePos[NumberOfNotes][0] = lane;
    NotePos[NumberOfNotes][1] = -radius;
    NumberOfNotes++;
  }
}

void drawNotes(){
   for(byte i = 0; i < NumberOfNotes; i++){
      runNote(i); 
   }
}

void runNote(byte note){
      NotePos[note][1] += noteSpeed; 
      byte lane = NotePos[note][0];
      
      // todo: Skift ut med test om bruker har trykket.
      if(NotePos[note][1] > tft.height() - radius && buttonState[lane] == HIGH){
        
        tft.fillCircle(((radius) + laneSize * lane) + 2, NotePos[note][1] - noteSpeed, radius, ST7735_BLACK);
        // tegn nye note
        tft.fillCircle(((radius) + laneSize * lane) + 2, NotePos[note][1], radius, ST7735_BLUE);
      }else{        
        // fjern forrige note
        tft.drawCircle(((radius) + laneSize * lane) + 2, NotePos[note][1] - noteSpeed, radius, ST7735_BLACK);
        // tegn nye note
        tft.drawCircle(((radius) + laneSize * lane) + 2, NotePos[note][1], radius, ST7735_BLUE);     
      }
      
      if(NotePos[note][1] > tft.height() + radius 
        || (NotePos[note][1] > tft.height() - radius 
            && buttonState[lane] == HIGH)){
         removeNote(note);
         score++;   
      }
      
}

void removeNote(byte note){
   for(byte i = note; i < NumberOfNotes ; i++){
      NotePos[i][0] = NotePos[i + 1][0];
      NotePos[i][1] = NotePos[i + 1][1];
   } 
   NumberOfNotes--;
}

void printScore() {
  tft.setTextWrap(true);
  tft.setTextColor(ST7735_WHITE);
  tft.setCursor(100, 20);
  tft.print(millis() / 1000);
}

