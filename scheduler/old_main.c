#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdlib.h>

#define THREAD_CNT 4

// co 1ms
// {fptr, interval, data_ptr, toGo, ready}

struct thread_t {
	void (*function_ptr)(void *data_ptr);
	unsigned int interval;
	void *data_ptr;

	unsigned int left;
	unsigned int ready;
};

static struct thread_t threads[THREAD_CNT];

ISR(TIMER0_COMP_vect){
	for(unsigned int i=0; i<THREAD_CNT; ++i){
		threads[i].left--;

		if(threads[i].left == 0){
			threads[i].left = threads[i].interval;
			threads[i].ready++;
		}
	}
}

void register_thread(unsigned int id, void (*function_ptr)(void *data_ptr), void *data_ptr, unsigned int interval){
	threads[id].function_ptr = function_ptr;
	threads[id].interval = interval;
	threads[id].data_ptr = data_ptr;

	threads[id].left = interval;
	threads[id].ready = 0;
}

void migaj0(void *data){
	PORTA ^= _BV(0);
}
void migaj1(void *data){
	PORTA ^= _BV(1);
}
void migaj2(void *data){
	PORTA ^= _BV(2);
}
void migaj3(void *data){
	PORTA ^= _BV(3);
}

int main(void){
	DDRA = 0xFF;
	PORTA = 0x00;

	TCCR0 |= _BV(WGM01);
	TIMSK |= _BV(OCF0);

	OCR0 = 125;

	register_thread(0, migaj0, NULL, 1000);
	register_thread(1, migaj1, NULL, 2000);
	register_thread(2, migaj2, NULL, 3000);
	register_thread(3, migaj3, NULL, 5000);


	TCCR0 |= _BV(CS00) | _BV(CS01);

	sei();


    while(1){
    	for(unsigned int i=0; i<THREAD_CNT; ++i){
    		if(threads[i].ready){
    			threads[i].ready--;
    			threads[i].function_ptr(threads[i].data_ptr);
    			break;
    		}
    	}
    }

    return 0;
}
