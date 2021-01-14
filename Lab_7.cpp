// cpp_compiler_options_openmp.cpp
#include <iostream>
#include <ctime>
#include <omp.h>
using namespace std;

const static int N = 100000;
long calculateSum(long arr[], int n) {
	long sum = 0;
#pragma omp parallel for reduction(+:sum) private(i)
	for (int i = 0; i < n; i++) {
		sum += arr[i];
	}
	return sum;
}

long calculateSum_2(long arr[], int n) {
	long sum = 0;
	int size = n;
	while (size > 1) {
		if (size % 2 == 1) {
			arr[0] += arr[size - 1];
			size -= 1;
		}
#pragma omp parallel private(i)
		for (int i = 0; i < size / 2; i++) {
			arr[i] += arr[size - i - 1];
		}
		size /= 2;
	}
	sum = arr[0];
	return sum;
}

void printMinEl(long arr[], int n) {\
	int min = arr[0];
	int index = 0;
#pragma omp parallel private(i)
	for (int i = 1; i < n - 1; i++) {
		if (arr[i] < min) {
			min = arr[i];
			index = i;
		}
	}
	cout << "\nMinimum is " << min << "\nIndex is " << index << endl;
}

int main()
{
	long arr[N];
	for (int i = 0; i < N; i++) {
		arr[i] = i + 1;
	}
	unsigned int start_time = clock();
	cout << "Sum by first method is  " << calculateSum(arr, N) << endl;
	unsigned int time = clock() - start_time;
	printf("%f", (double)time / CLOCKS_PER_SEC);
	start_time = clock();
	cout << "\nSum by second method is  " << calculateSum_2(arr, N) << endl;
	time = clock() - start_time;
	printf("%f", (double)time / CLOCKS_PER_SEC);

	for (int i = 0; i < N; i++) {
		arr[i] = i + 1;
	}
	arr[N / 2 + N / 4] = -1;
	printMinEl(arr, N);
}