#include "BUTTON.h"
#include "TIMER.h"
#include "UART.h"
#include <LPC21xx.H>
#include <stdio.h>

void EXTINT1VectoredIRQ (void)__irq;
void EXTINT2VectoredIRQ (void)__irq;

void Button_initial(void);

unsigned int start_flag;

void Button_initial(void)
{
	start_flag = 0;

	IODIR1  = 0x01000000; 						         	// Set GPIO-1[24] = Output
    IOSET1  = 0x01000000;                                  	// Set GPIO-1[24] Output Pin(OFF LED)  
	
	PINSEL0 |= 0x80000000;			//Enable the EXTINT2 interrupt
	PINSEL0 |= 0x20000000;			//Enable the EXTINT1 interrupt
	
	VICVectCntl1 	= 0x00000020 | 0x0000000F;  		//select a priority slot for a given interrupt
	VICVectAddr1 	= (unsigned)EXTINT1VectoredIRQ;		//pass the address of the IRQ into the VIC slot
	VICVectCntl2 	= 0x00000020 | 0x00000010;  		//select a priority slot for a given interrupt
	VICVectAddr2 	= (unsigned)EXTINT2VectoredIRQ;		//pass the address of the IRQ into the VIC slot
	
	VICIntEnable 	|= 0x00010000;						//enable EXTINT2 interrupt
	VICIntEnable 	|= 0x00008000;						//enable EXTINT1 interrupt
}

void EXTINT1VectoredIRQ (void)__irq
{
	if (start_flag == 0)
	{
		start_flag = 1;
		T0TCR 		= 0x00000001;			//enable timer
		
	}

	EXTINT  = 0x00000002;					//Clear the peripheral interrupt flag
	VICVectAddr 	= 0x00000000;			//Dummy write to signal end of interrupt
}
void EXTINT2VectoredIRQ (void)__irq
{
	if (start_flag == 1)
	{
		start_flag = 0;
		T0TCR 		= 0x00000000;			//disable timer
		IOSET1 = 0x01000000;                               		// Set Output GPIO1[24] Pin (OFF LED)	  
	}

	EXTINT  = 0x00000004;					//Clear the peripheral interrupt flag
	VICVectAddr 	= 0x00000000;			//Dummy write to signal end of interrupt
}
