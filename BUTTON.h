#ifndef __BUTTON_H
#define __BUTTON_H

void EXTINT1VectoredIRQ (void)__irq;
void EXTINT2VectoredIRQ (void)__irq;

void Button_initial(void);

#endif