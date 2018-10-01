#include <iostream>
#include <vector>

int task(std::vector<int> series_1, std::vector<int> series_2, int k) {

	int len1 = series_1.size();
	int len2 = series_2.size();

	size_t i = 0, j = len2 - 1, count = 0;
	int diff_1 = 0, diff_2 = 0;
	int n = 0;
	while (n < len1 + len2) {
		if ( series_1[i] + series_2[j] == k ) {
			count++;
			i++;
			j--;
		} else if (series_1[i] + series_2[j] < k) {
			if (i < len1) {
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
	size_t len1;
	std::cin >> len1;
	std::vector<int> series_1(len1);
	for (size_t i = 0; i < len1; i++) {
		std::cin >> series_1[i];
	}

	size_t len2;
	std::cin >> len2;
	std::vector<int> series_2(len2);
	for (size_t j = 0; j < len2; j++) {
		std::cin >> series_2[j];
	}

	int k;
	std::cin >> k;

	std::cout << task(std::move(series_1), std::move(series_2), k) << std::endl;

}