#ifndef __INCppc5125Intrh
#define __INCppc5125Intrh



#define IPIC_ADDR   0x80000C00

typedef int 		(*FUNCPTR) ();	   /* ptr to function returning int */
typedef void 		(*VOIDFUNCPTR) (int); /* ptr to function returning void */
typedef double 		(*DBLFUNCPTR) ();  /* ptr to function returning double*/
typedef float 		(*FLTFUNCPTR) ();  /* ptr to function returning float */

/* interrupt number definitions */
#define INT_NULL		0	/* level 0 interrupt */
#define INT_GPT10d		1	/* level 1 interrupt */
#define INT_GPT11		2	/* level 2 interrupt */
#define INT_SDHC2		3	/* level 3 interrupt */
#define INT_FEC1		4	/* level 4 interrupt */
#define INT_FEC2		5	/* level 5 interrupt */
#define INT_NFC  		6	/* level 6 interrupt */
#define INT_LPC 		7	/* level 7 interrupt */
#define INT_SDHC1		8	/* level 8 interrupt */
#define INT_I2C1		9	/* level 9 interrupt */
#define INT_I2C2		10	/* level 10 interrupt */
#define INT_I2C3		11	/* level 11 interrupt */
#define INT_MSCAN1		12	/* level 12 interrupt */
#define INT_MSCAN2		13	/* level 13 interrupt */
#define INT_BDLC		14	/* level 14 interrupt */
#define INT_GPT0		15	/* level 15 interrupt */
#define INT_GPT1		16	/* level 16 interrupt */
#define INT_IRQ1		17	/* level 17 interrupt */

#define INT_PSC4		32	/* level 32 interrupt */
#define INT_PSC5		33	/* level 33 interrupt */
#define INT_PSC6		34	/* level 34 interrupt */
#define INT_PSC7		35	/* level 35 interrupt */
#define INT_PSC8		36	/* level 36 interrupt */
#define INT_PSC9		37	/* level 37 interrupt */
#define INT_GPT8		38	/* level 38 interrupt */
#define INT_GPT9		39	/* level 39 interrupt */
#define INT_FIFOC		40	/* level 40 interrupt */

#define INT_USB2OTG1 	43	/* level 43 interrupt */
#define INT_USB2OTG2	44	/* level 44 interrupt */

#define INT_IRQ0	    48	/* level 48 interrupt */

#define INT_DIU	    	64	/* level 64 interrupt */
#define INT_DMA2		65	/* level 65 interrupt */

#define INT_PSC0 		68	/* level 68 interrupt */
#define INT_PSC1 		69	/* level 69 interrupt */
#define INT_PSC2 		70	/* level 70 interrupt */
#define INT_PSC3 		71	/* level 71 interrupt */
#define INT_GPT2 		72	/* level 72 interrupt */
#define INT_GPT3 		73	/* level 73 interrupt */
#define INT_GPT4 		74	/* level 74 interrupt */
#define INT_GPT5 		75	/* level 75 interrupt */
#define INT_GPT6 		76	/* level 76 interrupt */
#define INT_GPT7		77	/* level 77 interrupt */
#define INT_GPIO1		78	/* level 78 interrupt */
#define INT_RTC_SEC 	79	/* level 79 interrupt */
#define INT_RTC_ALARM 	80	/* level 80 interrupt */
#define INT_DDR	    	81	/* level 81 interrupt */
#define INT_SBA		    82	/* level 82 interrupt */
#define INT_PMC		    83	/* level 83 interrupt */
#define INT_USB2OTG1W	84	/* level 84 interrupt */
#define INT_USB2OTG2W	85	/* level 85 interrupt */
#define INT_GPIO2		86	/* level 86 interrupt */
#define INT_TEMP		87	/* level 87 interrupt */
#define INT_IIM		    88	/* level 88 interrupt */
#define INT_PRIOMON		89	/* level 89 interrupt */
#define INT_MSCAN3 		90	/* level 90 interrupt */
#define INT_MSCAN4 		91	/* level 91 interrupt */
#define INT_GPT12 	    92	/* level 92 interrupt */
#define INT_GPT13	    93	/* level 93 interrupt */
#define INT_GPT14		94	/* level 94 interrupt */
#define INT_GPT15		95	/* level 95 interrupt */



#define NUM_VEC_MAX	128

#define PPC5125IPICSICFR        (IPIC_ADDR+0x00)
#define PPC5125IPICSIVCR	    (IPIC_ADDR+0x04)
#define PPC5125IPICSIPNRH       (IPIC_ADDR+0x08)
#define PPC5125IPICSIPNRL       (IPIC_ADDR+0x0C)
#define PPC5125IPICSIPRRA       (IPIC_ADDR+0x10)
#define PPC5125IPICSIPRRB       (IPIC_ADDR+0x14)
#define PPC5125IPICSIPRRC       (IPIC_ADDR+0x18)
#define PPC5125IPICSIPRRD       (IPIC_ADDR+0x1C)
#define PPC5125IPICSIMSRH       (IPIC_ADDR+0x20)
#define PPC5125IPICSIMSRL       (IPIC_ADDR+0x24)
#define	PPC5125IPICSEPNR	    (IPIC_ADDR+0x2C)
#define	PPC5125IPICSEMSR       	(IPIC_ADDR+0x38)



/* typedefs */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct intr_handler
    {
    VOIDFUNCPTR vec;    		/* interrupt vector */
    int         arg;    		/* interrupt handler argument */
    } INTR_HANDLER;


/* forward declarations */

void    intInit(void);
void	ppc5125IntrDemux (void);
int     ppc5125IntConnect (VOIDFUNCPTR *, VOIDFUNCPTR, int);
int	    ppc5125IntEnable (int);
int	    ppc5125IntDisable (int);
void    time_enable(void);
void    int_enable(void);
void    int_disable(void);

#ifdef __cplusplus
}
#endif

#endif /* __INCppc5125Intrh */
