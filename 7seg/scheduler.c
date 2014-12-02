#include <stdlib.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "scheduler.h"

#define TASK_DISPOSABLE 1
#define TASK_PERIODIC 0

struct thread_t {
	unsigned int enabled;
	unsigned int is_disposable;

	int (*function_ptr)(void *data_ptr);
	void *params_ptr;

	unsigned int interval;

	unsigned int left;
	unsigned int ready;
};

static struct thread_t threads[MAX_NUMBER_OF_TASKS];

void init_scheduler() {
	cli();

	for(unsigned int i=0; i<MAX_NUMBER_OF_TASKS; ++i) {
		threads[i].enabled = 0;

		threads[i].is_disposable = 0;

		// Just to be sure...
		threads[i].function_ptr = NULL;
		threads[i].params_ptr = NULL;

		threads[i].interval = 0;
		threads[i].left = 0;
		threads[i].ready = 0;
	}

	sei();
}

inline static void add_event(unsigned int priority, unsigned int is_disposable, unsigned int interval, int (*function_ptr)(void *data_ptr), void *params_ptr) {
	if(priority >= MAX_NUMBER_OF_TASKS)
		return;

	cli();

	threads[priority].enabled = 1;

	threads[priority].is_disposable = is_disposable;

	threads[priority].interval = interval;

	threads[priority].function_ptr = function_ptr;
	threads[priority].params_ptr = params_ptr;

	threads[priority].left = interval;
	threads[priority].ready = 0;

	sei();
}

void add_task(unsigned int priority, unsigned int interval, int (*function_ptr)(void *data_ptr), void *params_ptr) {
	add_event(priority, TASK_PERIODIC, interval, function_ptr, params_ptr);
}

void add_disposable(unsigned int priority, unsigned int delay, int (*function_ptr)(void *data_ptr), void *params_ptr) {
	add_event(priority, TASK_DISPOSABLE, delay, function_ptr, params_ptr);
}

void disable_task(unsigned int priority) {
	cli();

	threads[priority].enabled = 0;

	sei();
}

void schedule() {
	for(unsigned int i=0; i<MAX_NUMBER_OF_TASKS; ++i) {
		if(!threads[i].enabled)
			continue;

		threads[i].left--;

		if(threads[i].left == 0) {
			threads[i].left = threads[i].interval;
			threads[i].ready++;
		}
	}
}

void execute() {
	while(1){
		cli();

		for(unsigned int i=0; i<MAX_NUMBER_OF_TASKS; ++i) {
			if(!threads[i].enabled)
				continue;

			if(threads[i].ready){
				threads[i].ready--;

				if(threads[i].is_disposable)
					threads[i].enabled = 0;

				sei();

				int result = threads[i].function_ptr(threads[i].params_ptr);
				if(result != EXIT_SUCCESS)
					disable_task(i);

				break;
			}
		}

		sei();
	}
}
