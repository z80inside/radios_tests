/***********************************************************************************

Filename:	    simple_link.c

Description:	

Operation:    

***********************************************************************************/

/***********************************************************************************
* INCLUDES
*/
#include "bsp.h"
#include "mrfi.h"
#include "nwk_types.h"
#include "nwk_api.h"
#include "bsp_leds.h"
#include "bsp_buttons.h"
#include "bsp_extended.h"
#include "uart_intfc.h"


/***********************************************************************************
* CONSTANTS and DEFINITIONS
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

/***********************************************************************************
* LOCAL VARIABLES
*/
static          linkID_t      sLinkID;
static volatile uint8_t       sSemaphore;
static          uint8_t       sCurrentPwrLevel;
static          uint8_t       sRequestPwrLevel;
static          uint8_t       sNoAckCount = 0;

/***********************************************************************************
* LOCAL FUNCTIONS
*/
static uint8_t    sRxCallback(linkID_t);
static void       sMaster(void);
static void       sSlave(void);


/***********************************************************************************
* @fn          main
*
* @brief       This is the main entry of the SMPL link application. It sets
*              random addresses for the nodes, initalises and runs
*              MASTER and SLAVE tasks sequentially in an endless loop.
*
* @return      none
*/
void main (void)
{
  char rxByte = 0;
  uint8_t buttonPushed;
  BSP_Init();

  /* Init UART */
  uart_intfc_init();
  
  /* Create and set random address for this device. */
  addr_t lAddr;
  BSP_createRandomAddress(&lAddr);      
  SMPL_Ioctl(IOCTL_OBJ_ADDR, IOCTL_ACT_SET, &lAddr);
  
  /* Initialize SimpliciTI and provide Callback function */
  SMPL_Init(sRxCallback);
  
  tx_send_wait("\r\nSimpliciTI - Simple Peer to Peer Example with UART\r\n", sizeof("\r\nSimpliciTI - Simple Peer to Peer Example with UART\r\n")); 
  tx_send_wait("\r\nPress Master or Slave to continue...\r\n", sizeof("\r\nPress Master or Slave to continue...\r\n")); 
  
  /* Turn on LEDs indicating power on */
  BSP_TURN_ON_LED1();
  BSP_TURN_ON_LED2();
  
  //BSP_SleepFor( POWER_MODE_2, SLEEP_1_MS_RESOLUTION, 1000);
  
  BSP_TURN_OFF_LED1();
  BSP_TURN_OFF_LED2();
  
  /* Enter PM3 until a button is pushed */
  buttonPushed = BSP_SleepUntilButton( POWER_MODE_3, BOTH_BUTTONS);
  
  if(buttonPushed==1)
    sMaster();
  
  if(buttonPushed==2)  
    sSlave();
  
  while (1);
} 


/***********************************************************************************
* LOCAL FUNCTIONS
*/

/***********************************************************************************
* @fn          sMaster
*
* @brief       Sends a packet and waits for ACK from slave.
*              Blinking green led indicates packet acknowledged
*              Blinking red led indicates packet not acknowledged
*              Adjust output power dynamically
*
* @param       none
*
* @return      none
*/
static void sMaster(void)
{
  uint8_t  radioMsg[2], len;   
  ioctlRadioSiginfo_t info;
  
  sCurrentPwrLevel  = MAXIMUM_OUTPUT_POWER;
  sRequestPwrLevel  = MAXIMUM_OUTPUT_POWER;
  
  tx_send_wait("\r\nLooking for a link as master",sizeof("\r\nLooking for a link as master"));
  
  /* Continue to try to link until success */
  while (SMPL_SUCCESS != SMPL_Link(&sLinkID))
  {
    BSP_TOGGLE_LED1();
    BSP_TOGGLE_LED2();
  }
  
  tx_send("\r\nLink established!",sizeof("\r\nLink established!"));
  
  BSP_TURN_OFF_LED1();
  BSP_TURN_OFF_LED2();
  
  while (1)
  {   
    /* If SLAVE button pushed, lit both LEDs for 1 second */
    if( BSP_BUTTON2() )
    {
      BSP_TURN_ON_LED1();
      BSP_TURN_ON_LED2();
      
      BSP_SleepFor( POWER_MODE_2, SLEEP_1_MS_RESOLUTION, 5000);
      
      BSP_TURN_OFF_LED1();
      BSP_TURN_OFF_LED2();
    }
    
    /* Build the message */
    radioMsg[0] = sRequestPwrLevel;
    radioMsg[1] = sCurrentPwrLevel;
    
    for( uint8_t x = 0; x < NUM_TX_RETRIES; x++ )
    {  
      SMPL_Send(sLinkID, radioMsg, sizeof(radioMsg));
      tx_send_wait("\r\nMessage sent",sizeof("\r\nMessage sent"));
          
      /* Turn on RX. default is RX Idle. */
      SMPL_Ioctl( IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_RXON, 0);
      
      SPIN_ABOUT_QUARTER_A_SECOND;  /* Might have to be longer for bigger payloads */
      if( sSemaphore )
        break;
    }      

    /* Radio IDLE to save power */
    SMPL_Ioctl( IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_RXIDLE, 0);
    
    if( sSemaphore )                    /* Acknowledge successfully received */
    {
      SMPL_Receive(sLinkID, radioMsg, &len);
      sSemaphore = 0;
      tx_send_wait("\r\nACK received",sizeof("\r\nACK received"));
      
      /* Check and set desired output power */
      if ( sCurrentPwrLevel != radioMsg[0] )
      {
        sCurrentPwrLevel = radioMsg[0];
        tx_send("\r\nCurrent power level: ", sizeof("\r\nCurrent power level: "));
        tx_send(&sCurrentPwrLevel, 1);
        SMPL_Ioctl( IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_SETPWR, &sCurrentPwrLevel);
      }
      
      /* Check and adjust wanted output power */
      info.lid = sLinkID;
      SMPL_Ioctl( IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_SIGINFO, &info);
      if( sRequestPwrLevel > MINIMUM_OUTPUT_POWER )
        if( info.sigInfo.rssi  > RSSI_UPPER_THRESHOLD )
          sRequestPwrLevel--;
      
      if( sRequestPwrLevel < MAXIMUM_OUTPUT_POWER )
        if( info.sigInfo.rssi  < RSSI_LOWER_THRESHOLD )
          sRequestPwrLevel++;
      
      BSP_TURN_ON_LED1();
      BSP_SleepFor( POWER_MODE_2, SLEEP_1_MS_RESOLUTION, 500);
      BSP_TURN_OFF_LED1();
      sNoAckCount = 0;     
    }
    else /* No ACK */ 
    {
      tx_send_wait("\r\nNO ACK",sizeof("\r\nNO ACK"));
      BSP_TURN_ON_LED2();
      BSP_SleepFor( POWER_MODE_2, SLEEP_1_MS_RESOLUTION, 500);
      BSP_TURN_OFF_LED2();
      
      sNoAckCount++;
    }      
    
    /* No ACK at after NO_ACK_THRESHOLD. Go to sleep */ 
    if( sNoAckCount == NO_ACK_THRESHOLD )                              
    {
      sNoAckCount = 0;
      /* Radio IDLE to save power */
      SMPL_Ioctl( IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_RXIDLE, 0);
      
      BSP_TURN_ON_LED1();
      BSP_TURN_ON_LED2();
      BSP_SleepFor( POWER_MODE_2, SLEEP_1_MS_RESOLUTION, 3000);
      BSP_TURN_OFF_LED1();
      BSP_TURN_OFF_LED2();
      
      BSP_SleepUntilButton( POWER_MODE_3, MASTER_BUTTON);
    }  
  }
}


