#define MAX_NUMBER_OF_TASKS 8
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

void init_scheduler(void);

void schedule(void);
void execute(void);

void add_task(unsigned int priority, unsigned int period, int (*function_ptr)(void *data_ptr), void *params);
void add_disposable(unsigned int priority, unsigned int delay, int (*function_ptr)(void *data_ptr), void *params);

void disable_task(unsigned int priority);
