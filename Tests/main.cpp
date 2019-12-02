#include <iostream>
#include <bitset>
#include <thread>

//void PORTB(unsigned char inter)
//{
//	std::cout << std::bitset<sizeof inter * 8>(inter) << '\n';
//}
//
//unsigned char PINK()
//{
//	std::string buf;
//	std::cin >> buf;
//	return std::bitset<sizeof(unsigned char) * 8>(buf).to_ulong();
//}

void delay_ms(unsigned int time)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(time));
}

unsigned char DDRB;
unsigned char DDRK;
unsigned char PORTB = 0;
unsigned char PINK = 0b1111'1101;

using VOID = int;




void				init			(){DDRB=(unsigned char)			0xFF				+						(unsigned char)
0xFF				+(				unsigned						char				)					0xFF+2;		   DDRK=0;
}void				set				(unsigned						char*				var,			  unsigned			char val)
{*var				=				~val;}							int b;				int a;			unsigned					char		     
get(			  unsigned			char*							var)				{return		   ~*var;							00;
}void execution(unsigned			int i){x:if(i++>2)return		;set				(&			  PORTB,							get(&			   
PINK)				+ 2);			0;								0;					0;				delay_ms					  (10);			
execution			(i);			if								(i					--<				  2)goto					  x;}								
void				loop			(){								0;					0;					 execution(0);		   }VOID			
main				()				{void							(*a)				();						a = init;		0;0;a
();a=				loop			;a();7;7;7;7;00000000;			0;}void ass()		{return;}void			   coolkidsclub(){}