/***********************************************************************************
* @fn          sSlave
*
* @brief       Waits for packet from Master and acknowledge this.
*              Red led lit means linked to master
*              Blinking green led indicates packet received
*              Adjust output power dynamically
*
* @param       none
*
* @return      none
*/
static void sSlave(void)
{
  uint8_t  radioMsg[2], len;   
  ioctlRadioSiginfo_t info;
  
  sCurrentPwrLevel  = MAXIMUM_OUTPUT_POWER;
  sRequestPwrLevel  = MAXIMUM_OUTPUT_POWER;

  tx_send_wait("\r\nLooking for a link as slave",sizeof("\r\nLooking for a link as slave"));
  
  /* Listen for link forever... */
  BSP_TURN_ON_LED1();
  BSP_TURN_ON_LED2();
  while (SMPL_LinkListen(&sLinkID) != SMPL_SUCCESS)
  {
    BSP_TOGGLE_LED1();
    BSP_TOGGLE_LED2();
  }

  tx_send("\r\nLink established!",sizeof("\r\nLink established!"));
  
  /* Turning on LED2 to show that we have link*/
  BSP_TURN_OFF_LED1();
  BSP_TURN_ON_LED2();
  
  /* turn on RX. default is RX off. */
  SMPL_Ioctl( IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_RXON, 0 );
  
  while (1)
  {
    if( sSemaphore )                    /* Acknowledge successfully received */
    {
      /* Radio IDLE to save power */
      SMPL_Ioctl( IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_RXIDLE, 0);
      SMPL_Receive(sLinkID, radioMsg, &len);
      sSemaphore = 0;
      
      /* Check and set desired output power */
      if ( sCurrentPwrLevel != radioMsg[0] )
      {
        sCurrentPwrLevel = radioMsg[0];
        SMPL_Ioctl( IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_SETPWR, &sCurrentPwrLevel);
      }
      
      /* Check and adjust wanted output power */
      info.lid = sLinkID;
      SMPL_Ioctl( IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_SIGINFO, &info);
      if( sRequestPwrLevel > MINIMUM_OUTPUT_POWER )
        if( info.sigInfo.rssi  > RSSI_UPPER_THRESHOLD )
          sRequestPwrLevel--;
      
      if( sRequestPwrLevel < MAXIMUM_OUTPUT_POWER )
        if( info.sigInfo.rssi  < RSSI_LOWER_THRESHOLD )
          sRequestPwrLevel++;
      
      /* Build and send acknowledge */
      radioMsg[0] = sRequestPwrLevel;
      radioMsg[1] = sCurrentPwrLevel;

      SMPL_Send(sLinkID, radioMsg, sizeof(radioMsg));
      
      /* Turn on RX. default is RX off. */
      SMPL_Ioctl( IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_RXON, 0);
      
      BSP_TURN_ON_LED1();
      SPIN_ABOUT_QUARTER_A_SECOND;
      BSP_TURN_OFF_LED1();  
    }  
  }
}


/***********************************************************************************
* @fn          sRxCallback
*
* @brief       
*
* @param       lid - link id message receive at
*
* @return      0 - frame left for application to read
*              1 - frame could be overwritten
*/
static uint8_t sRxCallback(linkID_t lid)
{
  if(lid)
  {  
    sSemaphore = 1;
   
    /* Radio IDLE to save power */
    SMPL_Ioctl( IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_RXIDLE, 0);
    tx_send_wait("\r\nSomething received",sizeof("\r\nSomething received"));
  }
  
  /* Leave frame to be read by application. */
  return 0;
}




