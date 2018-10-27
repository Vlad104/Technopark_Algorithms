#include <iostream>
//#include <algorithms>

struct CPoint {
	int x;
	int y;
	CPoint(int _x, int _y) : x(_x), y(_y) {}
	bool operator<(const CPoint& other);
};

bool CPoint::operator<(const CPoint& other) {
	if (x == other.x) {
		return y < other.y;
	}
	return x < other.x;
}


// Var2. Use function
void BubbleSort(CPoint* array, int size, bool (*compare (const CPoint&, const CPoint&))) {
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (array[j] < array[j+1]) {
				std::swap(array[j], array[j+1]);
			}
		}
	}
}

// Var3. Use all that you want
template<class Compare>
void BublleSort2(CPoint* array, int size, Cpmpare& compare)

bool CompareByDistanceFromZero(const CPoint& first, const CPoint& second) {
	return (first.x*first.x + first.y*first.y) < (second.x*second.x + second.y*second.y);

}

class CompareFunctor {
public:
	explicit CompareFunctor(const Point& center) : center_(center) {}
	bool operator()(const CPoint& first, const &CPoint& second) {
		int first_x_diff = first.x - center_.x;
		int first_y_diff = first.y - center_.y;
		int second_x_diff = second.x - center_.x;
		int second_y_diff = second.y - center_.y;
		return (first_x_diff*first_x_diff + second_x_diffy*second_x_diff) < (second_x_diff*second_x_diff + second_y_diff* second_y_diff);
	}
}

int main() {
	CPoint array[5] = { CPoint(2,2), CPoint(0,2), CPoint(1,1), CPoint(2,0), CPoint(1,0)};
	//BubbleSort(array, 5);
	BubbleSort(array, 5, CompareByDistanceFromZero);

	for(const CPoint& point: array) {
		std::cout << "[" << point.x << ", " << point.y << "]"<< std::endl;
	}
	return 0;
}