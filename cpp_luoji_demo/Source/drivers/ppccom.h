#ifndef _PPC_COM_
#define _PPC_COM_

#define  LPC_CLOCK_FREQ  66666666 
#define  IPS_CLOCK_FREQ  66666666 

#define PSC_BASE(n)		(0x80000000 + 0x11000 + 0x100 * (n))

 /* FIFOC configuration registers
 */
#define CFG_FIFO_TX_SIZE	64		/* 4 words, 4*4 bytes */
#define CFG_FIFO_RX_SIZE	64		/* 4 words, 4*4 bytes */ 
#define CFG_FIFO_TX_ADDR	0
#define CFG_FIFO_RX_ADDR	(CFG_FIFO_TX_SIZE + CFG_FIFO_RX_SIZE)

/* Register Offset Base */
#define MPC512X_SFIFO_OFFSET     		0x80011000

/* FIFO Controller */
#define MPC512X_FIFOC_CMD_OFFSET		(MPC512X_SFIFO_OFFSET + 0xf00)                 
#define MPC512X_FIFOC_ISR_OFFSET		(MPC512X_SFIFO_OFFSET + 0xf04) 
#define MPC512X_FIFOC_DMA_REQ_OFFSET	(MPC512X_SFIFO_OFFSET + 0xf08)  
#define MPC512X_FIFOC_DBG_OFFSET		(MPC512X_SFIFO_OFFSET + 0xf10) 

/* FIFOC PSCn offset based on PSCn base address */
#define FIFOC_PSCN_TX_CMD_OFFSET		 	0x80  /**< Command Register for PSC n TX */
#define FIFOC_PSCN_TX_ALARM_OFFSET	 		0x84  /**< Alarm Level for PSC n TX      */
#define FIFOC_PSCN_TX_SR_OFFSET		   		0x88  /**< Status Register for PSC n TX  */
#define FIFOC_PSCN_TX_ISR_OFFSET		 	0x8C  /**< Interrupt Status for PSC n TX */
#define FIFOC_PSCN_TX_IMR_OFFSET 		 	0x90  /**< Interrupt Mask for PSC n TX   */
#define FIFOC_PSCN_TX_COUNT_OFFSET 	 		0x94  /**< FIFO Count for PSC n TX       */
#define FIFOC_PSCN_TX_POINTER_OFFSET 		0x98  /**< FIFO Pointer for PSC n TX     */
#define FIFOC_PSCN_TX_SIZE_OFFSET    		0x9C  /**< FIFO Size for PSC n TX        */
#define FIFOC_PSCN_TX_DATA_OFFSET    		0xBC  /**< FIFO Data for PSC n TX        */

#define FIFOC_PSCN_RX_CMD_OFFSET		 	0xC0  /**< Command Register for PSC n RX */
#define FIFOC_PSCN_RX_ALARM_OFFSET	 		0xC4  /**< Alarm Level for PSC n RX      */
#define FIFOC_PSCN_RX_SR_OFFSET		   		0xC8  /**< Status Register for PSC n RX  */
#define FIFOC_PSCN_RX_ISR_OFFSET		 	0xCC  /**< Interrupt Status for PSC n RX */
#define FIFOC_PSCN_RX_IMR_OFFSET 		 	0xD0  /**< Interrupt Mask for PSC n RX   */
#define FIFOC_PSCN_RX_COUNT_OFFSET 	 		0xD4  /**< FIFO Count for PSC n RX       */
#define FIFOC_PSCN_RX_POINTER_OFFSET 		0xD8  /**< FIFO Pointer for PSC n RX     */
#define FIFOC_PSCN_RX_SIZE_OFFSET    		0xDC  /**< FIFO Size for PSC n RX        */
#define FIFOC_PSCN_RX_DATA_OFFSET    		0xFC  /**< FIFO Data for PSC n RX        */

