#include "readUtility.h"

#include <string>
#include <iostream>

bool readUtility::safeReadInt(int & valueToRead)
{
	bool success = false;
	std::string input;

	std::cin >> input;

	if(input.length() == 1)
	{
		char c = input.at(0);

		if((c >= '1') && (c <= '4'))
		{
			valueToRead = c - '0';

			success = true;
		}
	}

	return success;
}