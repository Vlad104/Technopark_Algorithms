#include <iostream>
#include <vector>

std::vector<int> setsUnion(std::vector<int> series_1, std::vector<int> series_2) {

	size_t len1 = series_1.size();
	size_t len2 = series_2.size();
	std::vector<int> series_3;
	size_t i = 0, j = 0, k = 0;;
	while (k < len1 + len2) {
		k++;
		if ( series_1[i] == series_2[j]) {
			series_3.push_back(series_1[i]);
			if ( i < len1 - 1 ) {
				i++;
			} 
			if ( j < len2 - 1 ) {
				j++;
			} 
			if ( (i == len1 - 1) && (j == len2 - 1) ) {
				break;
			}
		} else if ( series_1[i] < series_2[j]) {
			if ( i < len1 - 1 ) {
				i++;
			} else {
				break;
			}
		} else {
			if ( j < len2 - 1 ) {
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