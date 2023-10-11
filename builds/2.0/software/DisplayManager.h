#ifndef DISPLAYMANAGER_H_
#define DISPLAYMANAGER_H_

class DisplayManager{
	public:
	DisplayManager(){
	}
	
	void setup(){
		
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
		
		segments_clear();
	}

	void show(int16_t number){
		if (number < 0){
			digit1_is_negative = 1;
			number = -number;
			} else {
			digit1_is_negative = 0;
		}
		
		digit_4 = number % 10;
		number /= 10;
		digit_3 = number % 10;
		number /= 10;
		digit_2 = number % 10;
	}
	
	void multiplex_tick(){
		display_digit(digit_index);
		digit_index++;
		if (digit_index > 3){
			digit_index = 0;
		}
	}
	
	private:
	
	volatile uint8_t digit_index;
	volatile uint8_t digit1_is_negative;
	//volatile uint8_t digit_1;
	volatile uint8_t digit_2;
	volatile uint8_t digit_3;
	volatile uint8_t digit_4;
	
	/*
	// standard orientation
	void segment_set_A() { PORTD.OUTSET = PIN1_bm; }
	void segment_set_B() { PORTD.OUTSET = PIN2_bm; }
	void segment_set_C() { PORTD.OUTSET = PIN3_bm; }
	void segment_set_D() { PORTD.OUTSET = PIN4_bm; }
	void segment_set_E() { PORTD.OUTSET = PIN5_bm; }
	void segment_set_F() { PORTF.OUTSET = PIN2_bm; }
	void segment_set_G() { PORTF.OUTSET = PIN3_bm; }
	*/
	
	// vertically inverted orientation
	void segment_set_D() { PORTD.OUTSET = PIN1_bm; }
	void segment_set_E() { PORTD.OUTSET = PIN2_bm; }
	void segment_set_F() { PORTD.OUTSET = PIN3_bm; }
	void segment_set_A() { PORTD.OUTSET = PIN4_bm; }
	void segment_set_B() { PORTD.OUTSET = PIN5_bm; }
	void segment_set_C() { PORTF.OUTSET = PIN2_bm; }
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

/*
	// standard orientation
	void set_digit_1() { PORTC.OUT = ~PIN0_bm; }
	void set_digit_2() { PORTC.OUT = ~PIN1_bm; }
	void set_digit_3() { PORTC.OUT = ~PIN2_bm; }
	void set_digit_4() { PORTC.OUT = ~PIN3_bm; }
*/

	// vertically inverted orientation
	void set_digit_4() { PORTC.OUT = ~PIN0_bm; }
	void set_digit_3() { PORTC.OUT = ~PIN1_bm; }
	void set_digit_2() { PORTC.OUT = ~PIN2_bm; }
	void set_digit_1() { PORTC.OUT = ~PIN3_bm; }

	void display_digit(char digit){
		
		if (digit == 0){
			uint8_t display_value_is_not_zero = digit_2 | digit_3 | digit_4;
			set_digit_1();
			if (digit1_is_negative && display_value_is_not_zero){
				segments_set_negative();
				} else {
				segments_set_blank();
			}
			return;
		}
		
		if (digit == 1){
			set_digit_2();
			segments_set(digit_2);
			return;
		}
		
		if (digit == 2){
			set_digit_3();
			segments_set(digit_3);
			return;
		}
		
		if (digit == 3){
			set_digit_4();
			segments_set(digit_4);
			return;
		}
	}
};

#endif