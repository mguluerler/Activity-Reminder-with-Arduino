#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
int input[20];
int timeforblink = 0;


//blink[1dk, 30sn, 20sn, 10sn, 5sn, 2sn]
int blinkDegree(int degree){
  if (degree == 1 && timeforblink > 60){
    lcd.noBacklight();
    timeforblink = 0;
  }
  else if (degree == 2 && timeforblink > 30){
    lcd.noBacklight();
    timeforblink = 0;
  }
  else if (degree == 3 && timeforblink > 15){
    lcd.noBacklight();
    timeforblink = 0;
  }
  else if (degree == 4 && timeforblink > 10){
    lcd.noBacklight();
    timeforblink = 0;
  }
  else if (degree == 5 && timeforblink > 5){
    lcd.noBacklight();
    timeforblink = 0;
  }
  else if (degree == 6 && timeforblink > 2){
    lcd.noBacklight();
    timeforblink = 0;
  }
  else if (timeforblink > 0){
    lcd.backlight();
  }
}

int activities(int activity_number, int line){
  if (activity_number == 1){
    lcd.setCursor(0,line);
    lcd.print("ACT 1");
    lcd.setCursor(11,line);
    lcd.print("16:00");}
  else if (activity_number == 2){
    lcd.setCursor(0,line);
    lcd.print("ACT 2");
    lcd.setCursor(11,line);
    lcd.print("10:00");}
  else if (activity_number == 3){
    lcd.setCursor(0,line);
    lcd.print("ACT 3");
    lcd.setCursor(11,line);
    lcd.print("14:00");}
  else if (activity_number == 4){
    lcd.setCursor(0,line);
    lcd.print("ACT 4");
    lcd.setCursor(11,line);
    lcd.print("22:00");}
  else if (activity_number == 5){
    lcd.setCursor(0,line);
    lcd.print("ACT 5");
    lcd.setCursor(11,line);
    lcd.print("17:00");}
  else if (activity_number == 6){
    lcd.setCursor(0,line);
    lcd.print("ACT 6");
    lcd.setCursor(11,line);
    lcd.print("15:00");}
  else if (activity_number == 7){
    lcd.setCursor(0,line);
    lcd.print("ACT 7");
    lcd.setCursor(11,line);
    lcd.print("08:00");}
  else if (activity_number == 8){
    lcd.setCursor(0,line);
    lcd.print("ACT 8");
    lcd.setCursor(11,line);
    lcd.print("08:00");}
  else{
    lcd.setCursor(0,line);
    lcd.print("No Activities!");
  }
}

void setup() {
  Serial.begin(9600);
  lcd.begin();
}

void loop() {
  if (Serial.available()) {
    delay(100);    
    int i = 0;
    while (Serial.available() > 0) {
      input[i] = Serial.read()-48; // ascii numbers start with 48 (ascii48 == 0)
      i += 1;
    }
    lcd.clear();
    if (i==1){ activities( 0, 0 ); }
    else if (i>2){ activities( input[1], 0 ); activities( input[2], 1 ); }
    else { activities( input[1], 0 ); }
    timeforblink += 1;
  }
  blinkDegree( input[0] );
}
