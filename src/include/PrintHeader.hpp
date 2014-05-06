#include <windows.h>
#include <iostream>

void PrintHeader (void)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY );
	std::cout << "\n========================================\n";
	std::cout << "=                                      =\n";
	std::cout << "=            Sudoku  Solver            =\n";
	std::cout << "=               1.00.001               =\n";
	std::cout << "=                                      =\n";
	std::cout << "========================================\n";
	std::cout << "=                                      =\n";
	std::cout << "=               06/05/14               =\n";
	std::cout << "=                                      =\n";
	std::cout << "========================================\n";
	std::cout << "=                                      =\n";
	std::cout << "=             Daniel Forde             =\n";
	std::cout << "=                                      =\n";
	std::cout << "========================================\n\n";
}
