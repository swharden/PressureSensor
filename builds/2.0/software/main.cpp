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

int main(void)
{
	leds.setup();
	
	while(1){
		leds.sample_on();_delay_ms(200);
		leds.mode_on();_delay_ms(200);
		leds.signal_on();_delay_ms(200);
		
		leds.sample_off();_delay_ms(200);
		leds.mode_off();_delay_ms(200);
		leds.signal_off();_delay_ms(200);
	}
}