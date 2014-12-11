#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "7seg.h"

#define NO_VALUE 0xFF

volatile unsigned int sweep_counter = 0; // Liczy kiedy odpalic sweep_task

ISR(TIMER0_COMP_vect) {
	sweep_counter += 1;

	if(sweep_counter >= 5) {
		seg_timer_sweep();
		sweep_counter = 0;
	}
}

void init_timer_irq() {
	TCCR0 |= _BV(WGM01);
	TIMSK |= _BV(OCF0);

	OCR0 = 125;

	TCCR0 |= _BV(CS00) | _BV(CS01);

	sei();
}

void init_keyboard() {
	DDRD = 0x0F;
	PORTD = 0x00;
}

uint8_t getCol(uint8_t rowValue) {
	if((~rowValue & 0xF0) & _BV(4))
		return 0;
	else if((~rowValue & 0xF0) & _BV(5))
		return 1;
	else if((~rowValue & 0xF0) & _BV(6))
		return 2;
	else if((~rowValue & 0xF0) & _BV(7))
		return 3;
	else
		return NO_VALUE;
}


int main(int argc, char * argv[]) {
	init_timer_irq();
	init_7seg();
	init_keyboard();

	for(;;){
		uint8_t was_value = 0;

		for(uint8_t row=0; row<4; row++){
			PORTD = ~_BV(row);
			_delay_us(5);
			uint8_t col = getCol(PIND);

			if(col != NO_VALUE){
				displayValue = (uint32_t)(4*row + col + 1);
				was_value = 1;
			}
		}
		if(was_value==0)
			displayValue = 0;
	}

	return 0;
}
