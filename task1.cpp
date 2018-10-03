#include <iostream>
#include <vector>

long sumsEqualsTo(std::vector<int> series_1, std::vector<int> series_2, long k) {

	long len1 = series_1.size();
	long len2 = series_2.size();

	long count = 0;
	long i = 0, j = len2 - 1, n = 0;
	while ( n < len1 + len2 ) {
		if ( series_1[i] + series_2[j] == k ) {
			count++;
			if (i < len1 - 1) {
				i++;
			}
			if (j > 0) { 
				j--;
			}
		} else if (series_1[i] + series_2[j] < k) {
			if (i < len1 - 1) {
				i++;				
			}
		} else {
			if (j > 0) {
				j--;				
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