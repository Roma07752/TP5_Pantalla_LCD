#include "pantallalcd.h"

int main(void) {
    lcd_init();
    lcd_setCursor(0 , 0);
    lcd_print("Trabajo Practico");
    lcd_setCursor(0, 1);
    lcd_print("Pantalla LCD");
    while(1) {
        lcd_scrollDisplayLeft();
    }
}