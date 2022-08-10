#include <LiquidCrystal.h>
LiquidCrystal lcd(16, 17, 4, 21, 13, 12, 14, 27, 26, 25, 33);
void setup() {
  lcd.begin(12 ,4);
  lcd.print("ola mundo!");
}

void loop() {
  // put your main code here, to run repeatedly:

}
