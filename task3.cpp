#include <iostream>

class Deck {
public:
	//Deck();
	Deck(int bufSize);
	~Deck();
	
	void pushFront(int const number);
	void pushBack(int const number);
	int popFront();
	int popBack();
	int size();

private:
	void clearExtraMemory();
	int* buf_;
	int bufSize_;
	int head_;
	int tail_;
};

Deck::Deck(int bufSize) {
	bufSize_ = bufSize;
	buf_ = new int(bufSize_);
}

int Deck::size() {
	if (tail_ > head_) {
		//return bufSize_ - head_ + tail_;
		return tail_ - head_;
	}
	else {
		//return tail_ - head_;
		return bufSize_ - head_ + tail_;
	}
}

void Deck::pushFront(int const number) {
	if (head_ == (tail_ + 1) % bufSize_) {
		int * newBuf = new int[bufSize_*2];
		for (size_t i = 0; i < bufSize_; i++) {
			newBuf[i] = buf_[head_];
			head_ = (head_ + 1) % bufSize_;
		}
		delete[] buf_;
		buf_ = newBuf;
		head_ = 0;
		tail_ = bufSize_;
		//tail_ = bufSize_ - 1;
		bufSize_ *= 2;
	}
	head_ = (head_ - 1 + bufSize_) % bufSize_;
	buf_[head_] = number;
	return;
}

void Deck::pushBack(int const number) {
	if (head_ == (tail_ + 1) % bufSize_) {
		int * newBuf = new int[bufSize_*2];
		for (size_t i = 0; i < bufSize_; i++) {
			newBuf[i] = buf_[head_];
			head_ = (head_ + 1) % bufSize_;
		}
		delete[] buf_;
		buf_ = newBuf;
		head_ = 0;
		tail_ = bufSize_;
		//tail_ = bufSize_ - 1;
		bufSize_ *= 2;
	}
	//buf_[tail_] = number;
	//tail_ = (tail_ - 1 + bufSize_) % bufSize_;
	buf_[tail_] = number;
	tail_ = (tail_ + 1) % bufSize_;
	return;
}

void Deck::clearExtraMemory() {
	if (size() < bufSize_ / 4) {
		int * newBuf = new int[bufSize_/2];
		int newBufSize = size();
		for (size_t i = 0; i < newBufSize; i++)	{
			newBuf[i] = buf_[head_];
			head_ = (head_ + 1) % bufSize_;
		}
		delete[] buf_;
		buf_ = newBuf;
		head_ = 0;
		tail_ = newBufSize;
		bufSize_ /= 2;
	}	
}

int Deck::popFront(){
	if (size() > 0) {
		clearExtraMemory();
		int popNumber = buf_[head_];
		head_ = (head_ + 1) % bufSize_;
		return popNumber;
	}
	else {
		return -1;
	}
}

int Deck::popBack(){
	if (size() > 0) {
		clearExtraMemory();
		//int popNumber = buf_[tail_];
		//tail_ = (tail_ - 1 + bufSize_) % bufSize_;
		tail_ = (tail_ - 1 + bufSize_) % bufSize_;
		int popNumber = buf_[tail_];
		return popNumber;
	}
	else {
		return -1;
	}
}

int main() {
	int n;
	std::cin >> n;
	//Deck deck(n);
	Deck * deck = new Deck(n);
	bool isCorrect = true;
	for (int i = 0; i < n; i++) {
		int command, number, temp = 0;
		std::cin >> command >> number;
		switch (command) {
			case 1:
				deck->pushFront(number);
				break;
			case 2:
				temp = deck->popFront();
				printf("%d == %d\n", temp, number);
				if (number != temp) {
					isCorrect = false;
				}
				break;
			case 3:
				deck->pushBack(number);			
				break;
			case 4:
				temp = deck->popBack();
				printf("%d == %d\n", temp, number);
				if (number != temp) {
					isCorrect = false;
				}			
				break;
			default :			
				break;
		}
	}
	if (isCorrect) {
		std::cout << "YES" << std::endl;
	}
	else {
		std::cout << "NO" << std::endl;
	}
}