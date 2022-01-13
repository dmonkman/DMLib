// Drayton Monkman, 2022

#ifndef DMLIB_PESOLUTIONS
#define DMLIB_PESOLUTIONS

namespace DMLib {
	namespace PESolutions {
		// Solutions to problems found at https://projecteuler.net/

		int Problem_1();				// COMPLETE
		int Problem_1(int maxnum);

		int Problem_1_alt();
		int Problem_1_alt(int maxnum);

		uint64_t Problem_2();				// COMPLETE
		uint64_t Problem_2(int maxnum);

		uint64_t Problem_2_alt();
		uint64_t Problem_2_alt(int maxnum);

		uint64_t Problem_3();		// COMPLETE
		uint64_t Problem_3_alt();

		uint64_t Problem_6();	// COMPLETE

		uint64_t Problem_7();	// COMPLETE

		uint64_t Problem_8();	// COMPLETE

		uint64_t Problem_9();	// COMPLETE

		uint64_t Problem_10();	// COMPLETE

		uint64_t Problem_11();	// COMPLETE

		uint64_t Problem_12();	// COMPLETE

		std::string Problem_13();

		uint64_t Problem_15();  // COMPLETE

		uint64_t Problem_16();  // COMPLETE

		int Problem_20();

		uint64_t Problem_25();  // COMPLETE; SOLVED WITH PEN AND CALCULATOR USING LOG(F(N)) = 999 = golden ratio equation...

		uint64_t Problem_34();

		int Problem_58();		// COMPLETE

		void solvePellsEquation(uint64_t D, double* p_, double* q_);

		void solvePellsEquation(uint64_t D, uint64_t* p_, uint64_t* q_);

		uint64_t Problem_100();	// COMPLETE

		uint64_t Problem_100_general();		// WORKS FOR SMALL VALUES OF P AND Q

		long long Problem_719();		// COMPLETE

		long long Problem_745();			// TODO

		double Problem_757();			// TODO

		double Problem_776();			// TODO

		double Problem_777();	// TODO

		double Problem_778();	// TODO

		double Problem_779();	// TODO

		void SolveEulerProblems();
	}
}

#endif