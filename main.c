#include <LPC21xx.H>
#include <stdio.h>
#include "UART.h"
#include "TIMER.h"
#include "BUTTON.h"

void main (void)
{
	Timer_initial();
	UART0_initial();
	Button_initial();
	printTime();

	while(1);
}
