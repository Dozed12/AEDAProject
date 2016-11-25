#include "Tools.h"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <Windows.h>
#include <cstdlib>
#include <string>

using namespace std;


void resize()
{
	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);
	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 785, 600, TRUE);
}

void clearScreen()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	//Get the number of cells in the current buffer 
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	// Fill the entire buffer with spaces
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	// Fill the entire buffer with the current colors and attributes 
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	// Move the cursor home 
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

unsigned short int ReadUnsignedShortInt(unsigned short int min, unsigned short int max)
{
	bool BoolOption = true;
	unsigned short int Option;
	while (BoolOption == true)			//Ciclo: enquanto o booleano escolhaBool estiver a true, a opcao nao e valida. O ciclo e, portanto, repetido
	{
		cin >> Option;
		while (cin.fail())				//Ciclo: se o input for diferente do tipo declarado, neste caso unsigned short int, é assumido como fail, mostrando
		{								//uma mensagem de erro, limpando o buffer de input e voltando a pedir um novo unsigned short int
			cout << "Opcao invalida. Por favor insira um numero valido." << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cin >> Option;
		}
		if (Option < min || Option >max)
		{
			cout << "Opcao invalida. Por favor insira um numero valido.";
		}
		else BoolOption = false;				//Se a variavel escolha for valida, alterar o booleano escolhaBool para que se possa sair do ciclo
	}
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	return Option;
}