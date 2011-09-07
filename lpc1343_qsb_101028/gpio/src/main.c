/*****************************************************************************
 *   Goes through all gpios and sets them high/low every 100 ms.
 *
 *   Copyright(C) 2010, Embedded Artists AB
 *   All rights reserved.
 *
 ******************************************************************************/

#ifdef __USE_CMSIS
#include "LPC13xx.h"
#endif

#include "gpio.h"
#include "timer32.h"

void setAllPinsToOutput(void);
void setAllPinsValue(uint8_t value);

int pins [26] [26]= {{0, 7}, {0, 8}, {0, 9},
					  {0, 10},{1, 10}, {0, 11},
					  {1, 0},{1, 1}, {1, 2},
					  {1, 3}, {1, 4}, {1, 11},
					  {3, 2},{0, 6},{1, 9},
					  {0, 5}, {0, 4},{0, 3},
					  {0, 2}, {1, 8},{0, 0},
					  {2, 0}, {0, 1},{1, 7},
					  {1, 6}, {1, 5}};

int main(void) {

	GPIOInit();
	init_timer32(0, 10);

	setAllPinsToOutput();
	uint8_t on = 1;

	while (1) {
		setAllPinsValue(on);
		on = !on;
	}

	return 0;
}

void setAllPinsToOutput(void) {
	uint8_t i;

	//Selects function for GPIO, Disable JTAG
	LPC_IOCON->JTAG_TMS_PIO1_0 &= ~0x07;
	LPC_IOCON->JTAG_TMS_PIO1_0 |= 0x001;
	LPC_IOCON->JTAG_TDO_PIO1_1 &= ~0x07;
	LPC_IOCON->JTAG_TDO_PIO1_1 |= 0x001;
	LPC_IOCON->JTAG_nTRST_PIO1_2 &= ~0x07;
	LPC_IOCON->JTAG_nTRST_PIO1_2 |= 0x001;

	LPC_IOCON->JTAG_TDI_PIO0_11 &= ~0x07;
	LPC_IOCON->JTAG_TDI_PIO0_11 |= 0x001;

	LPC_IOCON->PIO1_5 &= ~0x07;

	//Set all pins to output
	for(i = 0; i < 26; i++) {
		uint8_t port = pins[i][0];
		uint8_t pin = pins[i][1];
		GPIOSetDir(port, pin, 1);
	}
}

void setAllPinsValue(uint8_t value) {

	//Set all pins to value
	uint8_t i;

	for(i = 0; i < 26; i++) {
		uint8_t port = pins[i][0];
		uint8_t pin = pins[i][1];
		GPIOSetValue(port, pin, value);
	    delay32Ms(0, 100);
	}

}
