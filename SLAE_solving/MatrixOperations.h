#pragma once
#include<iostream>
#include<vector>
#include"Rand_single_or_double.h"

using namespace std;

template<typename T>
void multi(vector<vector<T>> &left, vector<T> &right, vector<T> &result) {
	size_t size1 = left.size();
	if (size1 < 1) {
		throw new std::logic_error("Size of left matrix must be greater then zero!");
	}
	size_t size2 = left[0].size();
	if (size2 != right.size()) {
		throw new std::logic_error("One size of left matrix and right matrix must be equal!");
	}
	for (int i = 0; i < size1; i++) {
		result.push_back(0);
		for (int j = 0; j < size2; j++) {
			result[i] += left[i][j] * right[j];
		}
	}
}

template<typename T>
bool check_double_eq(T a, T b, T eps = 0.000001) {
	if (abs(a - b) < eps) {
		return true;
	}
	return false;
}

template<typename T>
void fill_vector(vector<T>& v, Rand_single_or_double<T>& r) {
	size_t N = v.size();
	for (size_t i = 0; i < N; i++) {
		v[i] = r();
	}
}

template<typename T>
void fill_vector(vector<vector<T>> &v, Rand_single_or_double<T> &r) {
	size_t size1 = v.size();
	if (size1 < 1) {
		return;
	}
	size_t size2 = v[0].size();
	for (size_t i = 0; i < size1; i++) {
		for (size_t j = 0; j < size2; j++) {
			v[i][j] = r();
		}
	}
}

template<typename T>
bool check_vector_for_equality(vector<T> &a, vector<T> &b, T eps = 0.000001) {
	size_t N = a.size();
	if (N != b.size()) {
		return false;
	}
	for(int i = 0; i < N; i++){
		if (abs(a[i] - b[i]) >= eps) {
			return false;
		}
	}
	return true;
}

template<typename T> 
void print(vector<vector<T>>& v, vector<T>& a, vector<T>& s) {
	size_t N = a.size();
	if (N < 1 || N != v.size() || N != v[0].size() || N != s.size()) {
		return;
	}
	cout << "Matix: " << endl;
	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < N; j++) {
			cout << v[i][j] << " ";
		}
		cout << endl;
	}
	cout << "Answers and solve: " << endl;
	for (size_t i = 0; i < N; i++) {
		cout << "ans: " << a[i] << ", solve: " << s[i] << endl;
	}
}

void print_time(clock_t time) {
	cout << "\nTime: " << time / 1000.0 << "seconds.\n" << endl;
}