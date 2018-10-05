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

ID Решения: 12295310
**/

#include <iostream>
#include <vector>

std::vector<int> setsUnion(std::vector<int> series_1, std::vector<int> series_2) {

	size_t len1 = series_1.size();
	size_t len2 = series_2.size();
	std::vector<int> series_3; // пересечение множеств
	size_t i = 0, j = 0;
	size_t step_counter = 0;
	
	// обход массивов
	while (step_counter < len1 + len2) {
		step_counter++;
		if ( series_1[i] == series_2[j]) {
			series_3.push_back(series_1[i]);
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

	return series_3;
}

int main() {
	size_t len1, len2;
	std::cin >> len1 >> len2;
	std::vector<int> series_1(len1);
	for (size_t i = 0; i < len1; i++) {
		std::cin >> series_1[i];
	}

	std::vector<int> series_2(len2);
	for (size_t j = 0; j < len2; j++) {
		std::cin >> series_2[j];
	}	

	std::vector<int> series_3 = setsUnion(std::move(series_1), std::move(series_2));
	for ( auto element : series_3) {
		std::cout << element << " ";
	}
	std::cout << std::endl;

	return 0;
}