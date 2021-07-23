#ifndef __MSCAN__
#define __MSCAN__


#define CAN_BASE_FRAME          0  
#define CAN_EXT_FRAME           1 

#define INT_MSCAN1		12	/* level 12 interrupt */
#define INT_MSCAN2		13	/* level 13 interrupt */
#define INT_MSCAN3 		90	/* level 90 interrupt */
#define INT_MSCAN4 		91	/* level 91 interrupt */

#define	CAN_SEND_BUF_LEN	64			


#define CAN_CHANNAL1         0
#define CAN_CHANNAL2         1
#define CAN_CHANNAL3         2
#define CAN_CHANNAL4         3


#define CAN_100Kbps		1    
#define CAN_125Kbps		2   
#define CAN_200Kbps		3    
#define CAN_250Kbps		4   
#define CAN_400Kbps		5   
#define CAN_500Kbps		6   
#define CAN_800Kbps		7    
#define CAN_1Mbps		8   




/* MSCAN offset based on MSCAN base address */
#define MSCAN_CANCTL0_OFFSET		 	0x00  
#define MSCAN_CANCTL1_OFFSET	 		0x01  
#define MSCAN_CANBTR0_OFFSET		   	0x04  
#define MSCAN_CANBTR1_OFFSET		 	0x05  
#define MSCAN_CANRFLG_OFFSET 		 	0x08  
#define MSCAN_CANRIER_OFFSET 	 		0x09  
#define MSCAN_CANTFLG_OFFSET 		        0x0C  
#define MSCAN_CANTIER_OFFSET    		0x0D 
#define MSCAN_CANTARQ_OFFSET    		0x10  
#define MSCAN_CANTAAK_OFFSET    		0x11 
#define MSCAN_CANTBSEL_OFFSET		 	0x14
#define MSCAN_CANIDAC_OFFSET	 		0x15 
#define MSCAN_CANMISC_OFFSET		   	0x19 
#define MSCAN_CANRXERR_OFFSET		 	0x1C  
#define MSCAN_CANTXERR_OFFSET 		 	0x1D 
#define MSCAN_CANIDAR0_OFFSET 	 		0x20 
#define MSCAN_CANIDAR1_OFFSET 	 		0x21 
#define MSCAN_CANIDAR2_OFFSET 	 		0x24 
#define MSCAN_CANIDAR3_OFFSET 	 		0x25
#define MSCAN_CANIDMR0_OFFSET 	 		0x28 
#define MSCAN_CANIDMR1_OFFSET 	 		0x29 
#define MSCAN_CANIDMR2_OFFSET 	 		0x2C 
#define MSCAN_CANIDMR3_OFFSET 	 		0x2D
#define MSCAN_CANIDAR4_OFFSET 	 		0x30 
#define MSCAN_CANIDAR5_OFFSET 	 		0x31 
#define MSCAN_CANIDAR6_OFFSET 	 		0x34 
#define MSCAN_CANIDAR7_OFFSET 	 		0x35
#define MSCAN_CANIDMR4_OFFSET 	 		0x38 
#define MSCAN_CANIDMR5_OFFSET 	 		0x39 
#define MSCAN_CANIDMR6_OFFSET 	 		0x3C 
#define MSCAN_CANIDMR7_OFFSET 	 		0x3D

#define MSCAN_RXIDR0_OFFSET 	 	        0x40 
#define MSCAN_RXIDR1_OFFSET 	 	        0x41 
#define MSCAN_RXIDR2_OFFSET 	 	        0x44 
#define MSCAN_RXIDR3_OFFSET 	 	        0x45  
#define MSCAN_RXDSR0_OFFSET 	 	   	0x48 
#define MSCAN_RXDSR1_OFFSET 	 	   	0x49  
#define MSCAN_RXDSR2_OFFSET 	 	   	0x4C  
#define MSCAN_RXDSR3_OFFSET 	      	        0x4D 
#define MSCAN_RXDSR4_OFFSET 	 	   	0x50 
#define MSCAN_RXDSR5_OFFSET 	 	   	0x51  
#define MSCAN_RXDSR6_OFFSET 	 	   	0x54  
#define MSCAN_RXDSR7_OFFSET 	 	   	0x55 
#define MSCAN_RXDLR_OFFSET 	 	     	0x58 
#define MSCAN_RXTBPR_OFFSET 	 	   	0x59 
#define MSCAN_RXTSRH_OFFSET 	 	   	0x5C 
#define MSCAN_RXTSRL_OFFSET 	 	   	0x5D 

