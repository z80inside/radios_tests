/*****************************************************************************
 *   This example shows how to read and write to the eeprom
 *
 *   Copyright(C) 2010, Embedded Artists AB
 *   All rights reserved.
 *
 ******************************************************************************/

#ifdef __USE_CMSIS
#include "LPC13xx.h"
#endif

#include "timer32.h"
#include "i2c.h"
#include "uart.h"
#include "type.h"

#include "string.h"
#include "stdio.h"

#define EEPROM_WRITE_LEN 200
#define EEPROM_I2C_ADDR 0xA0
#define EEPROM_PAGE_SIZE 32
#define EEPROM_TOTAL_SIZE 4096

uint16_t writeToEEPROM(uint32_t address, uint8_t* data, uint16_t length);
uint16_t readFromEEPROM(uint32_t address, uint8_t* data, uint16_t length);

int main(void) {
	uint8_t buf[EEPROM_WRITE_LEN];
	uint8_t index = 0;
	uint16_t length = 0;
	uint32_t address = 0x0001;

	//Init timers
	init_timer32(0, 10);

	I2CInit((uint32_t) I2CMASTER, 0);

	UARTInit(115200);

	for (index = 0; index < EEPROM_WRITE_LEN; index++) {
		buf[index] = (uint8_t)(index + 6);
	}

	length = writeToEEPROM(address, buf, EEPROM_WRITE_LEN);

	if (length != EEPROM_WRITE_LEN) {
		UARTSendString((uint8_t*) "Failed to write data\n");
		return 1;
	}

	delay32Ms(0, 2000);

	memset(buf, 0, EEPROM_WRITE_LEN);

	length = readFromEEPROM(address, buf, EEPROM_WRITE_LEN);

	if (length != EEPROM_WRITE_LEN) {
		UARTSendString((uint8_t*) "Failed to read all data\n");
		return 1;
	}

	for (index = 0; index < EEPROM_WRITE_LEN; index++) {
		if (buf[index] != (uint8_t)(index + 6)) {
			UARTSendString((uint8_t*) "Invalid data\n");
			return 1;
		}
	}

	return 0;
}

uint16_t writeToEEPROM(uint32_t address, uint8_t* data, uint16_t length) {
	uint8_t writeBuffer[2 + EEPROM_PAGE_SIZE];
	uint16_t data_index = 0;

	if (length > EEPROM_TOTAL_SIZE || address + length > EEPROM_TOTAL_SIZE) {
		return -1;
	}

	// Write bytes
	while (length > 0) {
		uint16_t writeLength = EEPROM_PAGE_SIZE - (address % EEPROM_PAGE_SIZE);

		writeBuffer[0] = address >> 8;
		writeBuffer[1] = address & 0xff;

		if (length < writeLength) {
			writeLength = length;
		}

		memcpy(&writeBuffer[2], (void*) &data[data_index], writeLength);
		I2CWrite(EEPROM_I2C_ADDR, writeBuffer, writeLength + 2);

		data_index += writeLength;
		length -= writeLength;
		address += writeLength;

		delay32Ms(0, 10);
	}

	return data_index;
}

uint16_t readFromEEPROM(uint32_t address, uint8_t* data, uint16_t length) {

	uint8_t command[2];

	command[0] = address >> 8;
	command[1] = address & 0xff;

	//read
	I2CWrite(EEPROM_I2C_ADDR, command, 2);
	delay32Ms(0, 10);
	I2CRead(EEPROM_I2C_ADDR, data, length);

	return length;
}

