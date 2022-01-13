// Drayton Monkman, 2022

#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include "DMLib_PESolutions.h"
#include "DMLib_Functions.h"

# define PI           3.14159265358979323846  /* pi */
# define TAU          3.14159265358979323846*2  /* pi */
# define PIl          3.141592653589793238462643383279502884L /* pi */

using std::cout;
using std::endl;
using std::cin;
using std::cerr;

static const uint64_t tenToThe[] = {
	1, 10, 100, 1000, 10000, 100000, 1000000, 10000000,
	100000000, 1000000000, 10000000000, 100000000000, 1000000000000,
	10000000000000, 100000000000000, 1000000000000000, 10000000000000000
};

namespace DMLib {
	namespace PESolutions {

		// I will try to make solutions optimized where possible, however there are many other problems to solve!

		//#########################################################//

		/* PROBLEM 1: Multiples of 3 or 5
			If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.
			Find the sum of all the multiples of 3 or 5 below 1000.
		*/
		int Problem_1() {
			int maxnum = 1000;
			int result = 0;
			int i = 0;
			int j = 0;

			// Iterate through numbers; Avoid divisions for speed
			while (i < maxnum || j < maxnum) {

				// 1. If the numbers are equal, add the number and increment both
				if (i == j) {
					result += i;
					i += 3;
					j += 5;
				}

				// 2. If i > j, add the number j and increment j by 5
				else if (i > j) {
					result += j;
					j += 5;
				}

				// 3. If j > i, add the number i and increment i by 3
				else if (j > i) {
					result += i;
					i += 3;
				}
			}

			return result;
		}

		// Solution using modulus
		int Problem_1_alt() {
			int maxnum = 1000;
			int result = 0;

			// Iterate through numbers. Add multiples of 3 and 5 to result
			for (int i = 3; i < maxnum; i++) {
				if (i % 3 == 0 || i % 5 == 0) {
					result += i;
				}
			}

			return result;
		}

		// ######################################################### //

		/* PROBLEM 2: Even Fibonacci numbers
			Each new term in the Fibonacci sequence is generated by adding the previous two terms. By starting with 1 and 2, the first 10 terms will be:

			1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...

			By considering the terms in the Fibonacci sequence whose values do not exceed four million, find the sum of the even-valued terms.
		*/
		uint64_t Problem_2() {
			// Solution by checking LSB
			int maxnum = 40000000;
			int i = 1, prev = 1;
			int next = i + prev;
			int result = 1;

			while (i < maxnum) {
				if (i & 1) {
					result += i;
				}
				prev = i;
				i = next;
				next = i + prev;
			}
			return result;
		}

		/* PROBLEM 3: Largest prime factor
		The prime factors of 13195 are 5, 7, 13 and 29.

		What is the largest prime factor of the number 600851475143 ?
		*/

		uint64_t Problem_3() {
			uint64_t result = 1;
			uint64_t number = 600851475143;

			// We only need to test up to the sqrt of number
			uint64_t sqrt_number = uint64_t(sqrt(number));

			// Start with 3; only test odd numbers
			for (uint64_t i = 3; i < sqrt_number; i += 2)
			{
				if (!(number % i)) {

					if (Functions::isPrime(i)) {
						//std::cout << i << std::endl;
						result = i;
					}
				}
			}

			return result;
		}

		uint64_t Problem_3_alt() {
			uint64_t result = 1;
			uint64_t number = 600851475143;

			return Functions::findLargestPrimeFactor(number);
		}

		/* PROBLEM 6: Sum square difference
			Explaination: https://projecteuler.net/problem=6
			The sum of the squares of the first ten natural numbers is, 1^2 + 2^2 + ... + 10^2 = 385
			The square of the sum of the first ten natural numbers is, (1 + 2 + ... + 10)^2 = 55^2 = 3025
			Hence the difference between the sum of the squares of the first ten natural numbers and the square of the sum is 3025 - 385 = 2640
			Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.
		*/
		uint64_t Problem_6() {
			uint64_t sumOfNums = 0;
			uint64_t sumOfSquares = 0;
			for (uint64_t i = 1; i <= 100; i++) {
				sumOfNums += i;
				sumOfSquares += i * i;
			}
			return (sumOfNums * sumOfNums) - sumOfSquares;
		}

