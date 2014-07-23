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

#include <vector>
#include <algorithm>

#define _VECTOR_

bool IsInVect ( std::vector<unsigned int> vect, unsigned int value )
{
	if ( std::find( vect.begin(), vect.end(), value ) != vect.end() ) return true;
	return false;
}
