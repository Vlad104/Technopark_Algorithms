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

#include <iostream>
#include <vector>

int * setsUnion(const int * series_1, const int * series_2, int len1, int len2, int * p_len3) {

	int * series_3 = new int[len1]; // пересечение множеств
	int i = 0, j = 0;
	int len3 = *p_len3;
	int step_counter = 0;
	
	// обход массивов
	while (step_counter < len1 + len2) {
		step_counter++;
		if ( series_1[i] == series_2[j]) {
			series_3[len3] = series_1[i];
			len3++;
			if ( i < len1 - 1 ) { // перейти на следующий элемент, если текущий не последний
				i++;
			} 
			if ( j < len2 - 1 ) { // перейти на следующий элемент, если текущий не последний
				j++;
			} 
			if ( (i == len1 - 1) && (j == len2 - 1) ) {
				break;
			}
		} else if ( series_1[i] < series_2[j]) { // если элемент первого массива меньше элемента второго массива, нужно взять следующий элемент первого массива, тогда возможно они сравняются
			if ( i < len1 - 1 ) { // перейти на следующий элемент, если текущий не последний
				i++;
			} else {
				break;
			}
		} else { // если элемент второго массива меньше элемента первого массива, нужно взять следующий элемент второго массива, тогда возможно они сравняются
			if ( j < len2 - 1 ) { // перейти на следующий элемент, если текущий не последний
				j++;
			} else {
				break;
			}
		}

	}
	*p_len3 = len3;
	return series_3;
}

int main() {
	int len1, len2;
	std::cin >> len1 >> len2;
	int * series_1 = new int[len1];
	for (int i = 0; i < len1; i++) {
		std::cin >> series_1[i];
	}

	int * series_2 = new int[len2];
	for (int j = 0; j < len2; j++) {
		std::cin >> series_2[j];
	}	

	int len3 = 0;
	int * series_3 = setsUnion(series_1, series_2, len1, len2, &len3);
	for (int k = 0; k < len3; k++) {
		std::cout << series_3[k] << " ";
	}
	std::cout << std::endl;
	delete[] series_1;
	delete[] series_2;
	delete[] series_3;

	return 0;
}