#define FIFOC_PSCN_CMD_SLICE_EN		0x00000001
#define FIFOC_PSCN_CMD_DMA_EN		0x00000004
#define FIFOC_PSCN_CMD_EOF_EN		0x00000100
#define FIFOC_ENABLE_CLOCK_GATE		0xFFFFFFF1
#define FIFOC_DISABLE_CLOCK_GATE	0xFFFFFFFE
#define FIFOC_PSCN_CMD_SLICE_RST	0x00000080
#define FIFOC_DISABLE_ALL			0x00000000

/* PSC Controller registers */
#define PSC_MR1_OFFSET		0x00 
#define PSC_MR2_OFFSET		0x04 
#define PSC_SR_OFFSET		0x08
#define PSC_CSR_OFFSET		0x0c  
#define PSC_CR_OFFSET       0x10  
#define PSC_RB_TB_OFFSET	0x14 

#define PSC_IPCR_OFFSET 	0x18  
#define PSC_ACR_OFFSET 		0x1c 

#define PSC_ISR_OFFSET  	0x20
#define PSC_IMR_OFFSET  	0x24  
#define PSC_CTUR_OFFSET     0x28 
#define PSC_CTLR_OFFSET     0x2c  
#define PSC_CCR_OFFSET      0x30  

#define PSC_OP1_OFFSET       0x48 

#define PSC_SICR_OFFSET      0x50  

/* DLL/DLM (Divisor Latch) data table (Clock 50MHz) */
#define	DL_1200		((IPS_CLOCK_FREQ/5/(1200)+1)/2)	/*   1200 baud */
#define	DL_2400		((IPS_CLOCK_FREQ/5/(2400)+1)/2)		/*   2400 baud */
#define	DL_4800		((IPS_CLOCK_FREQ/5/(4800)+1)/2)		/*   4800 baud */
#define	DL_9600		((IPS_CLOCK_FREQ/5/(9600)+1)/2)		/*   9600 baud */
#define	DL_19200	((IPS_CLOCK_FREQ/5/(19200)+1)/2)		/*  19200 baud */
#define	DL_38400	((IPS_CLOCK_FREQ/5/(38400)+1)/2)		/*  38400 baud */
#define	DL_57600	((IPS_CLOCK_FREQ/5/(57600)+1)/2)		/*  57600 baud */
#define	DL_115200	((IPS_CLOCK_FREQ/5/(115200)+1)/2)		/* 115200 baud */
#define	DL_230400	((IPS_CLOCK_FREQ/5/(230400)+1)/2)		/* 230400 baud */
#define	DL_460800	((IPS_CLOCK_FREQ/5/(460800)+1)/2)		/* 460800 baud */
#define	DL_921600	((IPS_CLOCK_FREQ/5/(921600)+1)/2)		/* 921600 baud */

#define  COM1           0
#define  COM2           1

#define  COM_PARITY_NONE        0               /*[Defines for setting parity]*/
#define  COM_PARITY_EVEN        1
#define  COM_PARITY_ODD         2

#define  RS232                   0
#define  RS422                   1

 
#define  PPC_ComTxBuffSize 256


#define  COM1_INT_SOURCE           68
#define  COM2_INT_SOURCE           69
#define  COM3_INT_SOURCE           32
#define  COM4_INT_SOURCE           36
#define  COM_INT_SOURCE            40

typedef struct {
    unsigned long   Base;
    unsigned char   Rxhead,Rxtail,RxBuf[256];
    unsigned char   Txhead,Txtail;
    unsigned char   TxBuf[256];
} CommStruc;

extern CommStruc            COM[2];

void PPC_ComInit(unsigned char Port,unsigned long BaudRate,unsigned char ParityMode,unsigned char StopBit,unsigned char Mode); 
unsigned char   PPC_ComIn (unsigned char Port,unsigned char Buf[], unsigned char Len);
unsigned char   PPC_ComOut(unsigned char Port,unsigned char Buf[], unsigned char Len);
unsigned char   PPC_ComRxLen(unsigned char Port);
unsigned char   PPC_ComTxLen(unsigned char Port);
void    PPC_ComEnableInterrupt(unsigned char Port);
void    PPC_ComRxInterruptHandler(unsigned char Port);
void    PPC_ComTxInterruptHandler(unsigned char Port);
void    PPC_ComFifoInterruptHandler(void);

#endif
