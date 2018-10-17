#include <iostream>
#include <vector>

int main(int argc, char const *argv[])
{
	std::vector<int> array;
	int element = 0;
	while (std::cin >> element) {
		array.push_back(element);
	}
	return 0;
}