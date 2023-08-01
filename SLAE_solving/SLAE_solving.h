// SLAE_resolving.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once

#include <iostream>
#include <vector>
#include "MatrixOperations.h"
#include <thread>
using namespace std;

template<typename T>
class SLAE_solving
{
	static_assert(std::is_same<T, float>::value || std::is_same<T, double>::value);
public:
	void solve(std::vector<std::vector<T>> &matrix, std::vector<T> &answers, std::vector<T> &solve)
	{
		size_t size = matrix.size();
		if (size < 1)
		{
			throw new std::logic_error("Size of matrix must be greater then zero!");
		}
		if (size != matrix[0].size())
		{
			throw new std::logic_error("Matrix must be square!");
		}
		if (size == 1) {
			solve.push_back(answers[0] / matrix[0][0]);
			return;
		}

		vector<vector<T>> matrix_m1 = vector<vector<T>>(size, vector<T>(size, 0));

		invert(matrix, matrix_m1);

		multi(matrix_m1, answers, solve);
	}
	void invert(std::vector<std::vector<T>> &matrix, std::vector<std::vector<T>> &matrix_m1)
	{
		T det = calc_det(matrix, true);
		if (check_double_eq(det, 0.0)) {
			throw new std::logic_error("Matrix determinant is zero! System has no solves!");
		}

		int size = matrix.size();

		if (size > minSizeForParallel/* && false*/) {
			vector<std::thread> threads;
			for (int i = 0; i < size; i++) {
				threads.push_back(std::thread(
					[&matrix, &matrix_m1, i, det, size, this]() {
						for (int j = 0; j < size; j++) {
							int koff = (i + j) % 2 == 0 ? 1 : -1;
							matrix_m1[j][i] = (1 / det) * koff * M(matrix, i, j);
						}
					}
				));
				cout << "Created thread " << i + 1 << endl;
			}
			int counter = 1;
			for(auto& thread : threads) {
				cout << "Joining thread " << counter++ << endl;
				thread.join();
			}
		}
		else {
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					int koff = (i + j) % 2 == 0 ? 1 : -1;
					matrix_m1[j][i] = (1 / det) * koff * M(matrix, i, j);
				}
			}
		}
	}
	void invert_JG(std::vector<std::vector<T>>& matrix, std::vector<std::vector<T>>& matrix_m1) {
		int size = matrix_m1.size();
		for (int i = 0; i < size; i++) {
			matrix_m1[i][i] = 1;
		}
		T koff1 = 1 / matrix[0][0];
		matrix_m1[0][0] *= koff1;
		for (int j = 0; j < size; j++) {
			matrix[0][j] *= koff1;
		}
		for (int i = 1; i < size; i++) {
			for (int i1 = 0; i1 < i; i1++) {
				T koff = matrix[i][i1] / matrix[i1][i1];
				for (int j = 0; j < size; j++) {
					matrix[i][j] -= koff * matrix[i1][j];
					matrix_m1[i][j] -= koff * matrix[i1][j];
				}
			}
			koff1 = matrix[i][i];
			for (int j = i; j < size; j++) {
				matrix[i][j] /= koff1;
				matrix_m1[i][j] /= koff1;
			}
		}

		for (int i = size - 1; i > 0; i--) {
			for (int i1 = i - 1; i1 > -1; i1--) {
				T koff = matrix[i1][i];
				for (int j = 0; j < size; j++) {
					matrix[i1][j] -= koff * matrix[i][j];
					matrix_m1[i1][j] -= koff * matrix_m1[i][j];
				}
			}
		}
	}
	T calc_det(std::vector<std::vector<T>>& matrix, bool toplevel = false)
	{
		int k = matrix.size();
		if (k < 0)
		{
			throw new std::logic_error("Size of matrix must be greater then zero!");
		}
		if (k != matrix[0].size())
		{
			throw new std::logic_error("Matrix must be square!");
		}
		if (k == 1) {
			return matrix[0][0];
		}
		else if (k == 2)
		{
			return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
		}
		else
		{
			T ret = 0;
			
			if (toplevel && k > minSizeForParallel) {
				vector<thread> threads;
				for (int j = 0; j < k; j++)
				{
					threads.push_back(thread([j, &ret, &matrix, this]() {
							int koff = j % 2 == 0 ? 1 : -1;
							ret += koff * matrix[0][j] * M(matrix, 0, j);
						}));
				}
				for (auto& th : threads) {
					th.join();
				}
			}
			else {
				for (int j = 0; j < k; j++)
				{
					int koff = j % 2 == 0 ? 1 : -1;
					ret += koff * matrix[0][j] * M(matrix, 0, j);
				}
			}
			return ret;
		}
	}
	T M(std::vector<std::vector<T>> &matrix, int I, int J) {
		int size = matrix.size();
		if (size < 1) {
			throw std::logic_error("Matrix size must be greater then zero!");
		}
		if (matrix[0].size() != size) {
			throw std::logic_error("Matrix must be square!");
		}
		if (I > size - 1 || J > size - 1) {
			throw std::logic_error("I or J greater then matrix size!");
		}
		auto m = std::vector<std::vector<T>>(size - 1, std::vector<T>(size - 1, 0));
		for (int i = 0; i < size; i++){
			if (i == I) {
				continue;
			}
			for (int j = 0; j < size; j++) {
				if (j == J) {
					continue;
				}
				m[i > I ? i - 1 : i][j > J ? j - 1 : j] = matrix[i][j];
			}
		}
		return calc_det(m);
	}
	private:
		int minSizeForParallel = 8;
};

// TODO: установите здесь ссылки на дополнительные заголовки, требующиеся для программы.
