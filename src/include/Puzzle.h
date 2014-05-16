#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>

#ifndef _CELL_
	#include "Cell.h"
#endif

#ifndef _VECTOR_
	#include "Vector.h"
#endif

#ifndef _FILE_
	#include "File.h"
#endif

#define _PUZZLE_

enum category_t { ROW, COL, BLK };

std::vector<Cell> CreateCells (std::vector<unsigned int> vect)
{
	std::vector<Cell> Cells;
	unsigned int count;
	count = 1;
	for ( std::vector<unsigned int>::iterator itr=vect.begin() ; itr!=vect.end() ; itr++)
	{
		Cells.push_back(Cell(*itr,count));
		count++;
	}
	return Cells;
}

void PrintPuzzle (std::vector<Cell> Cells)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY );
	unsigned int n=0;
	std::cout << "\n";
	for ( int i=0 ; i<9 ; i++ )
	{
		for ( int j=0 ; j<9 ; j++ )
		{
			if ( (Cells.at(n)).solved == true ) std::cout << (Cells.at(n)).val.at(0) << " ";
			else std::cout << 0 << " ";
			n++;
		}
		std::cout << "\n";
	}
}

void DiagnosePuzzle (std::vector<Cell> Cells)
{
	bool IDsValid = true, ValsValid = true, SolvedValid = true;
	
	for ( std::vector<Cell>::iterator CurrentCell = Cells.begin() ; CurrentCell != Cells.end() ; CurrentCell++ )
	{
		if ( CurrentCell->id>=80 && CurrentCell->id<=0 ) IDsValid = false;
				
		for ( std::vector<unsigned int>::iterator val = CurrentCell->val.begin() ; val != CurrentCell->val.end() ; val++ )
		{
			if ( *val>=9 && *val<=1 ) ValsValid = false;
		}
		
		if ( CurrentCell->val.size()==1 )
		{
			if ( !CurrentCell->solved ) SolvedValid = false;
		}
		else
		{
			if ( CurrentCell->solved ) SolvedValid = false;
		}
	}
	
	if ( !IDsValid || !ValsValid || !SolvedValid )
	{
		if ( !IDsValid ) std::cout << "\nOne or more cells have invalid IDs\n";
		if ( !ValsValid ) std::cout << "\nOne or more cells contain invalid Values\n";
		if ( !SolvedValid ) std::cout << "\nOne or more cells have incorrect solved statuses\n";
	}
	else std::cout << "\nNo errors were detected within the puzzle\n";
}

unsigned int NumberSolved (std::vector<Cell> Cells)
{
	unsigned int NumSolved=0;
	
	for ( std::vector<Cell>::iterator Cell = Cells.begin() ; Cell != Cells.end() ; Cell++ )
	{
		if ( Cell->solved ) NumSolved++;
	}
	
	return NumSolved;
}

std::vector<unsigned int> GetOtherUnsolvedCells (std::vector<Cell> Cells, unsigned int num, category_t category, unsigned int ID)
{
	std::vector<unsigned int> cellIDs;
	// Analyse every cell
	for ( std::vector<Cell>::iterator CurrentCell = Cells.begin() ; CurrentCell != Cells.end() ; CurrentCell++ )
	{
		if ( category==ROW && !CurrentCell->solved && CurrentCell->y==num && CurrentCell->id!=ID ) cellIDs.push_back(CurrentCell->id);
	 	else if ( category==COL && !CurrentCell->solved && CurrentCell->x==num && CurrentCell->id!=ID ) cellIDs.push_back(CurrentCell->id);
		else if ( category==BLK && !CurrentCell->solved && CurrentCell->blk==num && CurrentCell->id!=ID ) cellIDs.push_back(CurrentCell->id);
	}
	return cellIDs;
}

std::vector<unsigned int> GetSolvedCells (std::vector<Cell> Cells, unsigned int ID)
{
	std::vector<unsigned int> cellIDs;
	// Analyse every cell
	for ( std::vector<Cell>::iterator CurrentCell = Cells.begin() ; CurrentCell != Cells.end() ; CurrentCell++ )
	{
		if ( CurrentCell->solved && ( CurrentCell->y==Cells.at(ID).y || CurrentCell->x==Cells.at(ID).x || CurrentCell->blk==Cells.at(ID).blk ) ) cellIDs.push_back(CurrentCell->id);
	}
	return cellIDs;
}

std::vector<unsigned int> GetAllPossibleValues ( std::vector<Cell> Cells, std::vector<unsigned int> cellIDs )
{
	std::vector<unsigned int> possibleValues;
	// Compare to every other cell
	for ( std::vector<Cell>::iterator OtherCell = Cells.begin() ; OtherCell != Cells.end() ; OtherCell++ )
	{
		// If the other cell is one of those in the cellIDs list
		if ( IsInVect( cellIDs, OtherCell->id ) )
		{
			// Add all of the other cells possible values to the possible values list
			for ( std::vector<unsigned int>::iterator OtherCellValue=OtherCell->val.begin() ; OtherCellValue!=OtherCell->val.end() ; OtherCellValue++ )
			{
				possibleValues.push_back(*OtherCellValue);
			}
		}
	}
	return possibleValues;
}

