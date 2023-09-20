#define F_CPU 4000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t next_digit;
volatile uint8_t digit_1;
volatile uint8_t digit_2;
volatile uint8_t digit_3;
volatile uint8_t digit_4;

void setup_led(){
	PORTF.DIRSET = PIN4_bm;
	PORTF.OUTSET = PIN4_bm;
}

void led_on() {
	PORTF.OUTCLR = PIN4_bm;
}

void led_off() {
	PORTF.OUTSET = PIN4_bm;
}

void setup_display(){
	PORTC.DIRSET = PIN0_bm;
	PORTC.DIRSET = PIN1_bm;
	PORTC.DIRSET = PIN2_bm;
	PORTC.DIRSET = PIN3_bm;
	
	PORTD.DIRSET = PIN1_bm;
	PORTD.DIRSET = PIN2_bm;
	PORTD.DIRSET = PIN3_bm;
	PORTD.DIRSET = PIN4_bm;
	PORTD.DIRSET = PIN5_bm;
	PORTF.DIRSET = PIN2_bm;
	PORTF.DIRSET = PIN3_bm;
}

void segment_set_A() { PORTD.OUTSET = PIN1_bm; }
void segment_set_B() { PORTD.OUTSET = PIN2_bm; }
void segment_set_C() { PORTD.OUTSET = PIN3_bm; }
void segment_set_D() { PORTD.OUTSET = PIN4_bm; }
void segment_set_E() { PORTD.OUTSET = PIN5_bm; }
void segment_set_F() { PORTF.OUTSET = PIN2_bm; }
void segment_set_G() { PORTF.OUTSET = PIN3_bm; }

void segments_clear() {
	PORTD.OUTCLR = PIN1_bm;
	PORTD.OUTCLR = PIN2_bm;
	PORTD.OUTCLR = PIN3_bm;
	PORTD.OUTCLR = PIN4_bm;
	PORTD.OUTCLR = PIN5_bm;
	PORTF.OUTCLR = PIN2_bm;
	PORTF.OUTCLR = PIN3_bm;
}

void segments_set_0(){
	segments_clear();
	segment_set_A();
	segment_set_B();
	segment_set_C();
	segment_set_D();
	segment_set_E();
	segment_set_F();
}

void segments_set_1(){
	segments_clear();
	segment_set_B();
	segment_set_C();
}

void segments_set_2(){
	segments_clear();
	segment_set_A();
	segment_set_B();
	segment_set_D();
	segment_set_E();
	segment_set_G();
}

void segments_set_3(){
	segments_clear();
	segment_set_A();
	segment_set_B();
	segment_set_C();
	segment_set_D();
	segment_set_G();
}

void segments_set_4(){
	segments_clear();
	segment_set_B();
	segment_set_C();
	segment_set_F();
	segment_set_G();
}

void segments_set_5(){
	segments_clear();
	segment_set_A();
	segment_set_C();
	segment_set_D();
	segment_set_F();
	segment_set_G();
}

void segments_set_6(){
	segments_clear();
	segment_set_A();
	segment_set_C();
	segment_set_D();
	segment_set_E();
	segment_set_F();
	segment_set_G();
}

void segments_set_7(){
	segments_clear();
	segment_set_A();
	segment_set_B();
	segment_set_C();
}

void segments_set_8(){
	segments_clear();
	segment_set_A();
	segment_set_B();
	segment_set_C();
	segment_set_D();
	segment_set_E();
	segment_set_F();
	segment_set_G();
}

void segments_set_9(){
	segments_clear();
	segment_set_A();
	segment_set_B();
	segment_set_C();
	segment_set_D();
	segment_set_F();
	segment_set_G();
}

void segments_set(char value){
	if (value == 0){
		segments_set_0();
		} else if (value == 1) {
		segments_set_1();
		} else if (value == 2) {
		segments_set_2();
		} else if (value == 3) {
		segments_set_3();
		} else if (value == 4) {
		segments_set_4();
		} else if (value == 5) {
		segments_set_5();
		} else if (value == 6) {
		segments_set_6();
		} else if (value == 7) {
		segments_set_7();
		} else if (value == 8) {
		segments_set_8();
		} else if (value == 9) {
		segments_set_9();
	}
}

void digit_set(char digit){
	if (digit == 0){
		PORTC.OUT = ~PIN0_bm;
		segments_set(digit_1);
		} else if (digit == 1){
		PORTC.OUT = ~PIN1_bm;
		segments_set(digit_2);
		} else if (digit == 2){
		PORTC.OUT = ~PIN2_bm;
		segments_set(digit_3);
		} else if (digit == 3){
		PORTC.OUT = ~PIN3_bm;
		segments_set(digit_4);
	}
}

void setup_timer(){
	TCB0.INTCTRL |= TCB_CAPT_bm;
	TCB0.CCMP = 8000; // 500 Hz @ 4 MHz clock
	TCB0.CTRLA |= TCB_ENABLE_bm;
}

void display_number(uint16_t number){
	digit_4 = number % 10;
	number /= 10;
	digit_3 = number % 10;
	number /= 10;
	digit_2 = number % 10;
	number /= 10;
	digit_1 = number % 10;
}

void setup_button(){
	PORTF.DIRCLR = PIN5_bm;
	PORTF.PIN5CTRL = PORT_PULLUPEN_bm;
}

uint8_t is_button_down(){
	if (PORTF.IN & PIN5_bm){
		return 0;
		} else {
		return 1;
	}
}

uint8_t is_button_up(){
	if (PORTF.IN & PIN5_bm){
		return 1;
		} else {
		return 0;
	}
}

int main(void)
{
	setup_led();
	setup_display();
	setup_timer();
	setup_button();
	sei();
	
	uint16_t count = 0;
	while (1)
	{
		_delay_ms(100);
		display_number(count++);
		
		if (is_button_down()){
			count = 0;
			display_number(0);
			led_on();
			while (is_button_down());
			led_off();
		}
	}
}

ISR(TCB0_INT_vect)
{
	digit_set(next_digit);
	next_digit++;
	if (next_digit > 3){
		next_digit = 0;
	}
	
	TCB0.INTFLAGS = TCB_OVF_bm | TCB_CAPT_bm;
}