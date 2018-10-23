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
//#include <cassert>

struct Line {
	int x1;
	int x2;
	bool operator<(Line other) {
		return ( (x1 < other.x1) || ( x1 == other.x1 && x2 < other.x2) );
	}
	//Line(int _x1, int _x2) : x1(_x1), x2(_x2) {}
};

void BubbleSort(Line* line, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - 1 - i; j++) {
			if (line[j].x1 > line[j+1].x1) {
				std::swap(line[j], line[j+1]);
			}
		}
	}
}

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
	Line* line = new Line[n];
	for (int i = 0; i < n; i++) {
		std::cin >> line[i].x1 >> line[i].x2;
	}
	MergeSort(line, n);

	int i = 1;
	int k = 0;
	int dot = 0;
	dot = line[0].x1;
	while(i < n) {
		int distance = line[i].x1 - dot;
		int length = line[i-1].x2 - dot;
		if (distance < length) {
			k += distance;
			if (line[i-1].x2 <= line[i].x2) {
				dot = line[i-1].x2;
				line[i].x1 = dot;
				i++;
				while ( ( i < n ) && dot >= line[i].x2 ) {
					i++;
				}
				MergeSort(line, n);		
			}
			else {
				dot = line[i].x1;
				line[i-1].x1 = dot;
				MergeSort(line, n);
			}
		}
		else {
			k += length;
			dot = line[i].x1;
			i++;
		}
	//std::cout << "dist = " << distance << " len = " << length << " dot = " << dot << std::endl;
	}
	k += line[n-1].x2 - dot;

	//for (int i = 0; i < n; i++) {
	//	std::cout << "[" << line[i].x1 << ", " << line[i].x2 << "]" << std::endl; 
	//}
	std::cout << k << std::endl;
	delete[] line;
	return 0;
}