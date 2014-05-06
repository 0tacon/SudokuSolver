#include <vector>
#include <algorithm>

bool IsInVect ( std::vector<unsigned int> vect, unsigned int value )
{
	if ( std::find( vect.begin(), vect.end(), value ) != vect.end() ) return true;
	return false;
}
