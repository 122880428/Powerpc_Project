/*
NVram里面最多存储524288字节，用于存储重要参数和航点
 */
#ifndef AP_PARAM_H_
#define AP_PARAM_H_

#include <stdint.h>
#include "..\..\drivers\nvram.h"

#include "..\..\YN.h"

//皇：这里模版的写法，必须要把函数实现也放在头文件里面，不然它会出错。
//这编译器甚是奇怪。
template <class T>
class AP_Param
{
	//friend void AP_Param_init(void);
private:
	uint8_t type;		//皇：要存储参数的类型，不同的类型会占用不一样的字节
	T _value;		//皇：存储的数值，推荐使用uint8_t，只占用一个字节
	unsigned long _addr; 	//皇：存储地址。所有参数统一分配地址；
public:
	AP_Param(){_addr = 0x00;_addr = 0;type = 0;}		//皇：参数的存储地址必须去注册一下，不然不能进行后续操作
	~AP_Param(){_value = 0;}
	void save();	//皇：将数值保存到NVram里面
	void load();	//皇：从NVram里面读取数值
	void AP_Param_loadall(void);	//皇：加载所有的参数
	void set(T value);		
	void setaddr(unsigned long addr);//{_addr = addr;}
	T get();


	float Read_Float_Param(unsigned long address);
	void Write_Float_Param(float value, unsigned long address);	//这里还会有一个强制转换，需要注意一下

	//static void AP_Param_init(void);//皇：用于初始化所有的默认参数

//皇：尽量不去重载运算符，虽然使用上变得简洁，但更容易出错
    /*AP_Param<T>& operator +(const T v) {
        _value += v;
        return *this;
    }*/

};

/**NVram分为16个区（其实当成一个区用也没区别）
 * 第一组参数有256k个位，也就是32768个字节，理论上可以存储3万多个参数，这啥飞机它也用不完啊。
 * 第一个区就给参数用，绝对够用了，
 * 剩余的给航点用一个区，也没问题。还剩下十几个区，这个以后再说吧
 */
/*class Param_Group
{
	AP_Param _param;
	uint16_t _idx;	//最大65536，>32768
public:
	Param_Group_set(string description, AP_Param param,T value){}
	~Param_Group(){}
	void init();
	
};*/

typedef AP_Param<int8_t>        	AP_Int8;
typedef AP_Param<int16_t>        	AP_Int16;
typedef AP_Param<int32_t>        	AP_Int32;
typedef AP_Param<float>    			AP_Float;

void AP_Param_init(void);


template <class T>
void AP_Param<T>::setaddr(unsigned long addr)
{
	_addr = addr;
}


template <class T>
void AP_Param<T>::AP_Param_loadall(void)
{
	//NVram从0x02处开始存储。
unsigned char i = 0;
for (i = 0; i<16;i++)
    {	
       Sbus::_RC_max[i].load();	
       Sbus::_RC_min[i].load();	
    }
}

/**
 * 
 */
template <class T>
void AP_Param<T>::set(T value)
{
	_value = value;
}



/**
 * 
 */
template <class T>
T AP_Param<T>::get()
{
	return _value;
}

/**
 * 
 */
template <class T>
void AP_Param<T>::save()	//皇：将数值保存到NVram里面
{
	switch(sizeof(T)){
		//皇：尤其注意一下强制转换的事 
		case 2:		NvramWrite(_addr,(unsigned short)_value);	break;	//这是一个无符号int型
		case 4:		Write_Float_Param(_value, _addr);			break;
		default:	printf("save param error!\r\n"); 			break;
	}
}

/**
 * 
 */
template <class T>
void AP_Param<T>::load()	//皇：将数值保存到NVram里面
{
	switch(sizeof(T)){
		case 2:_value = NvramRead(_addr);				break;	//这是一个无符号int型
		case 4:_value = Read_Float_Param(_value);		break;	//浮点数占四个字节
		default:printf("load param error!\r\n"); 	break;
	}
}


/**
 * 
 */
// Utilities for writing and reading from the EEPROM
template <class T>
float AP_Param <class T>::Read_Float_Param(unsigned long address) 
{
	unsigned char i = 0;
  union floatStore {
  	unsigned short floatByte[2];
    float floatVal;
  } floatOut;
  
  for (i = 0; i < 2; i++) 		//这是小端的写法，powerpc是大端，但是读取和写入一致就不会出问题
    floatOut.floatByte[i] = NvramRead(address + i);
  return floatOut.floatVal;
}

/**
 *
 * 
 */
template <class T>
void AP_Param <class T>::Write_Float_Param(float value, unsigned long address) 
{
	unsigned char i = 0;
  union floatStore {
  unsigned short floatByte[2];
    float floatVal;
  } floatIn;
  
  floatIn.floatVal = value;
  for (i = 0; i < 2; i++) 
   	NvramWrite(address + i,floatIn.floatByte[i]);
}


#endif