#include <Wire.h>
//#include <LCD.h>
//#include <LiquidCrystal_I2C.h>
//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // Addr, En, Rw, Rs, d4, d5, d6, d7, backlighpin, polarity
 
//#define trigPin 12
//#define echoPin 13

int speaker = 6;    //porta do arduino
long vel = 20000;
 
void setup() {
    pinMode(speaker, OUTPUT);
    delay(2000);
    Serial.begin (9600);
  //  pinMode(trigPin, OUTPUT);
   // pinMode(echoPin, INPUT);
    
    
    //lcd.begin(16,2);
    //lcd.backlight();

    
    
}
 
int melod[] = {758, 758, 758, 955, 758, 638, 1276, 955, 1276, 1517, 1136, 1012, 1073, 1136, 1276, 758, 638, 568, 716, 638, 758, 955, 851, 1012, 955};
int ritmo[] = {6, 12, 12, 6, 12, 24, 24, 18, 18, 18, 12, 12, 6, 12, 8, 8, 8, 12, 6, 12, 12, 6, 6, 6, 12};

int i=0;
void loop() {
    int duration, distance;
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration/2) / 29.1;
    
    vel = (20000 - distance * 1000);
    
    if (distance >= 20){
      lcd.setCursor(0, 0);
      lcd.print("Out Of Range");
      lcd.setCursor(0, 1);
      lcd.print("Hover to play");
      
    }
    else {
      lcd.setCursor(0, 0);
      lcd.print("Mario theme song");
      lcd.setCursor(0, 1);
      lcd.print("");
      
      if (i > 25l) {
        delay(250);
        i = 0;
      }else{
        
        int tom = melod[i];
        int tempo = ritmo[i];
 
        long tvalue = tempo * vel;
 
        tocar(tom, tvalue);
 
        delayMicroseconds(1000); //pausa entre notas!
        i++; 
    }  
  }
}
 
void tocar(int tom, long tempo_value) {
     long tempo_gasto = 0;
     while (tempo_gasto < tempo_value) {
        digitalWrite(speaker, HIGH);
        delayMicroseconds(tom / 2);
 
        digitalWrite(speaker, LOW);
        delayMicroseconds(tom/2);
 
        tempo_gasto += tom;
    }
}
