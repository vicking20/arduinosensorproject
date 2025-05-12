#ifndef LCDDISPLAY_H
#define LCDDISPLAY_H

#include <LiquidCrystal_I2C.h>

class LCDDisplay {
public:
    LCDDisplay();
    void begin();
    void writeText(char* message);
    void displayTempHumidity(float temp, float humidity);
private:
    LiquidCrystal_I2C lcd;
};

#endif
