// with info from https://lastminuteengineers.com/i2c-lcd-arduino-tutorial/
// To figure i2c address, I used this: https://www.usinainfo.com.br/blog/como-descobrir-o-endereco-i2c-arduino/
// My 16x2 LCD display is at address 0x3D

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3D,16,2);  // set the LCD address to 0x3D for a 16 chars and 2 line display

#define LED D0
#define BUTTON D1
#define RESET D2

long whenPressed= 0;
bool previousState= false;
bool lastState= false;
long lcdTimer= 0;
int counter= 0;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(RESET, INPUT_PULLUP);
	Serial.begin(115200);
	lcd.init();
  lcd.clear();         
  lcd.backlight(); // Make sure backlight is on

}

void loop() {

  if(!digitalRead(BUTTON) && previousState == false){ // increments counter if the button is pressed and 
  //300ms have passed since the last press
    previousState= true;
    whenPressed= millis();
    counter++;
    if(lastState == true){ // alternates an LED ON and OFF for every button press
      digitalWrite(LED, LOW);
      lastState= false;
    }else{
      digitalWrite(LED, HIGH);
      lastState= true;
    }
     
  }else if(!digitalRead(RESET)){ // if reset button was pressed, zero counter
    counter= 0;
  }
	if((millis() - whenPressed >= 300) && digitalRead(BUTTON)){ // allows a new button press only after 300ms of the previous one
  // there is also a protection to avoid incrementing the counter if the button is kept pressed
    previousState= false;

  }

  if(millis() - lcdTimer > 500){ // update display every 500ms
    lcdTimer= millis();
    lcd.clear();
    lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
    lcd.print(counter);
    lcd.setCursor(4, 0); // Set cursor to character 4 on line 0
    lcd.print(" <- contador");
    lcd.setCursor(0, 1); // Set cursor to character 1 on line 1
    lcd.print("FritzenLab blog");

    
  }

}
