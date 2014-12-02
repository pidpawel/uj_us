#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "scheduler.h"
#include "7seg.h"

ISR(TIMER0_COMP_vect) {
	schedule();
}

void init_timer_irq() {
	TCCR0 |= _BV(WGM01);
	TIMSK |= _BV(OCF0);

	OCR0 = 125;

	TCCR0 |= _BV(CS00) | _BV(CS01);

	sei();
}

int sweep_task(void *args) {
	seg_timer_sweep();

	return EXIT_SUCCESS;
}

int increment_task(void *args) {
	seg_timer_increment();

	return EXIT_SUCCESS;
}


int main(int argc, char * argv[]) {
	init_scheduler();
	init_timer_irq();

	init_7seg();

	add_task(3, 5, sweep_task, NULL);
	add_task(5, 100, increment_task, NULL);

	execute();

	return 0;
}