		/* PROBLEM 7: 10001st prime
			Explaination: https://projecteuler.net/problem=7
			By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.
			What is the 10 001st prime number?
		*/
		uint64_t Problem_7() {
			uint64_t count = 1;
			for (uint64_t i = 3;; i += 2) {
				if (Functions::isPrime(i)) {
					count++;
					if (count == 10001) {
						return i;
					}
				}
			}
		}

		/* PROBLEM 8: Largest product in a series
			Explaination: https://projecteuler.net/problem=8
		*/
		uint64_t Problem_8() {
			char SERIES[] = "73167176531330624919225119674426574742355349194934"
				"96983520312774506326239578318016984801869478851843"
				"85861560789112949495459501737958331952853208805511"
				"12540698747158523863050715693290963295227443043557"
				"66896648950445244523161731856403098711121722383113"
				"62229893423380308135336276614282806444486645238749"
				"30358907296290491560440772390713810515859307960866"
				"70172427121883998797908792274921901699720888093776"
				"65727333001053367881220235421809751254540594752243"
				"52584907711670556013604839586446706324415722155397"
				"53697817977846174064955149290862569321978468622482"
				"83972241375657056057490261407972968652414535100474"
				"82166370484403199890008895243450658541227588666881"
				"16427171479924442928230863465674813919123162824586"
				"17866458359124566529476545682848912883142607690042"
				"24219022671055626321111109370544217506941658960408"
				"07198403850962455444362981230987879927244284909188"
				"84580156166097919133875499200524063689912560717606"
				"05886116467109405077541002256983155200055935729725"
				"71636269561882670428252483600823257530420752963450";

			uint16_t CHAR_SIZE = sizeof(char);
			uint16_t BUFFER_SIZE = 13 * CHAR_SIZE;

			uint64_t largestProd = 0;
			uint64_t currentProd = 1;

			// Iterate string array
			for (char* i = &SERIES[0]; *(i + BUFFER_SIZE) != '\0'; i += CHAR_SIZE) {
				currentProd = 1;
				// std::cout << *i - '0';
				for (char* j = i; j != (i + BUFFER_SIZE); j += CHAR_SIZE) {
					currentProd *= uint64_t((*j) - char('0'));
				}
				if (currentProd > largestProd) {
					largestProd = currentProd;
				}
			}
			return largestProd;
		}

		/* PROBLEM 9: Special Pythagorean triplet
			Explaination: https://projecteuler.net/problem=9
			A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,

			a^2 + b^2 = c^2
			For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2.

			There exists exactly one Pythagorean triplet for which a + b + c = 1000.
			Find the product abc.
		*/
		uint64_t Problem_9() {
			uint64_t squareOf[1001];

			// Create a table of squares to reduce calculations
			for (uint64_t i = 0; i < 1000; i++) {
				squareOf[i] = i * i;
			}

			uint64_t b;
			uint64_t c;

			for (uint64_t a = 10; a < 1000; a++) {
				b = a + 1;
				c = 1000 - a - b;
				while (c > b) {
					if (squareOf[a] + squareOf[b] == squareOf[c]) {
						// std::cout << a << "^2 + " << b << "^2 = " << c << "^2" << std::endl;
						return a * b * c;
					}
					c -= 1;
					b += 1;
				}
				// std::cout << a << std::endl;
				// squareOf[i] = i * i;
			}

			return 0;
		}

		/* PROBLEM 10: Summation of primes
			Explaination: https://projecteuler.net/problem=10
			The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
			Find the sum of all the primes below two million.
		*/
		uint64_t Problem_10() {
			uint64_t sum = 2;
			for (uint64_t i = 3; i < 2'000'000; i++) {
				if (Functions::isPrime(i)) sum += i;
			}
			return sum;
		}

		/* PROBLEM 11: Largest product in a grid
			Explaination: https://projecteuler.net/problem=11
			What is the greatest product of four adjacent numbers in the same direction (up, down, left, right, or diagonally) in the 20�20 grid?
		*/

