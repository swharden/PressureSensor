#ifndef LEDMANAGER_H_
#define LEDMANAGER_H_

class LedManager{
	public:

	LedManager(){
		setup();
	}
	
	void setup(){
		PORTF.DIRSET = PIN4_bm;
		PORTF.OUTSET = PIN4_bm;
	}
	
	void status_on(){
		PORTF.OUTCLR = PIN4_bm;
	}

	void status_off(){
		PORTF.OUTSET = PIN4_bm;
	}

	void status_toggle(){
		PORTF.OUTTGL = PIN4_bm;
	}
};

#endif