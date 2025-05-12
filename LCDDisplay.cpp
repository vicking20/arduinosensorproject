#include "LCDDisplay.h"

LCDDisplay::LCDDisplay()
  : lcd(0x27, 16, 2) {}

void LCDDisplay::begin() {
  lcd.begin();
  lcd.backlight();
}

void LCDDisplay::writeText(char* message){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(message);
}

void LCDDisplay::displayTempHumidity(float temp, float humidity) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print(" %");
}
