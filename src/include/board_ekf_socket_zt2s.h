#ifndef SRC_INCLUDE_BOARD_EKF_SOCKET_ZT2S_H_
#define SRC_INCLUDE_BOARD_EKF_SOCKET_ZT2S_H_

/************************* Configure KEY GPIO ***************************************/
#define MAX_BUTTON_NUM  1

#define BUTTON                  GPIO_PB5
#define PB5_INPUT_ENABLE        ON
#define PB5_DATA_OUT            OFF
#define PB5_OUTPUT_ENABLE       OFF
#define PB5_FUNC                AS_GPIO
//#define PULL_WAKEUP_SRC_PB4     PM_PIN_PULLUP_10K

enum {
    VK_SW1 = 0x01,
};

#define KB_MAP_NORMAL   {\
        {VK_SW1,}}

#define KB_MAP_NUM      KB_MAP_NORMAL
#define KB_MAP_FN       KB_MAP_NORMAL

#define KB_DRIVE_PINS  {NULL }
#define KB_SCAN_PINS   {BUTTON}

/************************** Configure LED ****************************************/

#define MAX_LED_NUM             2

#define LED_ON                  0
#define LED_OFF                 1

#define LED1_GPIO               GPIO_PB1
#define PB1_FUNC                AS_GPIO
#define PB1_OUTPUT_ENABLE       ON
#define PB1_INPUT_ENABLE        OFF

#if !UART_PRINTF_MODE
#define LED2_GPIO               GPIO_PC4
#define PC4_FUNC                AS_GPIO
#define PC4_OUTPUT_ENABLE       ON
#define PC4_INPUT_ENABLE        OFF

#define LED_STATUS_GPIO         LED2_GPIO

#endif

#define LED_NET_GPIO            LED1_GPIO

/********************* Configure Relay ***************************/

#define RELAY_ACTIVED           1
#define RELAY_DEACTIVED         0

#define RELAY_OFF_GPIO          GPIO_PB7
#define PB7_FUNC                AS_GPIO
#define PB7_OUTPUT_ENABLE       ON
#define PB7_INPUT_ENABLE        OFF
#define PB7_DATA_OUT            RELAY_DEACTIVED

#define RELAY_ON_GPIO           GPIO_PB4
#define PB4_FUNC                AS_GPIO
#define PB4_OUTPUT_ENABLE       ON
#define PB4_INPUT_ENABLE        OFF
#define PB4_DATA_OUT            RELAY_DEACTIVED

/*********************** Configure BL0937 ******************************/

#define SEL_GPIO                GPIO_PD2
#define PD2_FUNC                AS_GPIO
#define PD2_OUTPUT_ENABLE       ON
#define PD2_INPUT_ENABLE        OFF
#define PD2_DATA_OUT            OFF

#define CF_GPIO                 GPIO_PC3
#define PC3_FUNC                AS_GPIO
#define PC3_OUTPUT_ENABLE       OFF
#define PC3_INPUT_ENABLE        ON

#define CF1_GPIO                GPIO_PC2
#define PC2_FUNC                AS_GPIO
#define PC2_OUTPUT_ENABLE       OFF
#define PC2_INPUT_ENABLE        ON

/********************* Configure printf UART ***************************/

#if UART_PRINTF_MODE
#define DEBUG_INFO_TX_PIN       GPIO_PC4    //GPIO_SWS    //printf
#define DEBUG_BAUDRATE          115200

#endif /* UART_PRINTF_MODE */



#endif /* SRC_INCLUDE_BOARD_EKF_SOCKET_ZT2S_H_ */