bool SolveCellIfUnityPossibleValFreq ( Cell* CurrentCell, std::vector<unsigned int> possibleValues )
{
	std::vector<unsigned int>::iterator CurrentCellValue;
	// Examine each of the current cell's possible values until one is found that does not occur in the possible values list,
	// or until all values have been checked
	CurrentCellValue=CurrentCell->val.begin();
	while ( IsInVect(possibleValues, *CurrentCellValue) && CurrentCellValue!=CurrentCell->val.end() ) CurrentCellValue++;
	// If a non-occurring value was found, then the current cell must be equal to this value
	if ( CurrentCellValue!=CurrentCell->val.end() )
	{
		CurrentCell->val.clear();
		CurrentCell->val.push_back(*CurrentCellValue);
		CurrentCell->solved = true;
		return true;
	}
	else return false;
}

bool PotentialValueFrequencyAnalysis ( std::vector<Cell> &Cells, unsigned int &count, category_t category )
{
	std::vector<unsigned int> cellIDs, possibleValues;
	Cell* CurrentCell = &Cells.at(0);
	
	for ( unsigned int i=0 ; i<Cells.size() ; i++ )
	{
		CurrentCell = &Cells.at(i);
		
		if ( !CurrentCell->solved )
		{
			if ( category==BLK ) cellIDs = GetOtherUnsolvedCells (Cells, CurrentCell->blk, category, CurrentCell->id);
			else if ( category==ROW ) cellIDs = GetOtherUnsolvedCells (Cells, CurrentCell->y, category, CurrentCell->id);
			else if ( category==COL ) cellIDs = GetOtherUnsolvedCells (Cells, CurrentCell->x, category, CurrentCell->id);
			
			possibleValues = GetAllPossibleValues ( Cells, cellIDs );
			
			if ( SolveCellIfUnityPossibleValFreq ( CurrentCell, possibleValues ) )
			{
				cellIDs.clear();
				possibleValues.clear();
				return true;
			}
			
			cellIDs.clear();
			possibleValues.clear();
		}
	}
	return false;
}

void PossibleValueElimination (std::vector<Cell> &Cells, unsigned int &count)
{
	std::vector<unsigned int> cellIDs;
	std::vector<unsigned int>::iterator possibleVals;
	bool potentialValRemoval = true;
	
	while ( potentialValRemoval )
	{
		potentialValRemoval = false;
		// Analyse every cell
		for ( std::vector<Cell>::iterator CurrentCell = Cells.begin() ; CurrentCell != Cells.end() ; CurrentCell++ )
		{
			// If the current cell hasn't already been solved
			if ( !(CurrentCell->solved) )
			{
				cellIDs = GetSolvedCells (Cells, CurrentCell->id);
				
				for ( std::vector<unsigned int>::iterator id = cellIDs.begin() ; id != cellIDs.end() ; id++ )
				{
					// Remove the other cell's value from the current cell's possible values
					possibleVals = CurrentCell->val.begin();
					while ( ( *possibleVals != Cells.at(*id).val.at(0) ) && ( possibleVals != CurrentCell->val.end() ) ) possibleVals++;
					if ( possibleVals != CurrentCell->val.end() ) 
					{
						CurrentCell->val.erase(possibleVals);
						potentialValRemoval = true;
					}
					if ( CurrentCell->val.size() == 1 ) CurrentCell->solved = true;
				}
				
				count++;
			}
		}
	}
}

void SolvePuzzle (std::vector<Cell> &Cells, std::string filename)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY );
	unsigned int prevNumSolved=0, newNumSolved=1, originalNumSolved = NumberSolved (Cells), algorithmCount=0, cellAnalysisCount=0, id=0, val=0;
	std::chrono::time_point<std::chrono::system_clock> start, end;
	bool potentialValRemoval = true;
	
	std::cout << "\n" << originalNumSolved << " cells have given values\n";
	
	start = std::chrono::system_clock::now();
	
	// Continue as long as cells are being solved
	while ( newNumSolved>prevNumSolved && NumberSolved(Cells)!=81 )
	{
		prevNumSolved = NumberSolved (Cells);		
		
		PossibleValueElimination (Cells, cellAnalysisCount);
		PotentialValueFrequencyAnalysis (Cells, cellAnalysisCount, BLK);
		PossibleValueElimination (Cells, cellAnalysisCount);
		PotentialValueFrequencyAnalysis (Cells, cellAnalysisCount, ROW);
		PossibleValueElimination (Cells, cellAnalysisCount);
		PotentialValueFrequencyAnalysis (Cells, cellAnalysisCount, COL);
		
		newNumSolved = NumberSolved (Cells);
		algorithmCount++;
	}
	
	end = std::chrono::system_clock::now();
	
	std::cout << "\nAnalysis complete in " << (static_cast<std::chrono::duration<double> >((end-start))).count() << " seconds\n";
	std::cout << "\nThe algorithm executed " << algorithmCount << " times\n";
	std::cout << "\n" << cellAnalysisCount << " individual cell analyses were completed\n";
	std::cout << "\n" << ( NumberSolved(Cells) - originalNumSolved ) << " cells were solved\n";
	if ( NumberSolved(Cells) != 81 )
	{
		std::cout << "\nAnalysis failed " << ( 81-NumberSolved(Cells) ) << " cells couldn't be solved\n";
	}
	else
	{
		std::cout << "\nThe puzzle has been successfully solved\n";
		std::cout << (char)(7);
		WriteSolFile (Cells, filename);		
	}
}
