// Drayton Monkman, 2022


// SWAP TWO VALUES IN MEMORY (ONLY IF THEY ARE THE SAME SIZE, ex. 8 byte)

#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include "DMLib_Functions.h"

using std::cout; 
using std::cerr;
using std::cin;
using std::endl;

static const unsigned long long tenToThe[] = {
	1, 10, 100, 1000, 10000, 100000, 1000000, 10000000,
	100000000, 1000000000, 10000000000, 100000000000, 1000000000000,
	10000000000000, 100000000000000, 1000000000000000, 10000000000000000
};

namespace DMLib {
	namespace Functions {

		// Fast algorithm; Worst case O(sqrt(n)), average O(log(n)) (I think ?)
		uint64_t findLargestPrimeFactor(uint64_t n) {

			// Divide out all 2's
			while (!(n & 1)) {
				n /= 2;            // RSHIFT, divide by 2
			}

			// Iterator; current number being tested as a factor
			uint64_t i = 3;
			uint64_t sqrt_n = uint64_t(sqrt(n));

			while (true) {
				// Calculate sqrt(n)

				// Otherwise, exctract the next smallest prime factor from n
				while (i < sqrt_n) {
					// If divisible by i; divide out i
					//cout << n << " : " << i << " : " << sqrt_n << std::endl;
					if (n % i == 0) {
						n /= i;
						sqrt_n = uint64_t(sqrt(n));
						break;
					}
					i += 2;
				}

				// If I reaches the current sqrt_n...
				if (i >= sqrt_n) {

					// Return sqrt_n if it is not rounded and prime
					if (sqrt_n * sqrt_n == n) {
						if (isPrime(sqrt_n)) {
							return sqrt_n;
						}
						return n;
					}

					// Return n if it is prime
					if (isPrime(n)) {
						return n;
					}

					// Otherwise return n/i; root rounding is interfering
					return n / i;
				}
			};

			return n;
		}

		bool isPrime(uint64_t number) {

			// If number is 2 return true
			if (number == 2) return true;

			// If number is otherwise even, return false
			if (!(number % 2))
				return false;


			uint64_t sqrt_number = uint64_t(sqrt(number));

			// Check all odd numbers for divisability
			for (uint64_t i = 3; i <= sqrt_number; i += 2)
				if (!(number % i))
					return false;
			return true;
		}

		uint64_t power(uint64_t base, uint64_t exponent) {
			uint64_t result = 1;
			for (uint64_t i = 0; i < exponent; i++) {
				result *= base;
			}
			return result;
		}

		uint64_t n_choose_k(uint64_t n, uint64_t k) {

			// If n is odd, the row has an even number of terms and vice versa
			uint64_t result = 1;


			// If k is on the right half of the triangle, flip k to reduce calculation time (symmetry)
			// Use n + 1 because there are n + 1 elements in row n
			if (k > n - k) {
				k = n - k;
			}
			// std::cout << n << " : " << k << " -> " << (n + 1) - k << " = ";

			// Count divisions. Divide whenever the result is divisible to reduce the risk of overflow
			uint64_t divCount = k;

			// Iterate using Multiplicative formula (http://en.wikipedia.org/wiki/Binomial_coefficient#Multiplicative_formula)
			for (uint64_t i = 1; i <= k; i++) {
				result *= (n - (k - i));
				if (result % i == 0) {
					// 3.70 ms
					result /= i;
					divCount--;
				}
			}
			for (uint64_t i = 1; i <= divCount; i++) {
				result /= i;
			}
			// std::cout << result << std::endl;
			return uint64_t(result);
		}

		void PrintPascalsTriangle(short n) {
			// Prints Pascal's Triangle to the nth layer starting with layer 0 as (1), layer 1 as (1 1), ...
			for (int i = 0; i <= n; i++) {
				for (int j = 0; j <= i; j++) {
					std::cout << n_choose_k(i, j) << " ";
				}
				std::cout << std::endl;
			}
		}

		uint64_t factorial(uint64_t n) {
			if (n > 2) {
				return (n * factorial(n - 1));
			}
			else if (n == 0) {
				return 1;
			}
			else if (n == 1) {
				return 1;
			}
			else if (n == 2) {
				return 2;
			}
			else {
				return 0;
			}
		};

		uint64_t sumOfDigits(uint64_t n) {
			uint64_t result = 0;
			while (n > 0) {

				// Split msds from lsds
				result += (n % 10);
				n /= 10;
			}
			return result;
		}

