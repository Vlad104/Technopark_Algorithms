#include <iostream>

struct IntPair {
	int first;
	int second;

	IntPair(int _first, int _second) : first(_first), second(_second) {}
};

// Куча для хранения пар <значение, индекс>
class Heap {
public:
	explicit Heap(int buffer_size);
	~Heap() {delete[] buffer_};
	Heap(const Heap&) = delete;
	Heap(Heap&) = delete;
	Heap& operator=(const Heap&) = delete;
	Heap& operator=(Heap&) = delete;

	void Add(const IntPair& element);
	IntPair ExtractMax();
	const IntPair& GetMax() const;
	

private:
	IntPair* buffer_;
	int buffer_Size_;
	int size_;

};



int main() {
	//Heap heap(40);

	return 0;
}