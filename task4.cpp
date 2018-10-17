/*
Задача 4.2
Для сложения чисел используется старый компьютер. Время, затрачиваемое на нахождение суммы двух чисел равно их сумме.
Таким образом для нахождения суммы чисел 1,2,3 может потребоваться разное время, в зависимости от порядка вычислений.
((1+2)+3) -> 1+2 + 3+3 = 9
((1+3)+2) -> 1+3 + 4+2 = 10
((2+3)+1) -> 2+3 + 5+1 = 11
Требуется написать программу, которая определяет минимальное время, достаточное для вычисления суммы заданного набора чисел.
Формат входных данных. Вначале вводится n - количество чисел. Затем вводится n строк - значения чисел (значение каждого числа не превосходит 10^9, сумма всех чисел не превосходит 2*10^9).
Формат выходных данных. Натуральное число - минимальное время.
in
out
5
5 2 3 4 6
45

5
3 7 6 1 9
56

*/

#include <iostream>
#include <cassert>

class MinHeap {
public:
	explicit MinHeap(int bufferSize);
	~MinHeap() {delete[] buffer_;};
	MinHeap(const MinHeap&) = delete;
	MinHeap(MinHeap&) = delete;
	MinHeap& operator=(const MinHeap&) = delete;
	MinHeap& operator=(MinHeap&) = delete;

	//void Add(const int& element);
	void Add(int element);
	int ExtractMax();
	const int& GetMax() const;
	void BuildHeap();
	bool isEmpty() {return size_ <= 0;}
	int  size() {return size_;}

	

private:
	void SiftDown(int elementNum);
	void SiftUp(int elementNum);
	void AllocateNewMem();
	int* buffer_;
	int bufferSize_;
	int size_;

};

MinHeap::MinHeap(int bufferSize) {
	size_ = 0;
	bufferSize_ = bufferSize;
	buffer_ = new int[bufferSize];
}

void MinHeap::AllocateNewMem() {
	int* temp = new int[bufferSize_*2];
	for (int i = 0; i < bufferSize_; i++) {
		temp[i] = buffer_[i];
	}
	delete[] buffer_;
	buffer_ = temp;
	bufferSize_ *= 2;
}

void MinHeap::BuildHeap() {
	for (int i = size_ / 2 - 1; i >= 0; i--) {
		SiftDown(i);
	}
}

// проталкивание элемента вниз
void MinHeap::SiftDown(int elementNum) { // for MinHeap
	int left  = 2 * elementNum + 1;
	int right = 2 * elementNum + 2;
	int least = elementNum;

	if (left < size_ && buffer_[left] < buffer_[elementNum]) {
		least = left;
	}
	if (right < size_ && buffer_[right] < buffer_[least]) {
		least = right;
	}
	if (least != elementNum) {
		std::swap(buffer_[elementNum], buffer_[least]);
		SiftDown(least);
	}
}

void MinHeap::SiftUp(int elementNum) { // for MinHeap
	while (elementNum > 0) {
		int parent = (elementNum - 1) / 2;
		if (buffer_[elementNum] >= buffer_[parent]) {
			return;
		}
		std::swap(buffer_[elementNum], buffer_[parent]);
		elementNum = parent;
	}
}

void MinHeap::Add(int element) {
	if (bufferSize_ <= size_) {
		AllocateNewMem();
	}
	buffer_[size_] = element;
	size_++;
	SiftUp(size_ - 1);
}

int MinHeap::ExtractMax() {
	// if is not empty
	int result = buffer_[0];
	buffer_[0] = buffer_[size_ - 1];
	size_--; // delete last element
	if (size_ > 0) {
		SiftDown(0);
	}
	return result;
}


int main() {
	int n;
	std::cin >> n;
	MinHeap* heap = new MinHeap(n);
	for (int i = 0; i < n; i++) {
		int element;
		std::cin >> element;
		heap->Add(element);
	}
	int sum = 0;
	while(heap->size() > 1) {
		int element_1 = heap->ExtractMax();
		int element_2 = heap->ExtractMax();
		int temp_sum = element_1 + element_2;
		heap->Add(temp_sum);
		sum += temp_sum;
	}

	std::cout << sum << std::endl;

	return 0;
}