#ifndef __SERIALMANAGER_H__
#define __SERIALMANAGER_H__

#include <stdio.h>

#define GET_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (16 * (float)BAUD_RATE)) + 0.5)

class SerialManager
{
	public:
	
	SerialManager(){
		PORTA.DIRSET = PIN0_bm;
		USART0.CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_SBMODE_1BIT_gc | USART_CHSIZE_8BIT_gc;
		USART0.BAUD = GET_BAUD_RATE(9600);
		USART0.CTRLB = USART_RXMODE_NORMAL_gc;
		USART0.CTRLB |= USART_TXEN_bm;
	}
	
	void WriteChar(char c){
		while (!(USART0.STATUS & USART_DREIF_bm)) {;} // wait for previous byte to send
		USART0.TXDATAL = c;
	}
	
	void WriteLineBreak(){
		WriteChar('\r');
		WriteChar('\n');
	}

	void WriteString(const char* str){
		uint8_t i = 0;
		while (str[i] != '\0')
		{
			WriteChar(str[i]);
			i++;
		}
	}

	void WriteLineString(const char* str){
		WriteString(str);
		WriteLineBreak();
	}

	void WriteUInt(uint32_t value){
		uint8_t nonzero_seen = 0;
		uint32_t divisor = 1000000000;
		while(divisor > 0){
			uint8_t digit = value / divisor;
			char c = '0' + digit;
			value -= digit * divisor;
			divisor /= 10;
			if (digit > 0){
				nonzero_seen = 1;
			}
			if (nonzero_seen){
				WriteChar(c);
			}
		}
	}

	void WriteInt(int32_t value){
		if (value == 0){
			WriteChar('0');
			return;
		}
		if (value < 0){
			WriteChar('-');
		}
		uint8_t nonzero_seen = 0;
		int32_t divisor = 1000000000;
		while(divisor > 0){
			int8_t digit = value / divisor;
			if (digit < 0){
				digit *= -1;
				value += digit * divisor;
				} else {
				value -= digit * divisor;
			}
			char c = '0' + digit;
			divisor /= 10;
			if (digit > 0){
				nonzero_seen = 1;
			}
			if (nonzero_seen){
				WriteChar(c);
			}
		}
	}
};

#endif
