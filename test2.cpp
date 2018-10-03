#include <iostream>
#include <vector>

std::vector<int> task(std::vector<int> series_1, std::vector<int> series_2) {

	int len1 = series_1.size();
	int len2 = series_2.size();
	std::vector<int> series_3;
	size_t i = 0, j = 0, count = 0;
	while (i + j < len1 + len2) {
		if ( series_1[i] == series_2[j]) {
			series_3.push_back(series_1[i]);
			i++;
			j++;
		} else if ( series_1[i] < series_2[j]) {
			i++;
		} else {
			j++;
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

	std::vector<int> series_3 = task(std::move(series_1), std::move(series_2));
	for ( auto element : series_3) {
		std::cout << element << " ";
	}
	std::cout << std::endl;

	return 0;
}