		uint64_t Problem_11() {
			std::string filename("problem11.txt");
			std::ifstream inputFile(filename);

			// If file does not open, error occured
			if (!inputFile.is_open()) {
				std::cerr << "Could not open the file - '" << filename << "'" << std::endl;
				return EXIT_FAILURE;
			}

			// Read in the array
			std::vector<std::vector<uint64_t>> data;

			for (std::string line; std::getline(inputFile, line); )
			{
				std::stringstream ss(line);
				std::vector<uint64_t> row;
				for (int d; ss >> d; ) {
					row.push_back(d);
					// cout << d << "; ";
				}
				data.push_back(row);
			}

			inputFile.close();

			uint64_t largestProd = 0;
			uint64_t currentProd = 1;

			// Iterate array four times

			// ITERATION 1: HORIZONTAL PRODUCTS
			for (size_t i = 0; i < data.size(); i++) {
				for (size_t j = 0; j < data[i].size() - 3; j++) {
					currentProd = data[i][j] * data[i][j + 1] * data[i][j + 2] * data[i][j + 3];
					if (currentProd > largestProd) {
						largestProd = currentProd;
					}
				}
			}

			// ITERATION 2: DIAGONAL RIGHT SLOPE PRODUCTS
			for (size_t i = 0; i < data.size() - 3; i++) {
				for (size_t j = 0; j < data[i].size() - 3; j++) {
					currentProd = data[i][j] * data[i + 1][j + 1] * data[i + 2][j + 2] * data[i + 3][j + 3];
					if (currentProd > largestProd) {
						largestProd = currentProd;
					}
				}
			}

			// ITERATION 3: DIAGONAL LEFT SLOPE PRODUCTS
			for (size_t i = 3; i < data.size(); i++) {
				for (size_t j = 0; j < data[i].size() - 3; j++) {
					currentProd = data[i][j] * data[i - 1][j + 1] * data[i - 2][j + 2] * data[i - 3][j + 3];
					if (currentProd > largestProd) {
						largestProd = currentProd;
					}
				}
			}

			// ITERATION 4: VERTICLE PRODUCTS
			for (size_t i = 0; i < data.size() - 3; i++) {
				for (size_t j = 0; j < data[i].size(); j++) {
					currentProd = data[i][j] * data[i + 1][j] * data[i + 2][j] * data[i + 3][j];
					if (currentProd > largestProd) {
						largestProd = currentProd;
					}
				}
			}

			return largestProd;
		}


		/* PROBLEM 12: Summation of primes
			Explaination: https://projecteuler.net/problem=12
			The sequence of triangle numbers is generated by adding the natural numbers. So the 7th triangle number would be 1 + 2 + 3 + 4 + 5 + 6 + 7 = 28. The first ten terms would be:

			1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...

			Let us list the factors of the first seven triangle numbers:

			 1: 1
			 3: 1,3
			 6: 1,2,3,6
			10: 1,2,5,10
			15: 1,3,5,15
			21: 1,3,7,21
			28: 1,2,4,7,14,28
			We can see that 28 is the first triangle number to have over five divisors.

			What is the value of the first triangle number to have over five hundred divisors?
		*/

		// O(sqrt(n)) time algorithm
		uint64_t CountDivisors(uint64_t n) {
			uint64_t result = 2;
			for (uint64_t i = 1; i < sqrt(n); i++) {
				if (n % i == 0) {
					result += 2;
				}
			}

			// Consider if n is square number
			if (uint64_t(sqrt(n)) * uint64_t(sqrt(n)) == n) {
				result++;
			}
			return result;
		}

		uint64_t Problem_12() {
			uint64_t triangleNum = 0;
			uint64_t divCount = 0;
			for (uint64_t i = 1;; i++) {
				triangleNum += i;
				divCount = CountDivisors(triangleNum);
				// std::cout << triangleNum << " : " << divCount << std::endl;
				if (divCount > 500) {
					//std::cout << triangleNum << " : " << CountDivisors(triangleNum) << std::endl;
					return triangleNum;
				}
			}
			return 0;
		}

