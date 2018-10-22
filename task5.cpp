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

/*
// Метод слияния массивов
merge(int32_t left, int32_t middle, int32_t right) {
    int32_t it_left = 0, it_right = 0;

    // Буфферный массив для хранения первой половины массива
    auto *buf = new T[middle - left];
    memcpy(buf, array + left, sizeof(T) * (middle - left));

    // Сливаем буфрный массив и исходный массив с индекса middle
    //  В исходный массив
    while (left + it_left < middle && middle + it_right < right) {
        if (buf[it_left] < array[middle + it_right]) {
            array[left + it_left + it_right] = buf[it_left];
            it_left++;
        } else {
            array[left + it_left + it_right] = array[middle + it_right];
            it_right++;
        }
    }
    // Если остались элементы в буферном массиве
    // Перенсим их в исходный массив
    for ( ; left + it_left < middle; ++it_left)
        array[left + it_left + it_right] = buf[it_left];

    delete[] buf;
}
*/

void Merge(arr, left, arr + left, right, newArr) {
	int left_index = 0;
	int right_index = 0;
	int mid = (left + right) / 2;
	memcpy(newArr, array + left, (mid-left)*sizeof(int));
	while(left + left_index < mid && mid + right_index < right) {
		if (arr[left_index] < array[mid + right_index]) {
			array[left + left_index + right_index] = newArr[left_index];
			left_index++;
		}
		else {
			arr[left + left_index + right_index] = array[mid + right_index];
			right_index++;
		}
	}
	while(left + left_index < mid) {
		arr[left + left_index + right_index] = newArr[left_index];
		left_index++;
	}
}

void MergeSort(int* arr, int size) {
	if (size <= 1) {
		return;
	}
	int left = size / 2;
	int right = size - left;
	MergeSort(arr, left);
	MergeSort(arr + left, right);
	int* newArr = new int[size];
	Merge(arr, left, arr + left, right, newArr);
	memcpy(arr, newArr, size*sizeof(int));
	delete[] newArr;
	return;
}

int main() {

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

	//for (int i = 0; i < n; i++) {
	//	std::cout << "[" << line[i].x1 << ", " << line[i].x2 << "]" << std::endl; 
	//}
	std::cout << k << std::endl;

	delete[] line;
	return 0;
}