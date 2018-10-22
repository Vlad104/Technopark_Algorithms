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
//#include <cassert>

struct Line {
	int x1;
	int x2;
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

void Merge(int* arr_left, int left_size, int* arr_right, int right_size, int* merged_arr) {
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

void MergeSort(int* arr, int size) {
	if (size <= 1) {
		return;
	}
	int left_size = size / 2;
	int right_size = size - left_size;
	MergeSort(arr, left_size);
	MergeSort(arr + left_size, right_size);

	int* merged_arr = new int[size];
	Merge(arr, left_size, arr + left_size, right_size, merged_arr);
	memcpy(arr, merged_arr, size*sizeof(int));
	delete[] merged_arr;
}

int main() {
	int n;
	std::cin >> n;
	int* line = new int[n];
	for (int i = 0; i < n; i++) {
		std::cin >> line[i];
	}

	MergeSort(line, n);

	for (int i = 0; i < n; i++) {
		std::cout << line[i] << " ";
	}
	std::cout << std::endl;

/*
	int n;
	std::cin >> n;
	Line* line = new Line[n];
	for (int i = 0; i < n; i++) {
		std::cin >> line[i].x1 >> line[i].x2;
	}

	BubbleSort(line, n);
	int i = 0;
	int k = 0;
	int dot = 0;
	dot = line[0].x1;
	while(i < n - 1) {
		int distance = line[i+1].x1 - dot;
		int length = line[i].x2 - dot;
		k += std::min(length, distance);
		if ( (line[i].x2 < line[i+1].x1) ) {
			dot = line[i+1].x1;
		}
		else {
			dot = line[i].x2;
		}
		i++;
		if (i == n - 1) {
			k += line[i].x2 - dot;
		}
	}

	for (int i = 0; i < n; i++) {
		std::cout << "[" << line[i].x1 << ", " << line[i].x2 << "]" << std::endl; 
	}
	std::cout << k << std::endl;
	delete[] line;
*/
	return 0;
}