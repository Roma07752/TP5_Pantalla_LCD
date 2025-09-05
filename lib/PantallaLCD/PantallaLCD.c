#include "pantallalcd.h"

char backlight = 1;

void lcd_enablePulse(void) {
    GPIOB->BSRR = (1 << EN);
    delay_us(1);
    GPIOB->BRR = (1 << EN);
    delay_ms(50);
}

void lcd_send4bits(char data) {
    GPIOB->BRR = (1<<D4)|(1<<D5)|(1<<D6)|(1<<D7);

    if(data & 0x01) GPIOB->BSRR = (1<<D4);
    if(data & 0x02) GPIOB->BSRR = (1<<D5);
    if(data & 0x04) GPIOB->BSRR = (1<<D6);
    if(data & 0x08) GPIOB->BSRR = (1<<D7);

}

void lcd_send(char value, int mode) {
    if(mode){ 
        GPIOB->BSRR = (1<<RS); 
    }else{
        GPIOB->BRR  = (1<<RS);
    } 
    lcd_send4bits(value >> 4);
    lcd_send4bits(value & 0x0F);
    delay_us(50);
}

void lcd_sendCnd(char cnd){
    lcd_send(cnd, 0);
}

void lcd_sendChar(char c){
    lcd_send(c, 1);
}

void lcd_init() {
    delay_ms(40);
    lcd_send4bits(0x03);
    delay_ms(5);
    lcd_send4bits(0x03);
    delay_us(150);
    lcd_send4bits(0x03);
    lcd_send4bits(0x02); 

    lcd_send(0x28, 0); 
    lcd_send(0x0C, 0); 
    lcd_send(0x06, 0); 
    lcd_clear();
}

void lcd_clear() {
    lcd_send(0x01, 0);
    delay_ms(2);
}

void lcd_setCursor(int col, int row) {
    int filas[4] = {0x00, 0x40, 0x14, 0x54};
    int posicion = filas[row] + col;
    lcd_sendCnd(posicion);
}

void lcd_print(char *str) {
    while(*str) {
        lcd_sendChar(*str++);
    }
}

void lcd_scrollDisplayLeft() {
    lcd_send(0x18, 0);
}

void lcd_scrollDisplayRight() {
    lcd_send(0x1C, 0);
}

void lcd_backlight() {
    backlight = 1;  
}

void lcd_noBacklight() {
    backlight = 0;

}

void lcd_createChar(char num, char datos[8]) {
    lcd_sendCnd(num*8+0x40);
    for(int i=0;i<8;i++){
        lcd_sendChar(datos[i]);
    }
    
}
