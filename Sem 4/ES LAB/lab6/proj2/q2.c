#include <LPC17xx.h>

unsigned i, j;
unsigned long LED = 0x00000000;
unsigned long INV;


int main(void) {
    SystemInit();
    SystemCoreClockUpdate();

    LPC_PINCON->PINSEL0 &= 0xFF0000FF;
    LPC_GPIO0->FIODIR |= 0x00000FF0;

    while (1) {
        LED = 0x00000000;
        for (i = 1; i <= 255; i++) {
            LPC_GPIO0->FIOSET = LED;
            INV = (LED) ^ (0x00000FF0); 
            LPC_GPIO0->FIOCLR = INV;
            for (j = 0; j < 50000; j++);
            LED = LED >> 4;
            LED = LED + 1;
            LED = LED << 4;
        }
    }
}

