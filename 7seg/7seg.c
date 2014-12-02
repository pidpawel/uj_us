#include <stdint.h>
#include <avr/io.h>
#include "7seg.h"

#define ENABLE_COL(x) PORTC &= ~_BV(x)
#define DISABLE_COL(x) PORTC |= _BV(x)

static volatile uint32_t counter = 0; // Trzyma ilosc setek ms
static volatile uint8_t current_col = 0;  // Numerki inne niz w makrodefinicjach! (-1)

static uint8_t char_table[10] = {
	~0b00111111,
	~0b00000110,
	~0b01011011,
	~0b01001111,
	~0b01100110,
	~0b01101101,
	~0b01111101,
	~0b00000111,
	~0b01111111,
	~0b01101111,
};

void init_7seg() {
	DDRA = 0xFF;
	PORTA = 0xFF;

	DDRC = 0xFF;
	PORTC = 0xFF;
}

// Pokazuje literke, dot - flaga czy zaswiecic kropke
inline static void show_char(unsigned int c, uint8_t dot) {
	PORTA = char_table[c];

	if(dot)
		PORTA &= ~_BV(7);
	else
		PORTA |= _BV(7);
}

inline static void disable_all_cols() {
	PORTC |= _BV(COL1_PIN) | _BV(COL2_PIN) | _BV(COL3_PIN) | _BV(COL4_PIN);
}

inline static void enable_col(uint8_t col) {
	switch(col) {
		case 0:
			ENABLE_COL(COL1_PIN);
			break;
		case 1:
			ENABLE_COL(COL2_PIN);
			break;
		case 2:
			ENABLE_COL(COL3_PIN);
			break;
		case 3:
			ENABLE_COL(COL4_PIN);
			break;
	}
}

void seg_timer_sweep() {
	current_col += 1;

	if(current_col > 3)
		current_col = 0;

	disable_all_cols();  // Wylaczam przed rozpoczeciem zmian na pinach

	uint32_t i = counter;

	for(uint8_t j=3-current_col; j>0; j--){
		i = i/10;
	}

	if(counter < 10000) {  // 10000 odliczen czyli 1000s, czyli w szczegolnosci do 999.9s
		i = i % 10;

		switch(current_col) {
			case 0:
			case 1:
			case 3:
				show_char((unsigned int) i, 0);
				break;
			case 2:
				show_char((unsigned int) i, 1);
				break;
		}
	} else {
		i = (i / 10) % 10;

		show_char((unsigned int) i, 0);
	}

	enable_col(current_col);  // Wlaczam dopiero gdy mam "wyrenderowane" wyjscie dla danego znaku
}

void seg_timer_increment() {
	counter++;

	if(counter >= 100000L)  // Wiecej sie nie zmiesci na wyswietlaczu
		counter = 0;
}
