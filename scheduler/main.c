#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdint.h>
#include "scheduler.h"

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

void init_gpio() {
	DDRA = 0xFF;
	PORTA = 0x00;
}

int migacz(void *data) {
	uint8_t pin = *((uint8_t*)data);  // Uwielbiam takie krzaczki w C ;)
	PORTA ^= _BV(pin);

	return EXIT_SUCCESS;
	//return EXIT_FAILURE;  // Pozaswieca i umrze taski
}


static uint8_t reszta_migaczy[4] = { 4, 5, 6, 7 };
int dodaj_reszte_migaczy() {
	add_task(4, 1000, migacz, &reszta_migaczy[0]);
	add_task(5, 2000, migacz, &reszta_migaczy[1]);
	add_task(6, 3000, migacz, &reszta_migaczy[2]);
	add_task(7, 5000, migacz, &reszta_migaczy[3]);

	return EXIT_SUCCESS;
}

int main(int argc, char * argv[]) {
	init_scheduler();
	init_timer_irq();

	init_gpio();

	uint8_t migacze[4] = { 0, 1, 2, 3 };  // Tak, wiem, ze daloby sie to przekazac w wartosci wskaznika, ale badzmy ludzmi i nie przeginajmy z rzutowaniem :)

	add_task(0, 1000, migacz, &migacze[0]);
	add_task(1, 2000, migacz, &migacze[1]);
	add_task(2, 3000, migacz, &migacze[2]);
	add_task(3, 5000, migacz, &migacze[3]);

	add_disposable(4, 1000, dodaj_reszte_migaczy, NULL);

	execute();

	return 0;
}