		/* PROBLEM 13: Large Sum
		Explaination: https://projecteuler.net/problem=13
		Work out the first ten digits of the sum of the following one-hundred 50-digit numbers.
		*/
		std::string Problem_13() {
			std::string filename("problem13.txt");
			std::ifstream inputFile(filename);

			// If file does not open, error occured
			if (!inputFile.is_open()) {
				std::cerr << "Could not open the file - '" << filename << "'" << std::endl;
				return "ERROR";
			}

			// Read in the large numbers
			std::vector<std::string> data;

			for (std::string line; std::getline(inputFile, line); )
			{
				data.push_back(line);
			}
			inputFile.close();

			const unsigned short str_width = 60;
			// Pad input strings with zeros to equal result width
			for (auto it = data.begin(); it != data.end(); it++) {
				while ((*it).size() < str_width) {
					(*it).insert(0, "0");
				}
			}

			// Initialize result string; 
			std::string result = "0";
			while (result.size() < str_width) {
				result.push_back('0');
			}

			// Iterate all number strings
			for (int i = 0; i < data.size(); i++) {

				// Iterate all chars in the current string data[i]; starting at the end to account for carry
				auto it = result.end() - 1;
				char carry = 0;
				for (size_t j = data[i].size() - 1; j > 0; j--) {

					// Add strings with respect to zero; this gives us integer value
					char sum_i = ((data[i][j] - '0') + (*it - '0') + (carry));

					// Carry has been emptied
					carry = 0;

					// If carry occurs, handle carry
					if (sum_i > 9) {
						carry = 1;
						sum_i -= 10;
					}

					//// New result of it is the sum
					(*it) = sum_i + '0';
					it--;
				}
			}

			return result;
		}

		/* PROBLEM 15: Lattice paths
			Explaination: https://projecteuler.net/problem=15
			Starting in the top left corner of a 2�2 grid, and only being able to move to the right and down, there are exactly 6 routes to the bottom right corner.
			How many such routes are there through a 20�20 grid?
		*/
		uint64_t Problem_15() {

			/* SOLUTION: For any point along the / diagonal of an n x n grid, the number of paths
					to said point is the same as the kth term of layer n of pascals triangle.
					Ex.
				layer 0:	   1
				layer 1:      1 1		<- paths from the top left (or bottom right) corner to points along the / diagonal of n = 1
				layer 2:	 1 2 1		<- n = 2
				layer 3:	1 3 3 1		<- n = 3
				layer 4:   1 4 6 4 1	<- n = 4
					etc.

				If we sum the squares of all terms along the 21st layer of Pascal's triangle (n paths to * n paths from) we will get the total number of paths
			*/

			// METHOD 1: SUM SQUARES OF ROW 20

			uint64_t result = 0;
			uint64_t nck = 1;		// init as 1 (multiplicitave identity)
			int n = 20;				// n = 20, sidelength of grid

			for (int k = 0; k <= n; k++) {
				nck = Functions::n_choose_k(n, k);
				// std::cout << nck * nck << " ";
				result += nck * nck; // Add the square of each term
			}

			// METHOD 2: FIND THE MIDDLE TERM OF ROW 40 = 20 * 2
			return Functions::n_choose_k(40, 21);

			// std::cout << std::endl;
			return result;
		}

		uint64_t Problem_16() {
			return 0;
		}

		uint64_t Problem_17() {
			return 0;
		}
		/* PROBLEM 20: Factorial Digit sum
			Explaination: https://projecteuler.net/problem=20
		*/
		int Problem_20() {
			int result = 0;

			// Calculate total number 
			//int threesCount = 0;
			//int num = 0;
			//for (int i = 3; i <= 100; i+=3) {
			//	num = i;
			//	std::cout << i;

			//	// Count the number of threes factored from a number
			//	while (num % 3 == 0) {
			//		num /= 3;
			//		threesCount++;
			//	}
			//	std::cout << " : " << threesCount << std::endl;		
			//}

			double logSum = 0;
			for (int i = 2; i <= 100; i++) {
				logSum += log2f(float(i));
			}
			std::cout << logSum << std::endl;

			// BRUTE FORCE METHOD using pre-calculated 100!
			char factorial_100[] = "93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000";
			for (char* i = &factorial_100[0]; *i != '\0'; i += sizeof(char))
				result += (*i - '0');
			return result;
		}

		int Problem_24() {
			uint64_t i = 0;

			while (i < 1'000'000) {

			}
			return 0;

		}

		uint64_t Problem_33() {
			return 0;
		}

