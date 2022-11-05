#include <iostream>
#include "Courses.h"

// __courses

int main()
{
	try {
		__courses::CheckCourse c("Engineering", "Computers", true, false, true, true);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}