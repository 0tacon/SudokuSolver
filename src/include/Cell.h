#include <iostream>
#include <vector>

#define _CELL_

class Cell 
{
	public:
		
		unsigned int x,y,blk, id;
		std::vector<unsigned int> val;
		bool solved;
		
		Cell (unsigned int,unsigned int);
		
		void details ()
		{
			std::cout << "\nCo-ords: (" << x << ", " << y << ")\n";
			
			std::cout << "\nBlock #: " << blk << "\n";
			
			std::cout << "\nID #: " << id << "\n";
			
			if (solved == true) 
			{
				std::cout << "\nSolved: true\n";
				std::cout << "\nValue: ";
			} 
		 	else 
		 	{
		 	std::cout << "\nSolved: false\n";
		 	std::cout << "\nPossible values: ";
		 	}
		 	for ( std::vector<unsigned int>::iterator itr=val.begin() ; itr!=val.end() ; itr++ )
			{
				std::cout << *itr << " ";
			}	std::cout << "\n";
		}
};

Cell::Cell (unsigned int n, unsigned int pos)
{
	if ( n==0 )
	{
		solved = false;
		for ( int i=1; i<10 ; i++ )
		{
			val.push_back(i);
		}
	}
	else
	{
		solved = true;
		val.push_back(n);
	}
	
	id = pos-1;
	
	if ( pos%9 != 0 )
	{
		x = pos%9;
		y = ((pos-(pos%9))/9)+1;
	}
	else
	{
		x = 9;
		y = pos/9;
	}
	
	if ( (1<=x) && (x<=3) )
	{
		if ( (1<=y) && (y<=3) ) blk = 1;
		else if ( (4<=y) && (y<=6) ) blk = 4;
		else blk = 7;
	}
	else if ( (4<=x) && (x<=6) )
	{
		if ( (1<=y) && (y<=3) ) blk = 2;
		else if ( (4<=y) && (y<=6) ) blk = 5;
		else blk = 8;
	}
	else
	{
		if ( (1<=y) && (y<=3) ) blk = 3;
		else if ( (4<=y) && (y<=6) ) blk = 6;
		else blk = 9;
	}
}