		uint64_t Problem_34() {

			for (int i = 1; i < 100; i++) {
				for (int j = 1; j < i; j++) {
					if ((float(j) / float(i)) == (float(Functions::mulOfDigits(j)) / float(Functions::mulOfDigits(i))))
					{
						printf("%i / %i : %i / %i\n", j, i, int(Functions::mulOfDigits(j)), int(Functions::mulOfDigits(i)));
					}

					// printf("%I64u : %I64u\n", i, int(sumOfDigits(i)));
				}
			}
			//for (uint64_t k = 0; k < 15; k++) {
			//	for (uint64_t i = 0; i <= 15; i++) {
			//		for (uint64_t j = 0; j <= 15; j++) {
			//			uint64_t fac_sum = factorial(i) + factorial(j) + factorial(k);
			//			// printf("%i! + %i! + %i! = %i\n", k, i, j, fac_sum);
			//			


			//			if (((fac_sum / 100) % 10 == k) && ((fac_sum / 10) % 10 == i) && ((fac_sum) % 10 == j)) {
			//				printf("%i! + %i! + %i! = %i\n", (fac_sum / 100) % 10, (fac_sum / 10) % 10, (fac_sum) % 10, fac_sum);
			//				printf("%i! + %i! + %i! = %i\n", k, i, j, fac_sum);
			//			}
			//		}
			//	}
			//}

			// printf("%i! + %i! + %i! = %i\n", (145/100)%10, (145 / 10) % 10, (145) % 10, 145);
			return 0;
		}


		/* PROBLEM 58: Spiral Primes
			Explaination: https://projecteuler.net/problem=58
		*/
		int Problem_58() {

			// The spiral is the fibonacci sequence
			int corner = 3;
			int count_corner = 1;
			int count_primes = 1;

			double prime_ratio = 1.0;
			int sidelen = 2;
			bool switchSidelen = false;

			while (prime_ratio > 0.1) {
				corner += sidelen;

				// Iterate counts and calculate new prime ratio
				count_corner++;
				if (Functions::isPrime(corner)) {
					count_primes++;
				}
				std::cout << corner << " : " << count_primes << " / " << count_corner << " = " << prime_ratio << std::endl;

				prime_ratio = (double)(count_primes) / (double)(count_corner);


				// Check and flip sidelen switch
				if (switchSidelen) sidelen++;
				switchSidelen = !switchSidelen;
			}
			return sidelen;
		}

		/* PROBLEM 100: Arranged probability
			Explaination: https://projecteuler.net/problem=100
		*/

		// General Diophantine Solution: https://www.alpertron.com.ar/METHODS.HTM
		uint64_t Problem_100() {

			//	//B = k / sqrt(2);
			//	//while (B < 71*k/100) {
			//	//	// if ( (double(B) / double(k)) * (double(B-1) / (double)(k-1))  == 0.5) {
			//	//	std::cout << k << " : " << (long long)(B) << " : " << (double)B * (double)(B - 1) / ((double)k * ((double)k - 1)) << std::endl;
			//	//	// }
			//	//	B++;
			//	//}
			//}

			uint64_t B = 1, n = 1;
			uint64_t B_tmp = B;
			while (true) {
				std::cout << n << " : " << B << std::endl;
				//std::cout << "GCF: " << gcd(n,B) << std::endl;
				B_tmp = B;
				B = 3 * B + 2 * n - 2;
				n = 4 * B_tmp + 3 * n - 3;
				if (n > 1'000'000'000'000) {
					std::cout << n << " : " << B << std::endl;
					return B;
				}
			}


			return 0;
		}

