/*
Задача 5.4. Закраска прямой в один слой
На числовой прямой окрасили N отрезков.
Известны координаты левого и правого концов каждого отрезка [Li, Ri]. Найти сумму длин частей числовой прямой, окрашенных ровно в один слой.
N ≤ 10000. Li, Ri — целые числа в диапазоне [0, 109].

Формат ввода
В первой строке записано количество отрезков.
В каждой последующей строке через пробел записаны координаты левого и правого концов отрезка.

Формат вывода
Выведите целое число — длину окрашенной в один слой части.
3
1 4
7 8
2 5

3
*/

#include <iostream>
#include <string.h>

struct Point {
	int value;
	int type;
	bool operator<(Point other) {
		return value <= other.value;
	}
};

template <typename T>
void Merge(T arr_left[], int left_size, T arr_right[], int right_size, T merged_arr[]) {
	int left_index = 0;
	int right_index = 0;
	while(left_index < left_size && right_index < right_size) {
		if (arr_left[left_index] < arr_right[right_index]) {
			merged_arr[left_index + right_index] = arr_left[left_index];
			left_index++;
		}
		else {
			merged_arr[left_index + right_index] = arr_right[right_index];
			right_index++;
		}
	}
	// копирование оставшихся элементов
	while(left_index < left_size) {
		merged_arr[left_index + right_index] = arr_left[left_index];
		left_index++;
	}
	while(right_index < right_size) {
		merged_arr[left_index + right_index] = arr_right[right_index];
		right_index++;
	}
}

template <typename T>
void MergeSort(T arr[], int size) {
	if (size <= 1) {
		return;
	}
	int left_size = size / 2;
	int right_size = size - left_size;
	MergeSort(arr, left_size);
	MergeSort(arr + left_size, right_size);

	T* merged_arr = new T[size];
	Merge(arr, left_size, arr + left_size, right_size, merged_arr);
	memcpy(arr, merged_arr, size*sizeof(T));
	delete[] merged_arr;
}

int main() {
	int n = 0;
	std::cin >> n;
	if (n == 0) {
		std::cout << 0 << std::endl;
		return 0;
	}
	int points_num = 2*n;
	Point* points = new Point[points_num];
	for (int i = 0; i < points_num; i+=2) {
		std::cin >> points[i].value >> points[i+1].value;
		points[i].type = 1;
		points[i+1].type = -1;
	}

	MergeSort(points, points_num);

	int sum = 0;
	//int prev_point = points[0].value;
	int sign = points[0].type;

	for(int i = 1; i < points_num; i++) {
		if (sign == 1) {
			sum += points[i].value - points[i-1].value;
		}
		//prev_point = points[i].value;
		sign += points[i].type;
	}

	std::cout << sum << std::endl;
	delete[] points;
	return 0;
}