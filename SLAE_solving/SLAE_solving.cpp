// SLAE_resolving.cpp: определяет точку входа для приложения.
//

#include "SLAE_solving.h"
#include <cstdlib>
#include <ctime>
#include "MatrixOperations.h"
#include "Rand_single_or_double.h"

using namespace std;

int main()
{
	Rand_single_or_double<double> r(0, 1000.0);
	SLAE_solving<double> solver;
	clock_t start_time;
	clock_t end_time;

	for (int i = 0; i < 10; i++) {
		//Testcase 1:
		int N = i + 1;
		std::vector<std::vector<double>> t1(N, vector<double>(N, 0));
		std::vector<double> a1(N, 0);
		std::vector<double> s1;
		fill_vector(t1, r);
		fill_vector(a1, r);

		cout << "Testcase " << i + 1 << ", N = " << N << endl;
		start_time = clock();
		solver.solve(t1, a1, s1);
		end_time = clock();
		print_time(end_time - start_time);

		std::vector<double> a1_test;
		multi(t1, s1, a1_test);
		print(t1, a1, a1_test);
		cout << "Is solution correct: " << (check_vector_for_equality(a1, a1_test) ? "True" : "False") << endl;
		cout << endl << endl;
	}

	return 0;
}
