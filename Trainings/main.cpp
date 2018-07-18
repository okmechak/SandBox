#include <iostream>
#include "stl_experience.h"
#include "theEulerProject.h"

int main(int argc, char ** argv)
{
	std::cout << "Main" << std::endl;
	vetor_test();

	std::cout << "The Eulear Project" << std::endl;
	std::cout << "sum of all multipliers of 3 and 5 below 10 : " << multipliers_of_5_and_3(10) << std::endl;
	std::cout << "sum of all multipliers of 3 and 5 below 20 : " << multipliers_of_5_and_3(20) << std::endl;
	std::cout << "sum of all multipliers of 3 and 5 below 35 : " << multipliers_of_5_and_3(35) << std::endl;
	std::cout << "sum of all multipliers of 3 and 5 below 1000 : " << multipliers_of_5_and_3(1000) << std::endl;
	std::cout << "#####FAST######" << std::endl;
	std::cout << "sum of all multipliers of 3 and 5 below 10 : " << multipliers_of_5_and_3_fast(10) << std::endl;
	std::cout << "sum of all multipliers of 3 and 5 below 20 : " << multipliers_of_5_and_3_fast(20) << std::endl;
	std::cout << "sum of all multipliers of 3 and 5 below 35 : " << multipliers_of_5_and_3_fast(35) << std::endl;
	std::cout << "sum of all multipliers of 3 and 5 below 1000 : " << multipliers_of_5_and_3_fast(1000) << std::endl;

	return 0;
}