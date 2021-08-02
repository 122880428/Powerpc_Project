#ifndef _XR16L788_H_
#define _XR16L788_H_


#include "ppc5125Intr.h"
/*
*********************************************************************************************************
*                                               CONSTANTS
*********************************************************************************************************
*/

#define XFComTxBuffSize 1024
#define XFComRxBuffSize 1024

#define XFComFifoRxLen  1024 
#define XFComFifoTxLen  1024 

#define UARTFREQ   66666666    /*Hz*/
typedef struct {
    unsigned long   Base;
    unsigned short  Rxhead,Rxtail;
    unsigned char   RxBuf[XFComRxBuffSize];
    unsigned short  Txhead,Txtail;
    unsigned char   TxBuf[XFComTxBuffSize];
} XFCommStruc;


extern XFCommStruc             XFCOM[9];

#define  FCOM_UART_RX_EN         0               /*[Defines for Uart Registers]*/
#define  FCOM_UART_TX_EN         2
#define  FCOM_UART_BT            4
#define  FCOM_UART_PARITY        6
#define  FCOM_UART_FCR           8
#define  FCOM_UART_RXCNT         10
#define  FCOM_UART_RX_REG        12
#define  FCOM_UART_TXCNT         14
#define  FCOM_UART_TX_REG        16
#define  FCOM_UART_422_232       18
#define  FCOM_UART_TIME_OUT      20
#define  FCOM_UART_INT_ENABLE    22

#define  FCOM_UART_STATUS        0x84002000

#define  FCOM_IOBASE             0x84000000

#define  IRQ0_INT_SOURCE         INT_IRQ0
#define  IRQ1_INT_SOURCE         INT_IRQ1

/*
*********************************************************************************************************
*                                               CONSTANTS
*********************************************************************************************************
*/
#ifndef  NUL
#define  NUL                  0x00
#endif

#define  BIT0                 0x01               /*[Bit Specific]*/
#define  BIT1                 0x02
#define  BIT2                 0x04
#define  BIT3                 0x08
#define  BIT4                 0x10
#define  BIT5                 0x20
#define  BIT6                 0x40
#define  BIT7                 0x80


#define  COMM_PARITY_NONE        0               /*[Defines for setting parity]*/
#define  COMM_PARITY_EVEN        1
#define  COMM_PARITY_ODD         2

//皇：挂载在fpga下的串口，区别于cpu的串口
#define  FCOM1           0               /*[Com Specific]*/             
#define  FCOM2           1
#define  FCOM3           2                         
#define  FCOM4           3
#define  FCOM5           4
#define  FCOM6           5                         
#define  FCOM7           6
#define  FCOM8           7
#define  FCOM9           8                /*Sbus*/              

#define  RS232                   0
#define  RS422                   1


extern XFCommStruc            XFCOM[9];             /* XR16L788 */


/*
*********************************************************************************************************
*                                      FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void           FComSetIOBase(void);															/*设置串口基地址初始化*/    
void FComInit(unsigned char Port, long BaudRate,unsigned char Parity,unsigned char StopBit,unsigned short RxFifoNum,unsigned char Mode_422_232);		/*串口初始化*/
unsigned short  FComIn (unsigned char port,  unsigned char buf[], unsigned short len);		/*串口读取缓冲区数据*/
unsigned short  FComOut(unsigned char port, unsigned char buf[], unsigned short len);		/*串口发送缓冲区数据*/
unsigned short  FComTxLen (unsigned char port);												/*串口发送缓冲区数据长度查询*/
unsigned short  FComRxLen (unsigned char port);												/*串口接收缓冲区数据长度查询*/
unsigned short FComInPoll (unsigned char port);												/**/
void  FComRxInterruptHandler(unsigned char port);											/*串口中断处理函数*/
void  FComInterruptHandler(void);															/*串口接收中断处理函数*/





#endif

