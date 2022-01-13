// Drayton Monkman, 2022

#ifndef DMLIB_FUNCTIONS
#define DMLIB_FUNCTIONS

namespace DMLib {
	namespace Functions {

		// Fast algorithm; Worst case O(sqrt(n)), average O(log(n)) (I think ?)
		uint64_t findLargestPrimeFactor(uint64_t n);

		bool isPrime(uint64_t number);

		uint64_t n_choose_k(uint64_t n, uint64_t k);

		void PrintPascalsTriangle(short n = 5);

		uint64_t factorial(uint64_t n);

		uint64_t sumOfDigits(uint64_t n);

		uint64_t mulOfDigits(uint64_t n);

		// Takes the sum of all prime factors of a number
		bool CancelPrimeFactors(uint64_t NUMER, uint64_t DENOM);

		// Greatest common denominator of A and B
		uint64_t gcd(uint64_t A, uint64_t B);

		void solvePellsEquation(uint64_t D, double* p_, double* q_);

		// Useful for PE Problems 66, 100
		void solvePellsEquation(uint64_t D, uint64_t* p_, uint64_t* q_);

		double SumOfDigits(long long n);

		double F_SumOfDigits(long long N);

		// Basic base^power function
		uint64_t power(uint64_t base, uint64_t exponent);

		//// Print size of all datatypes. Provides a quick way know what the compiler is doing with int, long, etc.
		//void PrintDatatypeSizes() {
		//	std::cout
		//		<< "1) size of char:        " << sizeof(char) << '\n'
		//		<< "2) size of char*:       " << sizeof(char*) << '\n'
		//		<< "3) size of short:       " << sizeof(short) << '\n'
		//		<< "4) size of int:         " << sizeof(int) << '\n'
		//		<< "5) size of long:        " << sizeof(long) << '\n'
		//		<< "6) size of long long:   " << sizeof(long long) << '\n'
		//		<< "7) size of float:       " << sizeof(float) << '\n'
		//		<< "8) size of double:      " << sizeof(double) << '\n'
		//		<< "9) size of long double: " << sizeof(long double) << '\n'
		//		<< "A) size of uint8_t:     " << sizeof(uint8_t) << '\n'
		//		<< "B) size of intmax_t:    " << sizeof(intmax_t) << '\n' << std::endl;
		//}

		// Evaluate the runtime of a single function
		template <typename T>
		T EvaluateRuntime(T(*f1)(), double& runtime) {

			// TEST FUNCTION RUNTIME
			auto start = std::chrono::high_resolution_clock::now();	// Take initial timestamp
			T result = f1();
			auto stop = std::chrono::high_resolution_clock::now();  // Take second timestamp

			auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);	// Calculate the duration
			runtime = (double)(duration.count());	// Cast duration to double; "return" via pointer
			return result;							// return function output
		}

		// Function to compare the runtimes of two functions. Neither function can take input args with this configuration.
		template <typename T>
		void CompareRuntimes(T(*f1)(), T(*f2)()) {
			double t1, t2;
			double t1_adj, t2_adj;
			char postfix[3];

			std::cout << std::endl << std::endl << "******************* FUNCTION 1 BEGIN *******************" << std::endl << std::endl;

			// TEST FUNCTION 1 RUNTIME
			T result_1 = EvaluateRuntime<T>(f1, t1);
			std::cout << "Function 1 Result: " << result_1 << std::endl;
			postfix[0] = 'n';
			postfix[1] = 's';
			postfix[2] = '\0';

			t1_adj = t1;
			if (t1_adj > 1000) {
				t1_adj /= 1000;
				postfix[0] = 'u';
			}
			if (t1_adj > 1000) {
				t1_adj /= 1000;
				postfix[0] = 'm';
			}
			if (t1_adj > 1000) {
				t1_adj /= 1000;
				postfix[0] = 's';
				postfix[1] = '\0';
			}

			std::cout << "Runtime for Function 1: " << t1_adj << " " << postfix << std::endl;

			std::cout << std::endl << std::endl << "******************* FUNCTION 2 BEGIN *******************" << std::endl << std::endl;

			// TEST FUNCTION 2 RUNTIME
			T result_2 = EvaluateRuntime<T>(f2, t2);
			std::cout << "Function 2 Result: " << result_2 << std::endl;
			postfix[0] = 'n';
			postfix[1] = 's';
			postfix[2] = '\0';

			t2_adj = t2;
			if (t2_adj > 1000) {
				t2_adj /= 1000;
				postfix[0] = 'u';
			}
			if (t2_adj > 1000) {
				t2_adj /= 1000;
				postfix[0] = 'm';
			}
			if (t2_adj > 1000) {
				t2_adj /= 1000;
				postfix[0] = 's';
				postfix[1] = '\0';
			}

			std::cout << "Runtime for Function 2: " << t2_adj << " " << postfix << std::endl;

			// COMPARE RUNTIMES AND PRINT RESULT
			if (t2 >= t1)
				std::cout << "Function 1 ran " << std::setprecision(4) << double(t2) / double(t1) << "x FASTER than Function 2!" << std::endl;
			else
				std::cout << "Function 1 ran " << std::setprecision(4) << double(t1) / double(t2) << "x SLOWER than Function 2!" << std::endl;
			std::cout << std::endl << std::endl;
			return;
		}

		// Swap values using a temp value
		template <typename T>
		void SwapVals(T* pVal1, T* pVal2) {
			T tmp = *pVal1;
			*pVal1 = *pVal2;
			*pVal2 = tmp;
			return;
		}

		// Swap values without using a temp value (exercise)
		template <typename T>
		void SwapVals_noTemp(T* pVal1, T* pVal2) {

			// A* = A + B
			*pVal1 = (*pVal1 + *pVal2);

			// B* = -(B - A*) = -(B - (A + B)) = -(-A) = A
			*pVal2 = -(*pVal2 - *pVal1);

			// A** = A* - B* = (A + B) - (A) = B
			*pVal1 = (*pVal1 - *pVal2);
			return;
		}
	}
}

#endif