		uint64_t mulOfDigits(uint64_t n) {
			// Find ciel of log10 of number
			uint64_t result = 1;
			while (n > 0) {

				// Split msds from lsds
				result *= n % 10;
				n /= 10;
			}
			return result;
		}
		// Takes the sum of all prime factors of a number
		bool CancelPrimeFactors(uint64_t NUMER, uint64_t DENOM) {
			uint64_t NUMER_LESS_1 = NUMER - 1;
			uint64_t DENOM_LESS_1 = DENOM - 1;

			if (NUMER * NUMER_LESS_1 * 2 == DENOM * DENOM_LESS_1) {
				return true;
			}
			return false;

			// 1: Both the top and bottom MUST have a factor of 2. Cancel them
			//if (DENOM % 2 == 0)
			//	DENOM /= 2;
			//else
			//	DENOM_LESS_1 /= 2;

			//if (NUMER % 2 == 0)
			//	NUMER /= 2;
			//else
			//	NUMER_LESS_1 /= 2;

			//// 2. The bottom should have an extra factor of 2; Remove it or return false
			//if (DENOM % 2 == 0)
			//	DENOM /= 2;
			//else if (DENOM_LESS_1 % 2 == 0)
			//	DENOM_LESS_1 /= 2;
			//else {
			//	return false;
			//}


			//// CHECK FOR OVERFLOW
			//bool overflow = false;
			//uint64_t DENOM_PRODUCT = DENOM * DENOM_LESS_1;

			//if (DENOM != 0 && DENOM_PRODUCT / DENOM != DENOM_LESS_1) {
			//	std::cout << "OVERFLOW OCCURED!" << std::endl;
			//	//overflow = true;
			//}

			//while (overflow) {
			//	uint64_t i = 2;
			//	while (DENOM > 1) {
			//		if (DENOM % i == 0) {
			//			//std::cout << DENOM << " : "  << std::endl;
			//			// If numer term 1 can be cancelled, cancel
			//			if (NUMER % i == 0) {
			//				NUMER /= i;
			//				DENOM /= i;
			//			}

			//			// If numer term 2 can be cancelled, cancel
			//			else if (NUMER_LESS_1 % i == 0) {
			//				NUMER_LESS_1 /= i;
			//				DENOM /= i;
			//			}

			//			// If neither cancel, product of terms cannot be 1/2
			//			else {
			//				return false;
			//			}
			//		}
			//		else {
			//			i++;
			//		}
			//	}

			//	i = 2;
			//	while (DENOM_LESS_1 > 1) {
			//		if (DENOM_LESS_1 % i == 0) {
			//			//std::cout << DENOM << " : "  << std::endl;
			//			// If numer term 1 can be cancelled, cancel
			//			if (NUMER % i == 0) {
			//				NUMER /= i;
			//				DENOM_LESS_1 /= i;
			//			}

			//			// If numer term 2 can be cancelled, cancel
			//			else if (NUMER_LESS_1 % i == 0) {
			//				NUMER_LESS_1 /= i;
			//				DENOM_LESS_1 /= i;
			//			}

			//			// If neither cancel, a factor other than two that cannot be cancelled is found. Return false
			//			else {
			//				return false;
			//			}
			//		}
			//		else {
			//			i++;
			//		}
			//	}
			//}
			if (NUMER * NUMER_LESS_1 == DENOM * DENOM_LESS_1) {
				return true;
			}
			return false;
		}
		// Greatest common denominator of A and B
		uint64_t gcd(uint64_t A, uint64_t B) {
			// If equal, GCD is A = B, obviously
			if (A == B) {
				return A;
			}

			// If A = 0 or B = 0, return the other
			if (B == 0) {
				return A;
			}
			else if (A == 0) {
				return B;
			}

			// Divide out twos
			uint8_t k = 0;
			while (!(A & 1 || B & 1)) {
				A >>= 1;
				B >>= 1;
				k++;
			}

			// Make A the larger of A and B
			uint64_t tmp = A;
			if (B > A) {
				A = B;
				B = tmp;
			}



			// Iterate
			while (true)
			{
				// gcd(B, A) = gcd(| A - B |, min(B, A))
				A -= B;

				// gcd(u, 0) = u
				if (A == 0) {
					return (B << k);
				}

				// Divide out twos
				while (!(A & 1)) {
					A >>= 1;
				}

				// Make A the larger of A and B
				tmp = A;
				if (B > A) {
					A = B;
					B = tmp;
				}
			}
		}
		void solvePellsEquation(uint64_t D, double* p_, double* q_) {
			// If large D are expected, a correction for R is needed.
			uint64_t R = uint64_t(floor(sqrt(D)));
			// std::cout << "D : " << D << std::endl;

			// If it's a square, return the trivial solution
			if (R * R == D) {
				// std::cout << "D is a square. No continued fraction." << std::endl;
				*p_ = 1;
				*q_ = 0;
				return;
			}

			const uint32_t ARRLEN = 4096;
			double p[ARRLEN];
			double q[ARRLEN];

			uint64_t iter = 0;
			uint64_t a = R, P = 0, Q = 1, m = 0;

			p[0] = double(a);
			q[0] = 1;

			iter++;

			bool m_found = false;

			for (int i = 0; i < 2; i++) {
				do {
					if (!m_found) {
						m++;
					}
					P = a * Q - P;
					Q = (D - P * P) / Q;
					a = (R + P) / Q;

					// Build array of P and Q "guesses"
					if (iter == 1) {
						p[1] = double(a * p[0] + 1);
						q[1] = double(a);
					}
					else {
						p[iter] = a * p[iter - 1] + p[iter - 2];
						q[iter] = a * q[iter - 1] + q[iter - 2];
					}
					// printf("a%I64u = %I64u : p%I64u = %I64u : q%I64u = %I64u\n", iter, a, iter, p[iter], iter, q[iter]);
					iter++;
				} while (Q != 1);

				// m has been found; React accordingly
				// m_found == true;

				// If m is odd, solution is for p^2 + Dp^2 = -1, we want p^2 + Dp^2 = -1
				if (m % 2 == 0) {
					break;
				}
			}

			*p_ = p[m - 1];
			*q_ = q[m - 1];

			return;
		}

