/*
* �ļ����ƣ�5125ADS_init.c
* ժ Ҫ��������һЩ��ϵͳ��ʼ����ص�����
* 
* ��ǰ�汾��1.0
* �� �ߣ���½��18439432431
* ������ڣ�2021 �� 7 �� 14 ��
* �޸����ݣ������˺���ע�ͣ������cpp���������룬��ֲ����c++������ 
*
*/

//�ʣ���̫�����һ�δ��������
#pragma section code_type ".init"

//�ʣ�ʹ��c���﷨�������⼸��������
#ifdef __cplusplus
extern "C" {
#endif

asm void __reset(void);		//��λ
asm void usr_init();		//��ʼ��
extern void __start();		//������mpc5125\_start.c�ļ�����
//�ʣ�����������û���ҵ������ﶨ��ġ�
extern unsigned long gInterruptVectorTable;
extern unsigned long gInterruptVectorTableEnd;

#ifdef __cplusplus
}
#endif


/*
* �������ܣ���λ
* ����ʵ�֣��������ǿ���������ʱ���Ƚ��и��λ
* �����������
* ����ֵ  ����
* ע�������
*/
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

/*
* �������ܣ��û���ʼ��
* ����ʵ�֣��������ڻ�Ϊ��
* �����������
* ����ֵ  ����
* ע�������_ppc_eabi_init.c��__init_hardware�������������
*/
asm void usr_init()
{

}
