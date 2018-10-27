class Heap {
public:
	explicit Heap(int bufferSize);
	~Heap() {delete[] buffer_;};
	Heap(const Heap&) = delete;
	Heap(Heap&) = delete;
	Heap& operator=(const Heap&) = delete;
	Heap& operator=(Heap&) = delete;

	//void Add(const int& element);
	void Add(int element);
	int ExtractMax();
	const int& GetMax() const;
	void BuildHeap();
	

private:
	void SiftDown(int elementNum);
	void SiftUp(int elementNum);
	void AllocateNewMem();
	int* buffer_;
	int bufferSize_;
	int size_;

};

Heap::Heap(int bufferSize) {
	size_ = 0;
	bufferSize_ = bufferSize;
	buffer_ = new int[bufferSize];
}

void Heap::AllocateNewMem() {
	int* temp = new int[bufferSize_*2];
	for (int i = 0; i < bufferSize_; i++) {
		temp[i] = buffer_[i];
	}
	delete[] buffer_;
	buffer_ = temp;
	bufferSize_ *= 2;
}

void Heap::BuildHeap() {
	for (int i = size_ / 2 - 1; i >= 0; i--) {
		SiftDown(i);
	}
}

// проталкивание элемента вниз
void Heap::SiftDown(int elementNum) {
	int left  = 2 * elementNum + 1;
	int right = 2 * elementNum + 2;
	int largest = elementNum;

	if (left < size_ && buffer_[left] > buffer_[elementNum]) {
		largest = left;
	}
	if (right < size_ && buffer_[right] > buffer_[largest]) {
		largest = right;
	}
	if (largest != elementNum) {
		std::swap(buffer_[elementNum], buffer_[largest]);
		SiftDown(largest);
	}
}

void Heap::SiftUp(int elementNum) {
	while (elementNum > 0) {
		int parent = (elementNum - 1) / 2;
		if (buffer_[elementNum] <= buffer_[parent]) {
			return;
		}
		std::swap(buffer_[elementNum], buffer_[parent]);
		elementNum = parent;
	}
}

void Heap::Add(int element) {
	if (bufferSize_ <= size_) {
		AllocateNewMem();
		std::cout << "Alloc" << std::endl;
	}
	buffer_[size_] = element;
	std::cout << "Element = " << element << "  size = " << size_ << std::endl;
	size_++;
	SiftUp(size_ - 1);
}

int Heap::ExtractMax() {
	// if is not empty
	int result = buffer_[0];
	buffer_[0] = buffer_[size_ - 1];
	size_--; // delete last element
	if (size_ > 0) {
		SiftDown(0);
	}
	return result;
}