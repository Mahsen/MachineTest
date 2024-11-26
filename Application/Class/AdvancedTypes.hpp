#ifndef __ADVANCEDTYPES_HPP
#define __ADVANCEDTYPES_HPP
//----------------------------------------------------------
#include "../Core/Defines.hpp"
//----------------------------------------------------------
/// ساختار متغير 64 بيتي سبک
//{
struct struct_volatile_ValueDouble
{
	volatile double ValueDouble; 
	void Set(double Value)
	{
		ValueDouble = Value;
	}
	double Get(void)
	{
		return ValueDouble;
	}
	void Increase(void)
	{
		ValueDouble++;
	}
	void Decrease(void)
	{
		ValueDouble--;
	}
	void Add(double Value)
	{
		ValueDouble += Value;
	}
	void Sub(double Value)
	{
		ValueDouble -= Value;
	}
	void Div(double Value)
	{
		ValueDouble /= Value;
	}
	void Mol(double Value)
	{
		ValueDouble *= Value;
	}
	void Reset(void)
	{
		Set(0);
	}
	bool IsValid(void)
	{
		return true;
	}
};
//}
/// ساختار متغير 64 بيتي 
//{
struct struct_ValueDouble
{
	double ValueDouble; 
	void Set(double Value)
	{
		ValueDouble = Value;
	}
	double Get(void)
	{
		return ValueDouble;
	}
	void Increase(void)
	{
		ValueDouble++;
	}
	void Decrease(void)
	{
		ValueDouble--;
	}
	void Add(double Value)
	{
		ValueDouble += Value;
	}
	void Sub(double Value)
	{
		ValueDouble -= Value;
	}
	void Div(double Value)
	{
		ValueDouble /= Value;
	}
	void Mol(double Value)
	{
		ValueDouble *= Value;
	}
	void Reset(void)
	{
		Set(0);
	}
	bool IsValid(void)
	{
		return true;
	}
};
//}
/// ساختار متغير 64 بيتي 
//{
struct struct_ValueU64
{
	unsigned long long ValueU64; 
	void Set(unsigned long long Value)
	{
		ValueU64 = Value;
	}
	unsigned long long Get(void)
	{
		return ValueU64;
	}
	void Increase(void)
	{
		ValueU64++;
	}
	void Decrease(void)
	{
		ValueU64--;
	}
	void Add(unsigned long long Value)
	{
		ValueU64 += Value;
	}
	void Sub(unsigned long long Value)
	{
		ValueU64 -= Value;
	}
	void Div(unsigned long long Value)
	{
		ValueU64 /= Value;
	}
	void Mol(unsigned long long Value)
	{
		ValueU64 *= Value;
	}
	void Reset(void)
	{
		Set(0);
	}
};
//}
/// ساختار متغير 32 بيتي 
//{
struct struct_ValueU32
{
	unsigned int ValueU32; 
	void Set(unsigned int Value)
	{
		ValueU32 = Value;
	}
	unsigned int Get(void)
	{
		return ValueU32;
	}
	void Increase(void)
	{
		ValueU32++;
	}
	void Decrease(void)
	{
		ValueU32--;
	}
	void Add(unsigned int Value)
	{
		ValueU32 += Value;
	}
	void Sub(unsigned int Value)
	{
		ValueU32 -= Value;
	}
	void Div(unsigned int Value)
	{
		ValueU32 /= Value;
	}
	void Mol(unsigned int Value)
	{
		ValueU32 *= Value;
	}
	void Reset(void)
	{
		Set(0);
	}
};
//}
/// ساختار متغير 32 بيتي علامت دار
//{
struct struct_ValueS32
{
	int ValueS32; 
	void Set(int Value)
	{
		ValueS32 = Value;
	}
	int Get(void)
	{
		return ValueS32;
	}
	void Increase(void)
	{
		ValueS32++;
	}
	void Decrease(void)
	{
		ValueS32--;
	}
	void Add(int Value)
	{
		ValueS32 += Value;
	}
	void Sub(int Value)
	{
		ValueS32 -= Value;
	}
	void Div(int Value)
	{
		ValueS32 /= Value;
	}
	void Mol(int Value)
	{
		ValueS32 *= Value;
	}
	void Reset(void)
	{
		Set(0);
	}
};
//}
/// ساختار متغير 16 بيتي 
//{
struct struct_ValueU16
{
	unsigned short ValueU16; 
	void Set(unsigned short Value)
	{
		ValueU16 = Value;
	}
	unsigned short Get(void)
	{
		return ValueU16;
	}
	void Increase(void)
	{
		Set(ValueU16 + 1);
	}
	void Decrease(void)
	{
		Set(ValueU16 - 1);
	}
	void Add(unsigned short Value)
	{
		Set(ValueU16 + Value);
	}
	void Sub(unsigned short Value)
	{
		Set(ValueU16 - Value);
	}
	void Div(unsigned short Value)
	{
		Set(ValueU16 / Value);
	}
	void Mol(unsigned short Value)
	{
		Set(ValueU16 * Value);
	}
	void Reset(void)
	{
		Set(0);
	}
};
//}
/// ساختار متغير 8 بيتي 
//{
struct struct_ValueU8
{
	unsigned char ValueU8; 
	void Set(unsigned char Value)
	{
		ValueU8 = Value;
	}
	unsigned char Get(void)
	{
		return ValueU8;
	}
	void Increase(void)
	{
		ValueU8++;
	}
	void Decrease(void)
	{
		ValueU8--;
	}
	void Add(unsigned char Value)
	{
		ValueU8 += Value;
	}
	void Sub(unsigned char Value)
	{
		ValueU8 -= Value;
	}
	void Div(unsigned char Value)
	{
		ValueU8 /= Value;
	}
	void Mol(unsigned char Value)
	{
		ValueU8 *= Value;
	}
	void Reset(void)
	{
		Set(0);
	}
};
//}
/// ساختار متغير 1 بيتي سبک
//{
struct struct_volatile_ValueBool
{
	volatile unsigned int ValueBool; 
	void Set(volatile bool Value)
	{
		ValueBool = Value?0x00000001:0x00000000;
	}
	bool Get(void)
	{
		return (ValueBool==0x00000001);
	}
	void Enable(void)
	{
		Set(true);
	}
	void Disable(void)
	{
		Set(false);
	}
	void Reset(void)
	{
		Disable();
	}
	void Toggle(void)
	{
		Set(!ValueBool);
	}
	bool IsValid(void)
	{
		return (ValueBool==0x00000001) || (ValueBool==0x00000000);
	}
};
//}
/// ساختار متغير 1 بيتي 
//{
struct struct_ValueBool
{
	unsigned int ValueBool; 
	void Set(bool Value)
	{
		ValueBool = Value?0x00000001:0x00000000;
	}
	bool Get(void)
	{
		return (ValueBool==0x00000001);
	}
	void Enable(void)
	{
		Set(true);
	}
	void Disable(void)
	{
		Set(false);
	}
	void Reset(void)
	{
		Disable();
	}
	void Toggle(void)
	{
		Set(!ValueBool);
	}
	bool IsValid(void)
	{
		return (ValueBool==0x00000001) || (ValueBool==0x00000000);
	}
};
//}
/// ساختار متغير آرايه اي تمليت
//{
template <int Size, typename Type=unsigned char>  
class class_Array
{
	public:
		
		Type Data[Size]; 
		unsigned short Data_Length;
	
		void Add(Type* Value, unsigned short Length)
		{
			memcpy(&Data[Data_Length], Value, Length);
			Data_Length += Length;
		}
		void Set(Type* Value, unsigned short Length)
		{
			memcpy(Data, Value, Length);
			Data_Length = Length;
		}
		Type* Get(void)
		{
			return Data;
		}
		unsigned short Length(void)
		{
			return Data_Length;
		}
		void Reset(void)
		{
			memset(Data, 0, sizeof(Data));
			Data_Length = 0;
		}
};
//}
/// ساختار متغير رشته کاراکتر
//{
template <int Size>  
class class_String
{
	public:
		
		unsigned char Data[Size]; 
	
		void Set(unsigned char* Value)
		{
			strcpy((char*)Data, (char*)Value);
		}
                void Set(unsigned char* Value, int Length)
		{
			strncpy((char*)Data, (char*)Value, Length);
		}
		unsigned char* Get(void)
		{
			return Data;
		}
		unsigned short Length(void)
		{
			return strlen((char*)Data);
		}
		void Reset(void)
		{
			memset(Data, NULL, Size);
		}
};
//}
//----------------------------------------------------------
#endif