		uint64_t Problem_100_general() {
			// Methods used: https://www.alpertron.com.ar/METHODS.HTM#SolHomo
				// Quadratic Diophantine Equations by Titu Andreescu et al. pg 176 - 177
					// 7.2.2 Rational Numbers Representable as Tm / Tn

			// Quadratic Diophantine equations:
				// Ax2 + Bxy + Cy2 + Dx + Ey + F = 0

			// Our Equation:
				// Qx2 - Py2 - Qx + Py = 0
				// Ax2 + Cy2 + Dx + Ey = 0; 

			// Sub in P and Q
			int64_t P = 1;
			int64_t Q = 2;
			int64_t D = 1'000'000'000'000;

			// Step 1: Ensure P and Q are relatively prime
			int64_t g = Functions::gcd(Q, P);
			Q /= g;
			P /= g;

			// Step 2: If P*Q is square, no solutions exist beyond the trivial solutions
			int64_t sqrt_PQ = int64_t(sqrt(P * Q));
			if (sqrt_PQ * sqrt_PQ == P * Q) {
				std::cout << "No solution" << std::endl;
				return 0;
			}
			else {
				// Step 3: Find initial values. For this equation form, x0 = 1, y0 = 1 always because constant term F = 0
				int64_t x = 1;
				int64_t y = 1;

				/// Step 4: Find the fundamental solution to the Pell's Equation, r - QPs = 1, using continued fractions method
				uint64_t r[2] = { 0, 0 };
				uint64_t s[2] = { 0, 0 };
				Functions::solvePellsEquation(Q * P, &r[0], &s[0]);

				// Step 5: Find the next solution for Pell's Equation, (s1, r1))
				r[1] = (r[0] * r[0]) + (P * Q * s[0] * s[0]);
				s[1] = (2 * r[0] * s[0]);

				// Step 6: Iterate to find solutions
				int64_t SOLUTION_1X = 0;
				int64_t SOLUTION_1Y = 0;
				x = 1;
				y = 1;
				int64_t x_tmp = x;
				int64_t iter = 1;

				if (y > D) {
					SOLUTION_1X = x;
					SOLUTION_1Y = y;
				}
				else {
					while (x >= 0 && y >= 0) {
						x_tmp = x;
						x = r[1] * x + (P * s[1]) * y - ((P * Q * s[0] * s[0]) + P * r[0] * s[0]);
						y = Q * s[1] * x_tmp + (r[1]) * y - (Q * s[0] * r[0] + Q * P * s[0] * s[0]);

						if (y > D) {
							SOLUTION_1X = x;
							SOLUTION_1Y = y;
							break;
						}
					}
				}

				// Step 7: Iterate again using (1, 0) as a starting point using the obtained values
				x = 1;
				y = 0;
				x_tmp = x;
				iter = 1;

				while (x >= 0 && y >= 0) {
					x_tmp = x;
					x = r[1] * x + (P * s[1]) * y - ((P * Q * s[0] * s[0]) + P * r[0] * s[0]);
					y = Q * s[1] * x_tmp + (r[1]) * y - (Q * s[0] * r[0] + Q * P * s[0] * s[0]);

					if (y > D) {
						if (y < SOLUTION_1Y) {
							SOLUTION_1Y = y;
							SOLUTION_1X = x;
						}
						break;
					}
				}

				// Step 8: Iterate again using (1, 0) as a starting point using the obtained values
				x = 0;
				y = 1;
				x_tmp = x;
				iter = 1;

				while (x >= 0 && y >= 0) {
					cout << x << " : " << y << endl;
					x_tmp = x;
					x = r[1] * x + (P * s[1]) * y - ((P * Q * s[0] * s[0]) + P * r[0] * s[0]);
					y = Q * s[1] * x_tmp + (r[1]) * y - (Q * s[0] * r[0] + Q * P * s[0] * s[0]);

					if (y > D) {
						cout << x << " : " << y << endl;
						if (y < SOLUTION_1Y) {
							SOLUTION_1Y = y;
							SOLUTION_1X = x;
						}
						break;
					}
				}

				cout << endl;

				return SOLUTION_1Y;
			}
		}

		/* PROBLEM 719: Number Splitting
			Explaination: https://projecteuler.net/problem=719
		*/

		bool isSNumber(long long number, int depth = 0, long long parent_sum = 0, long long orig_root_num = 0) {
			if (number == 0) {
				return false;
			}
			long long dec = 1;
			long long root_num = orig_root_num;

			if (orig_root_num == 0) {
				root_num = long long(sqrt(number));
			}

			// Find ciel of log10 of number
			unsigned short i = 0;
			while (tenToThe[i + 1] <= uint64_t(number)) {
				i++;
			}
			dec = tenToThe[i];

			while (dec > 1) {

				// Split msds from lsds
				long long ms_digits = long long(number / dec);
				long long ls_digits = number - ms_digits * dec;
				dec /= 10;

				// Print digits and sum
				long long sum = ms_digits + ls_digits + parent_sum;
				/*for (int j = 0; j < depth; j++) std::cout << "\t";
				if(depth > 0) std::cout << " + ";
				std::cout << ms_digits << " + " << ls_digits << " = " << sum << std::endl;

				std::cout << "SUM: " << sum << "Rootnum: " << root_num << std::endl;*/

				// Check sum

				if (sum == root_num) {
					return true;
				}
				if (dec > 1) {
					if (isSNumber(ls_digits, depth + 1, ms_digits + parent_sum, root_num)) {
						return true;
					}
				}
				else {
					return false;
				}
			}
			return false;
		}

