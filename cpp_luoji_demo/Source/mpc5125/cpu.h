
#ifndef __CPU_H__     
#define __CPU_H__  

   STK_FRM_SZ    .equ     432           #/* 32 gpr + 8 spr + sp + 32 fp + fpcr -> (41 * 4 + 32 * 8 + 4 ) */
   XTR_REG_OFFS  .equ     396           #/* (33 * 4) + (32 * 8) + 4 + 4 fill */
   R0_OFFS       .equ     8
   R2_OFFS       .equ     12
   XF0     .equ    136
   XF1     .equ    XF0+8
   XF2     .equ    XF1+8
   XF3     .equ    XF2+8
   XF4     .equ    XF3+8
   XF5     .equ    XF4+8
   XF6     .equ    XF5+8
   XF7     .equ    XF6+8
   XF8     .equ    XF7+8
   XF9     .equ    XF8+8
   XF10    .equ    XF9+8
   XF11    .equ    XF10+8
   XF12    .equ    XF11+8
   XF13    .equ    XF12+8
   XF14    .equ    XF13+8
   XF15    .equ    XF14+8
   XF16    .equ    XF15+8
   XF17    .equ    XF16+8
   XF18    .equ    XF17+8
   XF19    .equ    XF18+8
   XF20    .equ    XF19+8
   XF21    .equ    XF20+8
   XF22    .equ    XF21+8
   XF23    .equ    XF22+8
   XF24    .equ    XF23+8
   XF25    .equ    XF24+8
   XF26    .equ    XF25+8
   XF27    .equ    XF26+8
   XF28    .equ    XF27+8
   XF29    .equ    XF28+8
   XF30    .equ    XF29+8
   XF31    .equ    XF30+8
   XFPSCR  .equ    XF31+8
  

prologue:       .macro

   mtspr        272,r0                  # backup r0 register
   mfmsr        r0                      #
   ori          r0, r0, 0x30            # turn on data translation  
   mtmsr        r0                      #
   isync
   mfspr        r0,272                  # get back original r0

   stwu         r1,-STK_FRM_SZ(r1)      # create stack frame
   stw          r0,R0_OFFS(r1)          # save r0
   stmw         r2,R2_OFFS(r1)          # save regs r2 through r31  

   mfmsr       r0
   ori         r0,r0,0x2000
   mtmsr       r0
   isync                                # wait for FPU availability
   stfd        f0,XF0(r1)
   stfd        f1,XF1(r1)
   stfd        f2,XF2(r1)
   stfd        f3,XF3(r1)
   stfd        f4,XF4(r1)
   stfd        f5,XF5(r1)
   stfd        f6,XF6(r1)
   stfd        f7,XF7(r1)
   stfd        f8,XF8(r1)
   stfd        f9,XF9(r1)
   stfd        f10,XF10(r1)
   stfd        f11,XF11(r1)
   stfd        f12,XF12(r1)
   stfd        f13,XF13(r1)
   stfd        f14,XF14(r1)
   stfd        f15,XF15(r1)
   stfd        f16,XF16(r1)
   stfd        f17,XF17(r1)
   stfd        f18,XF18(r1)
   stfd        f19,XF19(r1)
   stfd        f20,XF20(r1)
   stfd        f21,XF21(r1)
   stfd        f22,XF22(r1)
   stfd        f23,XF23(r1)
   stfd        f24,XF24(r1)
   stfd        f25,XF25(r1)
   stfd        f26,XF26(r1)
   stfd        f27,XF27(r1)
   stfd        f28,XF28(r1)
   stfd        f29,XF29(r1)
   stfd        f30,XF30(r1)
   stfd        f31,XF31(r1)
   mffs        f0
   stfd        f0,XFPSCR(r1)

   mflr         r31                     # fetch LR
   mfxer        r30                     # fetch XER
   mfctr        r29                     # fetch CTR
   mfsrr1       r28                     # fetch MSR (from normal interrupt)
   mfsrr0       r27                     # fetch PC  (from normal interrupt)
   mfcr         r26                     # fetch CR
   mfspr        r25, 59				    # fetch CSRR1 (for critical interrupt)
   mfspr        r24, 58				    # fecth CSRR0
   stmw         r24,XTR_REG_OFFS(r1)    # save regs r24 - r31

                .endm      

epilogue:       .macro

   lmw          r24,XTR_REG_OFFS(r1)          
   mtspr        58,r24			       # restore CSRR1 (for critical interrupt)
   mtspr        59,r25				   # restore CSRR0 (for critical interrupt)
   mtcr         r26                    # restore CR
   mtsrr0       r27                    # restore PC
   mtsrr1       r28                    # restore MSR
   mtctr        r29                    # restore CTR
   mtxer        r30                    # restore XER
   mtlr         r31                    # restore LR

   mfmsr        r0
   ori          r0,r0,0x2000
   mtmsr        r0
   lfd          f0,XFPSCR(r1)
   mtfsf        0xFF,f0
   lfd          f0,XF0(r1)
   lfd          f1,XF1(r1)
   lfd          f2,XF2(r1)
   lfd          f3,XF3(r1)
   lfd          f4,XF4(r1)
   lfd          f5,XF5(r1)
   lfd          f6,XF6(r1)
   lfd          f7,XF7(r1)
   lfd          f8,XF8(r1)
   lfd          f9,XF9(r1)
   lfd          f10,XF10(r1)
   lfd          f11,XF11(r1)
   lfd          f12,XF12(r1)
   lfd          f13,XF13(r1)
   lfd          f14,XF14(r1)
   lfd          f15,XF15(r1)
   lfd          f16,XF16(r1)
   lfd          f17,XF17(r1)
   lfd          f18,XF18(r1)
   lfd          f19,XF19(r1)
   lfd          f20,XF20(r1)
   lfd          f21,XF21(r1)
   lfd          f22,XF22(r1)
   lfd          f23,XF23(r1)
   lfd          f24,XF24(r1)
   lfd          f25,XF25(r1)
   lfd          f26,XF26(r1)
   lfd          f27,XF27(r1)
   lfd          f28,XF28(r1)
   lfd          f29,XF29(r1)
   lfd          f30,XF30(r1)
   lfd          f31,XF31(r1)

   lmw          r2,R2_OFFS(r1)         # restore regs r2 through r31
   lwz          r0,R0_OFFS(r1)         # restore r0
   lwz          r1,0(r1)               # restore stack pointer

                .endm      


#endif
