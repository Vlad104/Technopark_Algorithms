/**

Нужная сумма
Ограничение времени	0.05 секунд
Ограничение памяти	5Mb
Ввод	стандартный ввод или input.txt
Вывод	стандартный вывод или output.txt
Даны два строго возрастающих массива целых чисел A[0..n) и B[0..m) и число k. Найти количество таких пар индексов (i, j), что A[i] + B[j] = k. Время работы O(n + m). n, m ≤ 100000.

Указание. Обходите массив B от конца к началу.

Пример
Ввод	
4
-5 0 3 18
5
-10 -2 4 7 12
7

Вывод
3

**/

 


#include <iostream>
#include <vector>

long sumsEqualsTo(std::vector<int> series_1, std::vector<int> series_2, long k) {

	long len1 = series_1.size();
	long len2 = series_2.size();

	long count = 0;
	long i = 0, j = len2 - 1, n = 0;
	// пока целиком не обойдем оба массива
	while ( n < len1 + len2 ) {
		if ( series_1[i] + series_2[j] == k ) {
			count++;

			if ((i == len1 - 1) && (j == 0)) {
				break;
			}
			
			if (i < len1 - 1) {
				i++;
			}
			if (j > 0) { 
				j--;
			}
		} else if (series_1[i] + series_2[j] < k) {
			if (i < len1 - 1) {
				i++;				
			} else if (j > 0) {
				j--;
			}
		} else {
			if (j > 0) {
				j--;				
			} else if (i < len1 - 1) {
				i++;
			}
		}

		n++;
	}

	return count;
}

int main() {
	long len1;
	std::cin >> len1;
	std::vector<int> series_1(len1);
	for (long i = 0; i < len1; i++) {
		std::cin >> series_1[i];
	}

	long len2;
	std::cin >> len2;
	std::vector<int> series_2(len2);
	for (long j = 0; j < len2; j++) {
		std::cin >> series_2[j];
	}

	long k;
	std::cin >> k;

	std::cout << sumsEqualsTo(std::move(series_1), std::move(series_2), k) << std::endl;
	return 0;

}