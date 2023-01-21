
#include <stdio.h>
#include <cstdint>
#include <iostream>
#include <windows.h>

uint8_t xScreenLoc = 10;
uint8_t yScreenLoc = 10;

class data{
public:
	data() = default;
	data(const char * str){
		m_Size = sizeof(str);
		m_Data = new char[m_Size];
		memcpy(m_Data, str, m_Size);
	}
	data(const data& other){
		m_Size = other.m_Size;
		m_Data = new char[m_Size];
		memcpy(m_Data, other.m_Data, m_Size);
	}
	data(data&& other) noexcept{
		delete[] m_Data;

		m_Size = other.m_Size;
		m_Data = other.m_Data;

		m_Size = 0;
		m_Data = nullptr;
	}
	data& operator=(data&& other) noexcept{
		if(this != &other){
			delete[] m_Data;

			m_Size = other.m_Size;
			m_Data = other.m_Data;

			m_Size = 0;
			m_Data = nullptr;
		}

		return *this;
	}
	virtual void print() const{
		for(int iterator=0; iterator<m_Size; ++iterator)
			{printf("%c", m_Data[iterator]);}
	}
	inline void GetConsoleScreenLocation(const uint8_t& x, const uint8_t& y){
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD CursorPosition;

		CursorPosition.X = (uint8_t&&)x;
		CursorPosition.Y = (uint8_t&&)y;
		SetConsoleCursorPosition(console, CursorPosition);
	}
	bool hexcheck(data&& m_hex){
		uint8_t s=0;
		for(uint8_t i=1; i<m_hex.size(); ++i){
			s += (uint8_t)m_hex.m_Data[i]>=65 && (uint8_t)m_hex.m_Data[i]<=70 
			  || (uint8_t)m_hex.m_Data[i]>=97 && (uint8_t)m_hex.m_Data[i]<=102
			  || (uint8_t)m_hex.m_Data[i]>=48 && (uint8_t)m_hex.m_Data[i]<=57
			  ? 1 : 0;

			GetConsoleScreenLocation(xScreenLoc, yScreenLoc + (m_hex.size() + 4) + i);  
			printf("(uint8_t)m_hex.m_Data[%d] = %d\n", i, (uint8_t)m_hex.m_Data[i]);

				 if((uint8_t)m_hex.m_Data[i]<=65 && (uint8_t)m_hex.m_Data[i]>=70) printf("\n\tERROR: hexcodes only take capital letters from A - F, character found: %c", m_hex.m_Data[i]);
			else if((uint8_t)m_hex.m_Data[i]<=97 && (uint8_t)m_hex.m_Data[i]>=102)printf("\n\tERROR: hexcodes only take letters from a - f, character found: %c", m_hex.m_Data[i]);
			else if((uint8_t)m_hex.m_Data[i]<=48 && (uint8_t)m_hex.m_Data[i]>=57) printf("\n\tERROR: hexcodes only take numbers from 0 - 9, number found: %c", m_hex.m_Data[i]);
		}
		if(m_hex.m_Data[0]!='#') printf("\nERROR: hexcode started with %c!", m_hex.m_Data[0]);
		if((m_hex.size() - 2) !=6) printf("\nERROR: hexcodes are 6 characters long after the # symbol");
		printf("\nm_Data[0][%c], size[%d], s[%d]", m_hex.m_Data[0], m_hex.size(), s);
		return m_hex.m_Data[0]=='#' && (m_hex.size() - 2)==6 && s==6 ? true : false;
	}
	virtual uint32_t size(){return m_Size;}
	~data(){delete[] m_Data;}

	uint32_t m_Size;
	char * m_Data;
};

#define GetInsertKey while(1){if(GetAsyncKeyState(VK_INSERT & 0x2D)) break;}

inline void box(uint8_t dim, data&& other){
	char m_boxC;
	for(uint8_t x=0; x<=dim; ++x){
		other.GetConsoleScreenLocation(xScreenLoc, yScreenLoc + x);
		for(uint8_t y=0; y<=dim; ++y){
			m_boxC = x!=0 && x!=dim && y!=0 && y!=dim ? ' ' : '#';
			printf("%c ", m_boxC);
		}
		printf("\n");
	}
	other.GetConsoleScreenLocation(xScreenLoc + 2, yScreenLoc + (other.m_Size>>1));
	other.print();
	printf("\n\n");
}

int main(int s, char * z[]){
	unsigned char key = ' ';
	unsigned char SelectorIcon = '*';
	uint8_t sl = 3;
	bool running = true;
	uint8_t iterator=0;

	while(running){
		key=GetAsyncKeyState(VK_LEFT  & 0x25) ? key = 'L'
		:	GetAsyncKeyState(VK_UP    & 0x26) ? key = 'U'
		:	GetAsyncKeyState(VK_RIGHT & 0x27) ? key = 'R'
		:	GetAsyncKeyState(VK_DOWN  & 0x28) ? key = 'D'
		:	GetAsyncKeyState(VK_INSERT& 0x2D) ? key = 'I'
		:	key = ' ';

		data m_hex = "#000000";

		if(m_hex.hexcheck((data&&)m_hex)){
			printf("\nHexcode accepted");
		}
		else{
			printf("\nHexcode not accepted");
		}

		box(m_hex.m_Size, (data&&)m_hex);
		m_hex.GetConsoleScreenLocation(xScreenLoc + sl, yScreenLoc + (m_hex.m_Size>>1) - 1);
		
		switch(key){
			case 'I': running = false; break;
			case 'L': 
				--sl; if((xScreenLoc + sl) - 1 < (xScreenLoc + 3)) sl = 3;
				--iterator; if((iterator - 1) < 1) iterator = 1; 
				system("cls"); break;
			case 'R': 
				++sl; if((xScreenLoc + sl) + 1 > (xScreenLoc + 8)) sl = 8;
				++iterator; if((iterator + 1) == m_hex.m_Size) iterator = m_hex.m_Size - 1; 
				system("cls"); break;
			case 'U': (uint8_t)m_hex.m_Data[iterator]++; break;
			case 'D': (uint8_t)m_hex.m_Data[iterator]--; break;
		}
				
		printf("%c", SelectorIcon);
	}
		GetInsertKey;
	return 0;
}