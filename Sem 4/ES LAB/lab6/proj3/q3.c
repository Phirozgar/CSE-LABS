#include <LPC17xx.h>
//Declaration outside everything

unsigned int counter = 1, i, switchState=1, flag = 1;

int main(void){
	SystemInit();
	SystemCoreClockUpdate();
	LPC_PINCON->PINSEL0 &= 0xFF0000FF; //For LED
	LPC_GPIO0->FIODIR |= 0x00000FF0;
	
	LPC_PINCON->PINSEL4 &= 0xFCFFFFFF; //For Key
	LPC_GPIO2->FIODIR &= ~(1<<12);//0x00001000;
	
	//switchState = (LPC_GPIO2->FIOPIN >> 7) & 1
	
	while(1){
		switchState = (LPC_GPIO2->FIOPIN >> 12) & 1;
		if (switchState == 0){
			flag = !flag;
			if (flag) counter = 0;
			else counter = 255;
		}
		if (flag)	
			counter++;
		else counter--;
		
		LPC_GPIO0->FIOCLR = 0x00000FF0;
		LPC_GPIO0->FIOSET = (counter<<4);
		for (i=0; i<100000; i++); //delay
		
		if (counter>0xFF || counter==0) 
			break;
	}
}