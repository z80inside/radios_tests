#include "bsp.h"
#include "mrfi.h"
#include "nwk_types.h"
#include "nwk_api.h"
#include "bsp_leds.h"
#include "bsp_buttons.h"
#include "bsp_extended.h"
#include "uart_intfc.h"

/*
* CONSTANTS AND DEFINITIONS
*/
#define SPIN_ABOUT_QUARTER_A_SECOND   NWK_DELAY(250)
#define SPIN_ABOUT_100_MS             NWK_DELAY(100)

#define NUM_TX_RETRIES                3
#define NO_ACK_THRESHOLD              50

#define RSSI_UPPER_THRESHOLD          -40
#define RSSI_LOWER_THRESHOLD          -70

#define MINIMUM_OUTPUT_POWER          0
#define MEDIUM_OUTPUT_POWER           1
#define MAXIMUM_OUTPUT_POWER          2

#define SLEEP_31_25_US_RESOLUTION     0
#define SLEEP_1_MS_RESOLUTION         1
#define SLEEP_32_MS_RESOLUTION        2
#define SLEEP_1_S_RESOLUTION          3

#define MASTER_BUTTON                 1
#define SLAVE_BUTTON                  2
#define BOTH_BUTTONS                  3

/*
* LOCAL VARIABLES
*/
static linkID_t sLinkID;
static volatile uint8_t rxFlag;
static volatile uint8_t instFlag;
static uint8_t sCurrentPwrLevel;
static uint8_t sRequestPwrLevel;
static uint8_t sNoAckCount = 0;

/*
* LOCAL FUNCTIONS
*/
static uint8_t sRxCallback(linkID_t);
static void main_loop(void);
static void wait_for_link(void);
static void process_instruction(void);
static uint8_t check_instructions(void);

void main (void)
{
	char rxByte = 0;
	BSP_Init();

	/* Init UART */
	uart_intfc_init();

	/* Create and set random address for this device. */
	addr_t lAddr;
	BSP_createRandomAddress(&lAddr);
	SMPL_Ioctl(IOCTL_OBJ_ADDR, IOCTL_ACT_SET, &lAddr);

	/* Initialize SimpliciTI and provide Callback function */
	SMPL_Init(sRxCallback);

	tx_send_wait("Send-Receive demo\r\n", sizeof("Send-Receive demo\r\n"));

	/* Turn on LEDs indicating power on */
	BSP_TURN_ON_LED1();
	BSP_TURN_ON_LED2();

	BSP_SleepFor( POWER_MODE_2, SLEEP_1_MS_RESOLUTION, 1000);

	BSP_TURN_OFF_LED1();
	BSP_TURN_OFF_LED2();

	wait_for_link();

	tx_send_wait("Send a number enclosed in ? signs\r\n",
		sizeof("Send a number enclosed in ? signs\r\n"));

	main_loop();
}

static void wait_for_link()
{
	tx_send_wait("Looking for a link . . .\r\n",
		sizeof("Looking for a link . . .\r\n"));
	/* Continue to try to link until success */
	while (1) {
		if (SMPL_SUCCESS == SMPL_Link(&sLinkID))
			break;
		if (SMPL_SUCCESS == SMPL_LinkListen(&sLinkID))
			break;
		BSP_TOGGLE_LED1();
		BSP_TOGGLE_LED2();
	}
	tx_send("Link established!\r\n",sizeof("Link established!\r\n"));
}

/* Application logic state machine */
static void main_loop()
{
	uint8_t available = 0;
	while (1) {
		if (rxFlag) {
			/* Receive and process radio message */
		}
		if (available = rx_peek()) {
			/* ins_buffer[current] <- rx_receive(available) */
		}
		check_instructions();
		if (instFlag == 1) {
			process_instruction();
		}
	}
}

static uint8_t check_instructions(void)
{
}

static void process_instruction(void)
{
}

static uint8_t sRxCallback(linkID_t lid)
{
	if(lid) {
		rxFlag = 1;
		/* Radio IDLE to save power */
		SMPL_Ioctl( IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_RXIDLE, 0);
		tx_send_wait("\r\nSomething received",sizeof("\r\nSomething received"));
	}
	/* Leave frame to be read by application. */
	return 0;
}
