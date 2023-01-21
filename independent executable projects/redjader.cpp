
#include <stdio.h>
#include <cstdint>
#include <vector>
#include <iostream>

class string{
public:
	string() = default;
	string(const char* str){
		printf("created");
		m_Size = sizeof(str);       printf("*");
		m_Data = new char[m_Size];  printf("*");
		memcpy(m_Data, str, m_Size);printf("*");
	}
	string(const string& other){
		printf("\ncopy");
		m_Size = other.m_Size;      printf("*");
		m_Data = new char[m_Size];  printf("*");
		memcpy(m_Data, other.m_Data, m_Size);printf("*");
	}
	string(string&& other) noexcept{
		printf("\nmoved");
		m_Size = other.m_Size;
		m_Data = other.m_Data;

		other.m_Size = 0;
		other.m_Data = nullptr;
	}
	void print(){
		printf("\n");
		for(uint32_t i=0; i<m_Size; ++i){
			printf("%c", m_Data[i]);
		}
		printf("\n");
	}
	~string(){delete[] m_Data;}
private:
	uint32_t m_Size;
	char * m_Data;
};

class entity{
public:
	entity(const string& name)
		: m_name(name)
	{}
	entity(string&& name)
		: m_name((string&&)name)
	{}
	void printname(){
		m_name.print();
	}
private:
	string m_name;
};

int main(int s, char * z[]){
	entity e("redjader");
	e.printname();
	std::cin.get();
	return 0;
}