		long long Problem_719() {
			long long sum = 0;
			long long sqr_i = 0;
			for (long long i = 1; i <= 1000000; i++) {
				sqr_i = i * i;
				if (isSNumber(sqr_i, 0, 0, i)) {
					std::cout << sqr_i << " : " << i << std::endl;
					sum += sqr_i;
				}
			}
			return sum;
		}

		/* PROBLEM 745: Sum of Squares II
			Explaination: https://projecteuler.net/problem=745
		*/

		uint64_t P745_g(uint64_t n) {
			uint64_t result = 1;
			for (uint64_t i = 2; i * i <= n; i++) {
				if (n % (i * i) == 0) {
					result = i * i;
				}
			}
			return result;
		}

		long long Problem_745() {

			// Sum perfect square numbers
			uint64_t N = 1000000;
			uint64_t result = 0;
			for (uint64_t i = 1; i <= N; i++) {
				result += P745_g(i);
				result = result % 1000000007;
			}
			return result;
		}

		/* PROBLEM 757: Stealthy Numbers
			Explaination: https://projecteuler.net/problem=757
		*/
		bool isStealthy(uint64_t N) {
			uint32_t sqrt_N = uint32_t(sqrt(N));

			for (uint32_t a = 0; a < sqrt_N; a++) {

			}
			return false;
		}

		double Problem_757() {

			return 0;
		}

		/* PROBLEM 776: Digit Sum Division
			Explaination: https://projecteuler.net/problem=776
		*/
		double Problem_776() {

			return Functions::F_SumOfDigits(1234567);
		}


		/* PROBLEM 777: Lissajous Curves
			Explaination: https://projecteuler.net/problem=777
		*/

		double Coprime_Curve(uint32_t a, uint32_t b) {
			// The sum is over all points(x, y) at which C crosses itself.
			const double step = 0.00000001;
			double t = 0;
			double ct = 0;
			// TODO: WE WANT TO MEMOIZE COSINE VALUES
			while (t <= TAU) {
				t += step;
				ct += cos(t);
			}
			return t;
		}

		double Problem_777() {
			return Coprime_Curve(2, 7);
		}

		/* PROBLEM 778: Freshman's Product
			Explaination: https://projecteuler.net/problem=778
		*/

		int64_t Freshmans_Product(uint32_t a, uint32_t b) {
			unsigned short i = 0;
			int64_t c = 0;
			while (a > 0 && b > 0) {
				// std::cout << a << " : " << b << " : " << tenToThe[i] * (a * b % 10) << std::endl;
				c += int64_t(tenToThe[i]) * ((a * b) % 10);

				a /= 10;
				b /= 10;
				i++;
			}
			return c;
		}

		long long Freshmans_Product_Sum(uint32_t R, uint32_t M) {
			long long result = 0;
			for (uint32_t i = 0; i <= M; i++) {
				for (uint32_t j = 0; j <= M; j++) {
					long long tmp_i = Freshmans_Product(i, j);
					//for (uint32_t k = 1; k <= R; k++) {
						//tmp_i = Freshmans_Product(tmp_i, k);
					//}
					result += tmp_i;
				}
			}
			return result;
		}

		double Problem_778() {
			double res = 0;

			res = double(Freshmans_Product(234, 765));

			return res;
		}

		/* PROBLEM 779: Prime Factor and Exponent
			Explaination: https://projecteuler.net/problem=779
		*/

		double Problem_779() {
			return 0;
		}

		void SolveEulerProblems() {
			std::cout << "Problem 1 | Solution: " << Problem_1() << std::endl;
		}
	}
}
