#define F_CPU 4000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t digit_index;
volatile uint8_t digit1_is_negative = 0;
//volatile uint8_t digit_1;
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

void segments_set_blank(){
	segments_clear();
}

void segments_set_negative(){
	segments_clear();
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

void display_digit(char digit){
	
	if (digit == 0){
		uint8_t display_value_is_not_zero = digit_2 | digit_3 | digit_4;
		PORTC.OUT = ~PIN0_bm;
		if (digit1_is_negative && display_value_is_not_zero){
			segments_set_negative();
			} else {
			segments_set_blank();
		}
		return;
	}
	
	if (digit == 1){
		PORTC.OUT = ~PIN1_bm;
		segments_set(digit_2);
		return;
	}
	
	if (digit == 2){
		PORTC.OUT = ~PIN2_bm;
		segments_set(digit_3);
		return;
	}
	
	if (digit == 3){
		PORTC.OUT = ~PIN3_bm;
		segments_set(digit_4);
		return;
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
	// digit_1 is reserved for minus sign
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

void setup_spi(){
	PORTA.DIRCLR = PIN5_bm; // MISO
	PORTA.OUTCLR = PIN5_bm;
	PORTA.DIRSET = PIN6_bm; // SCK
}

void spi_pulse_clock(){
	PORTA.OUTSET = PIN6_bm;
	PORTA.OUTCLR = PIN6_bm;
}

uint64_t readHX() {

	// wait for the reading to finish
	while (PORTA.IN & PIN5_bm) {}

	// read the 24-bit pressure
	uint64_t result = 0;
	for (int i=0; i<24; i++){
		spi_pulse_clock(1);
		result = result << 1;
		if((PORTA.IN & PIN5_bm)) {
			result++;
		}
	}

	// take 2's compliment
	result=result ^ 0x800000;
	
	// pulse 3 times to start a 40 Hz pressure reading
	spi_pulse_clock();
	spi_pulse_clock();
	spi_pulse_clock();
	
	return result;
}

volatile uint64_t pressure_baseline = 0;

void pressure_reset(){
	led_on();
	for (int i=0; i<5; i++){
		pressure_baseline = readHX();
	}
	led_off();
}

int main(void)
{
	setup_led();
	setup_display();
	setup_timer();
	setup_button();
	setup_spi();
	sei();
	
	pressure_reset();
	
	while (1)
	{
		// TODO: Avoid flickering by not updating the display
		// if the new reading is the same as 2 readings ago.

		uint64_t pressure_raw = readHX();
		uint64_t pressure_disp = 0;
		if (pressure_raw >= pressure_baseline){
			pressure_disp = pressure_raw - pressure_baseline;
			digit1_is_negative = 0;
			} else {
			pressure_disp = pressure_baseline - pressure_raw;
			digit1_is_negative = 1;
		}
		display_number(pressure_disp / 10000);
		
		// TODO: long press changes sensitivity.
		
		if (is_button_down()){
			while (is_button_down()){
				pressure_reset();
			}
		}
	}
}

ISR(TCB0_INT_vect)
{
	display_digit(digit_index);
	digit_index++;
	if (digit_index > 3){
		digit_index = 0;
	}
	
	TCB0.INTFLAGS = TCB_OVF_bm | TCB_CAPT_bm;
}