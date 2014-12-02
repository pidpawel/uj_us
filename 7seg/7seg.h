/*
PORTA
01234567 - abcdefg<dp>
PORTC
7654 - d1, d2, d3, d4
*/

#define COL1_PIN 7
#define COL2_PIN 6
#define COL3_PIN 5
#define COL4_PIN 4

void init_7seg(void);
void seg_timer_sweep(void);
void seg_timer_increment(void);
