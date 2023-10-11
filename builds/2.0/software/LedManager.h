#ifndef LEDMANAGER_H_
#define LEDMANAGER_H_

class LedManager{
	public:

	LedManager(){
	}
	
	void setup(){
		PORTA.DIRSET = PIN2_bm;
		PORTA.OUTSET = PIN2_bm;
		
		PORTA.DIRSET = PIN3_bm;
		PORTA.OUTSET = PIN3_bm;
		
		PORTA.DIRSET = PIN4_bm;
		PORTA.OUTSET = PIN4_bm;
	}

	void sample_on(){
		PORTA.OUTCLR = PIN4_bm;
	}

	void sample_off(){
		PORTA.OUTSET = PIN4_bm;
	}

	void mode_on(){
		PORTA.OUTCLR = PIN3_bm;
	}

	void mode_off(){
		PORTA.OUTSET = PIN3_bm;
	}

	void signal_on(){
		PORTA.OUTCLR = PIN2_bm;
	}

	void signal_off(){
		PORTA.OUTSET = PIN2_bm;
	}
};

#endif