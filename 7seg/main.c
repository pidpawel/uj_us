#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "7seg.h"

volatile unsigned int inc_counter = 0; // Liczy kiedy odpalic increment_task
volatile unsigned int sweep_counter = 0; // Liczy kiedy odpalic sweep_task

ISR(TIMER0_COMP_vect) {
	inc_counter += 1;
	sweep_counter += 1;

	if(inc_counter >= 100) {
		seg_timer_increment();
		inc_counter = 0;
	}

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


int main(int argc, char * argv[]) {
	init_timer_irq();

	init_7seg();

	for(;;){}

	return 0;
}
