#include "bsp.h"
#include "mrfi.h"
#include "nwk_types.h"
#include "nwk_api.h"
#include "bsp_leds.h"
#include "bsp_buttons.h"
#include "bsp_extended.h"
#include "uart_intfc.h"
#include <stdlib.h>

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
static uint8_t ins_ini = 0;
static uint8_t ins_end = 0;

struct ringbuf {
	char buffer[20];
	uint8_t size;
	uint8_t head;
	uint8_t tail;
	uint8_t items;
};

/*
* LOCAL FUNCTIONS
*/
static uint8_t sRxCallback(linkID_t);
static void main_loop(void);
static void wait_for_link(void);
static void process_instruction(struct ringbuf *b);
static void check_instructions(struct ringbuf *b);
static void init_inst_buf(struct ringbuf*);
static void append_data(struct ringbuf *buf_out, char *buf_in, uint8_t n);
static void print_rx_status(struct ringbuf *b);

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
	struct ringbuf inst_buf;
	uint8_t in_rx = 0;
	uint8_t chars_read = 0;
	char buf[15];
	
	init_inst_buf(&inst_buf);
	while (1) {
		if (rxFlag) {
			/* Receive and process radio message */
		}
		if (in_rx = rx_peek()) {
			if (in_rx <= 15)
				chars_read = rx_receive(buf, in_rx);
			else
				chars_read = rx_receive(buf, 15);
			append_data(&inst_buf, buf, chars_read);
		}
		check_instructions(&inst_buf);
		if (instFlag == 1) {
			tx_send("Found an instruction . . .\r\n",
				sizeof("Found an instruction . . .\r\n"));
			process_instruction(&inst_buf);
		}
	}
}

static void print_rx_status(struct ringbuf *b)
{
	uint8_t head = 48 + b->head;
	uint8_t tail = 48 + b->tail;
	uint8_t items = 48 + b->items;

	tx_send("\r\nhead: ", sizeof("\r\nhead: "));
	tx_send(&head, 1);
	tx_send("\r\ntail: ", sizeof("\r\ntail: "));
	tx_send(&tail, 1);
	tx_send("\r\nitems: ", sizeof("\r\nitems: "));
	tx_send(&items, 1);
	tx_send("\r\n", 2);
}

static void check_instructions(struct ringbuf *b)
{
	uint8_t i;
	uint8_t ini = 0;

	/* Search from tail up to (but not including) head */
	for (i = b->tail; i != b->head; i = (i + 1) % b->size) {
		if (b->buffer[i] == '?') {
			if (ini) {
			  	ins_ini = ini;
				ins_end = i;
				instFlag = 1;
				return;
			} else {
				ini = i;
			}
		}
	}
	/* Search in head */
	if (b->buffer[i] == '?') {
		if (ini) {
		  	ins_ini = ini;
			ins_end = i;
			instFlag = 1;
			return;
		}
	}
}

static void process_instruction(struct ringbuf *b)
{
        uint8_t i;
	//uint8_t start = 0;
	//uint8_t end = 0;
	uint8_t inst[15];
	uint8_t j = 0;
	
	/* Get instruction */
	for (i = 0; i < 15; i++)
		inst[i] = 0;
	for (i = ins_ini; i != ins_end; i = (i + 1) % b->size) {
		if (b->buffer[i] == '?')
			continue;
		inst[j++] = b->buffer[i];
	}
	b->tail = (ins_end + 1) % b->size;
	instFlag = 0;
	b->items -= j + 2;
	
	/* Parse instruction */
	//i = atoi(inst);
	//tx_send(&i, 1);
	
	/* Send message */
	for (i = 0; i < NUM_TX_RETRIES; i++) {
		SMPL_Send(sLinkID, inst, j);
		/* Turn on RX. default is RX Idle. */
		SMPL_Ioctl( IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_RXON, 0);
		SPIN_ABOUT_QUARTER_A_SECOND;
		if (rxFlag)
			break;
	}
	if (rxFlag) {
		tx_send("Data sent OK\r\n", sizeof("Data sent OK\r\n"));
		rxFlag = 0;
	}
	else {
		tx_send("No ACK\r\n", sizeof("No ACK\r\n"));
	}
}

static void append_data(struct ringbuf *buf_out, char *buf_in, uint8_t n)
{
	uint8_t i;
	
	if (n < 1)
		return;
	for (i = 0; i < n; i++) {
		buf_out->buffer[buf_out->head] = buf_in[i];
		buf_out->head = (buf_out->head + 1) % buf_out->size;
		buf_out->items++;
	}
	print_rx_status(buf_out);
}

static void init_inst_buf(struct ringbuf *buf){
	buf->size = 20;
	buf->head = 0;
	buf->tail = 0;
	buf->items = 0;
}

static uint8_t sRxCallback(linkID_t lid)
{
	if(lid) {
		rxFlag = 1;
		/* Radio IDLE to save power */
		SMPL_Ioctl( IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_RXIDLE, 0);
	}
	/* Leave frame to be read by application. */
	return 0;
}
