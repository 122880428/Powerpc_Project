#pragma section code_type ".init"

#ifdef __cplusplus
extern "C" {
#endif

asm void __reset(void);
asm void usr_init();
extern void __start();
extern unsigned long gInterruptVectorTable;
extern unsigned long gInterruptVectorTableEnd;
#ifdef __cplusplus
}
#endif


asm void __reset(void)
{
	//
	//   Enable machine check exceptions & floating point
	//
	lis		r3, 0x0000
	ori		r3, r3, 0x3000
	mtmsr	r3
		
	b		__start
} 



asm void usr_init()
{

}
