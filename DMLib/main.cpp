#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <future>
#include <bitset>
#include <cmath>

#include "DMLib.h"
// #include "DMLib_PESolutions.h"
// using namespace DMLib;
using namespace DMLib;

void TestSwapVals();

extern "C" int GetValueFromASM();

using std::cout;
using std::cerr;
using std::cin;
using std::endl;

int main() {
	// PrintDatatypeSizes();
	std::cout << "### BEGIN MAIN #########################################" << std::endl << std::endl;

	//CompareRuntimes(Problem_100_alt, Problem_100_alt);

	std::cout << std::endl << "### END MAIN #########################################" << std::endl << std::endl;

	// CompareRuntimes(ProjectEulerSolutions::Problem_100, ProjectEulerSolutions::Problem_100_alt);

	Problem_1();

	return 0;
}