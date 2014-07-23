/*

Copyright 2014 Daniel Forde

This file is part of ProjectEuler.

SudokuSolver is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

SudokuSolver is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with SudokuSolver.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#ifndef _CELL_
	#include "Cell.h"
#endif

#define _FILE_

std::vector<unsigned int> ReadFileIntoVect (std::string &filename)
{
	std::fstream file;
	std::vector<unsigned int> vect;
	bool FileReadSuccess = false;
	std::string filepath;

	while ( FileReadSuccess == false )
	{
		std::cout << "\nEnter file name > ";
		std::cin >> filename;
		filepath = "..\\puzzles\\" + filename + ".txt";

		file.open(filepath.c_str(), std::ios::in);

		if ( !file.is_open() )
		{
			file.clear();
			FileReadSuccess = false;
			std::cout << "\nError: file does not exist...\n";
		}
		else FileReadSuccess = true;
	}

	for ( int i = 0 ; i < 9 ; i++ )
	{
		while (file.peek() != '\n')
		{
			vect.push_back((file.get()-48));
			if ( file.peek() == ',' ) file.get();
		}
		file.get();
	}
	file.close();

	return vect;
}

void WriteSolFile (std::vector<Cell> Cells, std::string filename)
{
	std::string filepath;
	std::fstream file;
	unsigned int counter=0;

	CreateDirectory( "..\\puzzles\\solutions\\", NULL );
	filepath = "..\\puzzles\\solutions\\" + filename + "_sol.txt";

	file.open(filepath.c_str());

	while ( !file.is_open() && counter<100 )
	{
		file.clear();
		file.open(filepath, std::ios::out);
   		file.close();
   		file.open(filepath);

		counter++;
	} counter = 0;

	if ( !file.is_open() ) std::cout << "\nError: Unable to save solution to file...\n";
	else
	{
		for ( std::vector<Cell>::iterator Cell = Cells.begin() ; Cell != Cells.end() ; Cell++ )
		{
			counter++;
			file.put( static_cast<unsigned char>(Cell->val.at(0) + 48) );
			if ( counter == 9 )
			{
				file.put('\n');
				counter = 0;
			}
			else file.put(',');
		}
		file.put('\n');
		file.close();
	}
}
