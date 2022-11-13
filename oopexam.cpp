#include <iostream>
#include "Study.h"

// __courses

// TODO before the exam:
// instead of a map, use vector(maybe?)

int main()
{
	using namespace __courses;

	Study uni("John Smith", 2, 3);

	try {
		uni.add(new AveragedCourse("English", "Languages", 4, 5));
		uni.add(new ScoredCourse("Programming", "Computers", 65));
		uni.add(new CheckCourse("Engineering", "Computers", true, false, true, true));
		uni.add(new ScoredCourse("Football", "Sport", 90));
	}
	catch (Study::LimitError& e)
	{
		std::cout << e.what() << std::endl;
	}

	std::cout << uni;

	std::cout << Course::count() << std::endl;
	std::cout << uni.averageGrade() << std::endl;
	uni.remove("English");
	std::cout << Course::count() << std::endl;
	std::cout << uni.averageGrade() << std::endl;

	try {
		std::cout << uni[1].getMark() << std::endl;
		std::cout << uni[5].getMark() << std::endl;
	}
	catch (Study::IndexError& e)
	{
		std::cout << e.what() << std::endl;
	}
	uni.clear();
	std::cout << Course::count() << std::endl;
	return 0;
}