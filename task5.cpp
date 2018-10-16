#include <iostream>
//#include <algorithms>

struct Line {
	int x1;
	int x2;
	Line(int _x1, int _x2) : x1(_x1), x2(_x2) {}
};

int main() {

	int n;
	std::cin >> n;
	Line line = new Line[n];
	for (int i = 0; i < n; i++) {
		std::cin >> line[i].x1 >> line[i].x2;
	}


	return 0;
}