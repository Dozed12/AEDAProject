#pragma once


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


class Date {
private:
	unsigned int Day;			//Dia
	unsigned int Month;			//Mes
	unsigned int Year;			//Ano

public:
	Date() {};				//Construtor por omissao da classe Data
	Date(string TheDate);		//Construtor da classe Data (na forma DD/MM/AAAA)
	int getDia() const;					//Funcao que retorna o Dia
	int getMes() const;					//Funcao que retorna o Mes
	int getAno() const;					//Funcao que retorna o Ano
	void setDia(unsigned int NewdDay);		//Funcao que permite modificar o Dia
	void setMes(unsigned int NewMonth);		//Funcao que permite modificar o Mes
	void setAno(unsigned int NewAno);		//Funcao que permite modificar o Ano
	friend ostream& operator<<(ostream& out, const Date & TheDate);		//Funcao que mostra a Data
};