		// Useful for PE Problems 66, 100
		void solvePellsEquation(uint64_t D, uint64_t* p_, uint64_t* q_) {
			// If large D are expected, a correction for R is needed.
			uint64_t R = uint64_t(floor(sqrt(D)));

			// If it's a square, return the trivial solution
			if (R * R == D) {
				// std::cout << "D is a square. No continued fraction." << std::endl;
				*p_ = 1;
				*q_ = 0;
				return;
			}

			std::vector<uint64_t> p;
			std::vector<uint64_t> q;
			// uint64_t q[2560];


			uint64_t iter = 0;
			uint64_t a = R, P = 0, Q = 1, m = 0;
			p.push_back(a);
			q.push_back(1);
			// p[0] = a;
			// q[0] = 1;

			iter++;

			bool m_found = false;
			for (int i = 0; i < 2; i++) {
				do {
					if (!m_found) {
						m++;
					}
					P = a * Q - P;
					Q = (D - P * P) / Q;
					a = (R + P) / Q;

					// Build array of P and Q "guesses"
					if (iter == 1) {
						p.push_back(a * p[0] + 1);
						q.push_back(a);
					}
					else {
						p.push_back(a * p[iter - 1] + p[iter - 2]);
						q.push_back(a * q[iter - 1] + q[iter - 2]);
					}
					// printf("a%I64u = %I64u : p%I64u = %I64u : q%I64u = %I64u\n", iter, a, iter, p[iter], iter, q[iter]);
					iter++;
				} while (Q != 1 || (m_found && iter <= 4 * m));

				// m has been found; React accordingly
				// m_found == true;

				// If m is odd, solution is for p^2 + Dp^2 = -1, we want p^2 + Dp^2 = -1
				if (m % 2 == 0) {
					break;
				}
			}

			*p_ = p[m - 1];
			*q_ = q[m - 1];

			return;
		}


		double SumOfDigits(long long n) {
			// Find ciel of log10 of number
			unsigned short i = 0;
			while (tenToThe[i + 1] <= (long long)(n)) {
				i++;
			}

			short ith_digit = 0;
			long long result = 0;
			while (i > 0) {
				// Split msds from lsds
				ith_digit = (short)(n / tenToThe[i]);
				result += ith_digit;
				n -= ith_digit * tenToThe[i];
				i--;
			}
			return double(result + n);  // at this point, n is the final digit

		}

		double F_SumOfDigits(long long N) {
			double result = 0;

			// TOO SLOW
			/*
			for (long long n = 1; n <= N; n++) {
				result += (double)(n / SumOfDigits(n));
				// std::cout << "Res: " << result << std::endl;
			}*/
			return result;
		}
	}
}

