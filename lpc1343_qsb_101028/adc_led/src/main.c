/*****************************************************************************
 *   Flash led on PIO0.7
 *
 *   Copyright(C) 2010, Embedded Artists AB
 *   All rights reserved.
 *
 ******************************************************************************/

#ifdef __USE_CMSIS
#include "LPC13xx.h"
#endif

#include "timer32.h"
#include "gpio.h"
#include "adc.h"

int main(void) {
	uint8_t led = 0;

	GPIOInit();

	ADCInit(ADC_CLK);
	init_timer32(0, 10);

	GPIOSetDir(PORT0, 7, 1);

	while (1) {
		uint32_t value = ADCRead(0);
		delay32Ms(0, value);
		GPIOSetValue(PORT0, 7, led);
		led = !led;

	}
	return 0;
}
