#ifndef __PRESSURESENSOR_H__
#define __PRESSURESENSOR_H__

class PressureSensor{
	public:
	
	PressureSensor(){
	}
	
	void setup(){
		PORTA.DIRCLR = PIN5_bm; // MISO
		PORTA.OUTCLR = PIN5_bm;
		PORTA.DIRSET = PIN6_bm; // SCK
	}
	
	uint32_t Read() {

		// wait for the reading to finish
		while (PORTA.IN & PIN5_bm) {}

		// read the 24-bit pressure
		uint32_t result = 0;
		for (int i=0; i<24; i++){
			pulse_clock();
			result = result << 1;
			if((PORTA.IN & PIN5_bm)) {
				result++;
			}
		}

		// take 2's compliment
		result=result ^ 0x800000;
		
		// pulse 3 times to start a 40 Hz pressure reading
		pulse_clock();
		pulse_clock();
		pulse_clock();
		
		return result;
	}
	
	private:
	
	void pulse_clock(){
		PORTA.OUTSET = PIN6_bm;
		PORTA.OUTCLR = PIN6_bm;
	}
};

#endif