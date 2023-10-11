#define F_CPU 4000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "LedManager.h"
#include "DisplayManager.h"
#include "SerialManager.h"
#include "PressureSensor.h"
#include "ButtonManager.h"

LedManager leds = LedManager();
DisplayManager display = DisplayManager();
PressureSensor sensor = PressureSensor();
ButtonManager button = ButtonManager();

void setup_multiplex_display_timer(){
	TCB0.INTCTRL |= TCB_CAPT_bm;
	TCB0.CCMP = F_CPU / 500;
	TCB0.CTRLA |= TCB_ENABLE_bm;
	sei();
}

ISR(TCB0_INT_vect)
{
	display.multiplex_tick();
	TCB0.INTFLAGS = TCB_OVF_bm | TCB_CAPT_bm;
}

volatile int32_t zero_value = 0;

int main(void)
{
	leds.setup();
	display.setup();
	sensor.setup();
	button.setup();
	
	setup_multiplex_display_timer();

	// zero on startup
	// TODO: put this logic in the sensor manager
	for (int i=0; i<5; i++){
		zero_value = sensor.Read();
	}
	
	while(1){
		
		// TODO: put this logic in the sensor manager
		//leds.sample_toggle(); // NOTE: this is highly distracting if it's bright green
		int32_t sensor_value_raw = sensor.Read();
		int32_t sensor_value_centered = sensor_value_raw - zero_value;
		int16_t display_value = sensor_value_centered / 10000;
		display.show(display_value);
		
		if (button.is_down()){
			zero_value = sensor_value_raw;
			leds.mode_on();
			button.wait_until_up();
			leds.mode_off();
		}
	}
}