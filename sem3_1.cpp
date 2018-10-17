#include <iostream>
#include <vector>

int Partition(std::vector<int>& array, int left, int right) {
	int pivot = array[right - 1];
	int i = left;
	int j = right - 2;
	while ( i <= j ) {
		for (; array[i] < pivot; ++i);
		for (; array[j] >= pivot && j >= left; --j);
		if (i < j) {
			std::swap(array[i], array[j]);
			++i;
			--j;
		}
	}
	std::swap(array[i], array[right - 1]);
	return i;
}

// Поиск k-ой порядковой статистики, возвращаем её значение
int KStatistic(std::vector<int>&  array, int k) {
	int left = 0;
	int right = static_cast<int>(array.size());
	while (true) {
		int pivot_index = Partition(array, left, right);
		if (pivot_index == k) {
			return array[k];
		}
		if (pivot_index < k) {
			left = pivot_index + 1;
		}
		else {
			right = pivot_index;
		}
	}
}

int main(int argc, char const *argv[]) {
	size_t n = 0;
	std::cin >> n;
	int k = 0;
	std::cin >> k;

	std::vector<int> array(n, 0);

	for (int i = 0; i < n; i++) {
		std::cin >> array[i];
	}
	const int result = KStatistic(array, k);
	std::cout << result << std::endl;

	return 0;
}