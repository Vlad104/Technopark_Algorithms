#include <iostream>
#include <cstdlib>
#include <ctime>

int Partition(int* array, int left, int right) {
	if (left == right) {
		return left;
	}
	srand(time(NULL));
	int rand_pivot_index = left + (rand() % (right - left));
	int pivot = array[rand_pivot_index];
	std::swap(array[rand_pivot_index], array[left]);
	// now pivot in left position

	int i = right + 1;
	int j = right;
	while ( j > left ) {
		if (pivot < array[j]) {
			i--;		
			std::swap(array[i], array[j]);
		}
		j--;	
	}
	i--;		
	std::swap(array[i], array[j]);	
	//std::cout << "i = " << i << std::endl;
	return i;
}

// Поиск k-ой порядковой статистики, возвращаем её значение
int KStatistic(int* array, int size, int k) {
	int left = 0;
	int right = size - 1;
	while (true) {
		const int pivot_index = Partition(array, left, right);
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
	std::ios_base::sync_with_stdio(false);
	int n = 0;
	int k = 0;
	std::cin >> n >> k;

	int* array = new int[n];
	for (int i = 0; i < n; i++) {
		std::cin >> array[i];
	}
	const int result = KStatistic(array, n, k);
	std::cout << result << std::endl;

	delete[] array;
	return 0;
}