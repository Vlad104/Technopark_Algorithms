#include <iostream>

struct Line {
	int x1;
	int x2;
	//Line(int _x1, int _x2) : x1(_x1), x2(_x2) {}
};

void BubbleSort(Line* line, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - 1 - i; j++) {
			if (line[j].x1 > line[j+1].x1) {
				std::swap(line[j], line[j+1]);
			}
		}
	}
}

int main() {

	int n;
	std::cin >> n;
	Line* line = new Line[n];
	for (int i = 0; i < n; i++) {
		std::cin >> line[i].x1 >> line[i].x2;
	}

	BubbleSort(line, n);
	int i = 0;
	int k = 0;
	int dot = 0;
	dot = line[0].x1;
	while(i < n - 1) {
		int distance = line[i+1].x1 - dot;
		int length = line[i].x2 - dot;
		k += std::min(length, distance);
		if ( (line[i].x2 < line[i+1].x1) ) {
			dot = line[i+1].x1;
		}
		else {
			dot = line[i].x2;
		}
		i++;
		if (i == n - 1) {
			k += line[i].x2 - dot;
		}
	}

	//for (int i = 0; i < n; i++) {
	//	std::cout << "[" << line[i].x1 << ", " << line[i].x2 << "]" << std::endl; 
	//}
	std::cout << k << std::endl;

	delete[] line;
	return 0;
}