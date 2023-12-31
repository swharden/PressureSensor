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
SerialManager serial = SerialManager();
PressureSensor sensor = PressureSensor();
ButtonManager button = ButtonManager();

volatile int32_t zero_value = 0;

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

int main(void)
{
	setup_multiplex_display_timer();
	
	serial.WriteLineBreak();
	serial.WriteLineString("Pressure Sensor 1.0");
	_delay_ms(200);
	
	while (1)
	{
		int32_t sensor_value_raw = sensor.Read();
		int32_t sensor_value_centered = sensor_value_raw - zero_value;
		int16_t display_value = sensor_value_centered / 10000;
		
		serial.WriteInt(sensor_value_raw);
		serial.WriteString(", ");
		serial.WriteInt(sensor_value_centered);
		serial.WriteString(", ");
		serial.WriteInt(display_value);
		serial.WriteLineBreak();
		
		display.show(display_value);
		
		if (button.is_down()){
			zero_value = sensor_value_raw;
			serial.WriteLineString("Button Pressed");
			leds.status_on();
			button.wait_until_up();
			leds.status_off();
		}
	}
}