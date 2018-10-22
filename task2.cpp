/**
Пересечение множеств
Ограничение времени	1 секунда
Ограничение памяти	5Mb
Ввод	стандартный ввод или input.txt
Вывод	стандартный вывод или output.txt

Даны два массива неповторяющихся целых чисел, упорядоченные по возрастанию. A[0..n-1] и B[0..m-1]. n » m. 
Найдите их пересечение. Требуемое время работы: O(m * log k), где k - позиция элементта B[m-1] в массиве A.. В 
процессе поиска очередного элемента B[i] в массиве A пользуйтесь результатом поиска элемента B[i-1]. n, k ≤ 10000.

Пример
Ввод	
5¶
3¶
1 2 3 4 5¶
1 3 5¶

Вывод
1 3 5¶

ID Решения: 12400138
**/

/**
Время работы: О(len1 + len2)
Доп. память:  T(len2) // len2 < len1 (по условию)
**/

#include <iostream>

// Функция бинарного поиска.
// Аргументы: массив, по которому идет поиск, элемент, и границы поиска
// Возвращает позицию найденного элемента, и -1, если поис прошел без результата 
int binSeach(const int* array, int element, int left, int right ) {
	while (left < right) {
		int mid = (left + right) / 2;
		if (array[mid] == element) {
			return mid;
		}
		else if (array[mid] < element) {
			left = mid + 1;
		}
		else {
			right = mid;
		}
	}
	return -1; 
}

// Функция поиска пересечения множеств
// принимает два массива, их размер и указатель на размер их пересечения
// Возвращает указатель на массив пересечения множеств
int* setsUnion(const int* series_1, const int* series_2, int len1, int len2, int* p_len3) {
 
 	// пересечение множеств, выделяется память размера len2, так как размер перечения множеств не сможет превысить размер меньшего множества (len2 < len1 по условию)
	int* series_3 = new int[len2];
	int len3 = 0; // размер массива пересечения множеств

	int previousIndex = 0;
	for (int i = 0; i < len2; i++) {
		int index = binSeach(series_1, series_2[i], previousIndex, len1);
		if (index != -1) {
			series_3[len3] = series_1[index];
			len3++;
			previousIndex = index; // смещаем левую границу для поиска
		}
	}
	*p_len3 = len3;
	return series_3;
}

int main() {
	int len1 = 0;
	int len2 = 0;
	std::cin >> len1 >> len2;
	// считываем первый массив
	int* series_1 = new int[len1];
	for (int i = 0; i < len1; i++) {
		std::cin >> series_1[i];
	}

	// считываем второй массив
	int* series_2 = new int[len2];
	for (int j = 0; j < len2; j++) {
		std::cin >> series_2[j];
	}	

	int len3 = 0;
	int* series_3 = setsUnion(series_1, series_2, len1, len2, &len3);
	for (int k = 0; k < len3; k++) {
		std::cout << series_3[k] << " ";
	}
	std::cout << std::endl;
	delete[] series_1;
	delete[] series_2;
	delete[] series_3;

	return 0;
}