#define MSCAN_TXIDR0_OFFSET 	 	        0x60 
#define MSCAN_TXIDR1_OFFSET 	 	        0x61 
#define MSCAN_TXIDR2_OFFSET 	 	        0x64 
#define MSCAN_TXIDR3_OFFSET 	 	        0x65  
#define MSCAN_TXDSR0_OFFSET 	 	   	0x68 
#define MSCAN_TXDSR1_OFFSET 	 	   	0x69  
#define MSCAN_TXDSR2_OFFSET 	 	   	0x6C  
#define MSCAN_TXDSR3_OFFSET 	      	        0x6D 
#define MSCAN_TXDSR4_OFFSET 	 	   	0x70 
#define MSCAN_TXDSR5_OFFSET 	 	   	0x71  
#define MSCAN_TXDSR6_OFFSET 	 	   	0x74  
#define MSCAN_TXDSR7_OFFSET 	 	   	0x75 
#define MSCAN_TXDLR_OFFSET 	 	     	0x78 
#define MSCAN_TXTBPR_OFFSET 	 	   	0x79 
#define MSCAN_TXTSRH_OFFSET 	 	   	0x7C 
#define MSCAN_TXTSRL_OFFSET 	 	   	0x7D 


/* CANCTL0 Bit Fields */
#define MSCAN_CANCTL0_INITRQ_MASK                0x1u
#define MSCAN_CANCTL1_INITAK_MASK                0x1u

#define  CAN1_INT_SOURCE           INT_MSCAN1
#define  CAN2_INT_SOURCE           INT_MSCAN2
#define  CAN3_INT_SOURCE           INT_MSCAN3
#define  CAN4_INT_SOURCE           INT_MSCAN4

typedef  struct 
{
    unsigned long  id;                     
    unsigned char  length;
    unsigned char  mode;
    unsigned char  data[8];               
    
} canbuff_t;



static 	canbuff_t  		        CANRxBuf0;    
static 	canbuff_t  		        CANRxBuf1;
static 	canbuff_t  		        CANRxBuf2;
static 	canbuff_t  		        CANRxBuf3;

static 	canbuff_t  		        CANTxBuf0[CAN_SEND_BUF_LEN];
static 	unsigned short 			bCANTxBufHead0;
static 	unsigned short   		bCANTxBufTail0;

static 	canbuff_t  		        CANTxBuf1[CAN_SEND_BUF_LEN];
static 	unsigned short 			bCANTxBufHead1;
static 	unsigned short   		bCANTxBufTail1;

static 	canbuff_t  		        CANTxBuf2[CAN_SEND_BUF_LEN];	
static 	unsigned short 			bCANTxBufHead2;					
static 	unsigned short   		bCANTxBufTail2;					

static 	canbuff_t  		        CANTxBuf3[CAN_SEND_BUF_LEN];
static 	unsigned short 			bCANTxBufHead3;
static 	unsigned short   		bCANTxBufTail3;


void InitMsCAN(unsigned char canChannalNum,unsigned char canBaudRate);
void MsCANIntInit(unsigned char canChannalNum,unsigned char mode);
unsigned short MsCANSend( unsigned char canChannalNum, canbuff_t *ps_Buffer);
unsigned short MsCANSendOneMsg(unsigned char canChannalNum);
void MsCANRevOneMsg(unsigned char canChannalNum);
void MsCANInterruptHandler(unsigned char canChannalNum);

#endif