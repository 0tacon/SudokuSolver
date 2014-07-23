/*

Copyright 2014 Daniel Forde

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <windows.h>
#include <iostream>
#include <vector>
#include <string>

#ifndef _PRINTHEADER_
	#include "include/PrintHeader.h"
#endif

#ifndef _CELL_
	#include "include/Cell.h"
#endif

#ifndef _VECTOR_
	#include "include/Vector.h"
#endif

#ifndef _FILE_
	#include "include/File.h"
#endif

#ifndef _PUZZLE_
	#include "include/Puzzle.h"
#endif

using namespace std;

int main()
{
	vector<unsigned int> vect;
	vector<Cell> Cells;
	bool Exit = false, InputValid = false;
	string input, filename;

	unsigned int count;

	PrintHeader();

	while ( !Exit )
	{
		vect = ReadFileIntoVect(filename);

		Cells = CreateCells(vect);

		PrintPuzzle(Cells);

		SolvePuzzle(Cells, filename);

		PrintPuzzle(Cells);

		InputValid = false;
		while ( !InputValid )
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY );
			cout << "\nWould you like to solve another puzzle? (Y/N) > ";
			cin >> input;

			if ( (input == "Y") || (input == "y") )
			{
				Exit = false;
				InputValid = true;
			}
			else if ( (input == "N") || (input == "n") )
			{
				Exit = true;
				InputValid = true;
			}
			else
			{
				cout << "\nIncorrect input, please enter again...\n";
				InputValid = false;
				Exit = false;
			}
		}
	}

	return 0;
}
