#ifndef __BUTTONMANAGER_H__
#define __BUTTONMANAGER_H__

class ButtonManager
{
	public:
	
	ButtonManager(){
	};
	
	void setup(){
		PORTF.DIRCLR = PIN4_bm;
		PORTF.PIN4CTRL = PORT_PULLUPEN_bm;
		
		PORTF.DIRCLR = PIN5_bm;
		PORTF.PIN5CTRL = PORT_PULLUPEN_bm;
	}
	
	uint8_t is_down(){
		if (PORTF.IN & PIN5_bm){
			return 0;
			} else {
			return 1;
		}
	}
	
	uint8_t is_up(){
		return !is_down();
	}

	void wait_until_down(){
		while (is_up()){}
	}

	void wait_until_up(){
		while (is_down()){}
	}
};

#endif
