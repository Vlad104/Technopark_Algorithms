/**
Дек с динамическим буфером
Ограничение времени	1 секунда
Ограничение памяти	5Mb
Ввод	стандартный ввод или input.txt
Вывод	стандартный вывод или output.txt
Реализовать дек с динамическим зацикленным буфером.

Обрабатывать команды push * и pop *.

Формат ввода
В первой строке количество команд n. n ≤ 1000000.

Каждая команда задаётся как 2 целых числа: a b.

a = 1 - push front
a = 2 - pop front
a = 3 - push back
a = 4 - pop back
Если дана команда pop *, то число b - ожидаемое значение. 
Если команда pop * вызвана для пустой структуры данных, то ожидается “-1”.

Пример 1
Ввод
3
1 44
3 50
2 44
Вывод
YES

Пример 2
Ввод	
2
2 -1
1 10
Вывод
YES

Пример 3
Ввод	
2
3 44
4 66
Вывод
NO
**/

#include <iostream>
#include <cassert>

class Deck {
public:
	Deck(int bufSize);
	~Deck() {delete[] buf_;};
	Deck(const Deck&) = delete;
	Deck(Deck&) = delete;
	Deck& operator=(const Deck&) = delete;
	Deck& operator=(Deck&) = delete;
	
	void pushFront(int const number);
	void pushBack(int const number);
	int popFront();
	int popBack();
	long size();

private:
	void allocateNewMem();
	void clearExtraMemory();
	int* buf_;
	long bufSize_;
	long head_;
	long tail_;
};

Deck::Deck(int bufSize = 1) {
	bufSize_ = bufSize;
	buf_ = new int[bufSize_];
	head_ = 0;
	tail_ = 0;
}

// возвращает колличество элементов в буффере
long Deck::size() {
	return (tail_ >= head_) ? tail_ - head_ : bufSize_ - head_ + tail_;
}

// выделение дополнительной памяти
void Deck::allocateNewMem() {
	int* newBuf = new int[bufSize_*2];
	assert(newBuf != nullptr);
	//memcpy(newBuf, buf_, bufSize_);
	for (long i = 0; i < bufSize_; i++) {
		newBuf[i] = buf_[head_];
		head_ = (head_ + 1) % bufSize_;
	}
	delete[] buf_;
	buf_ = newBuf;
	head_ = 0;
	tail_ = bufSize_ - 1;
	bufSize_ *= 2;
	return;
}

/*
// освобождение лишней памяти
void Deck::clearExtraMemory() {
	if (size() < bufSize_ / 4) {
		int* newBuf = new int[bufSize_/2];
		assert(newBuf != nullptr);
		long newBufSize = size();
		//memcpy(newBuf, buf_, newBufSize);
		for (long i = 0; i < newBufSize; i++)	{
			newBuf[i] = buf_[head_];
			head_ = (head_ + 1) % bufSize_;
		}
		delete[] buf_;
		buf_ = newBuf;
		head_ = 0;
		tail_ = newBufSize - 1;
		bufSize_ /= 2;
	}	
	return;
}
*/

// добавление элемента в начало дека
void Deck::pushFront(int const number) {
	if ( ( head_ == (tail_ + 1) % bufSize_) ) {
		allocateNewMem();
	}
	head_ = (head_ - 1 + bufSize_) % bufSize_;
	buf_[head_] = number;
	return;
}

// добавление элемента в конец дека
void Deck::pushBack(int const number) {
	if ( ( head_ == (tail_ + 1) % bufSize_) ) {
		allocateNewMem();
	}
	buf_[tail_] = number;
	tail_ = (tail_ + 1) % bufSize_;
	return;
}

// извлечение элемента из начала дека
int Deck::popFront() {
	if (size() > 0) {
		//clearExtraMemory();
		int popNumber = buf_[head_];
		head_ = (head_ + 1) % bufSize_;
		return popNumber;
	}
	else {
		return -1;
	}
}

// извлечение элемента с конца дека
int Deck::popBack() {
	if (size() > 0) {
		//clearExtraMemory();
		tail_ = (tail_ - 1 + bufSize_) % bufSize_;
		int popNumber = buf_[tail_];
		return popNumber;
	}
	else {
		return -1;
	}
}

int main() {
	long n = 0;
	std::cin >> n;
	Deck* deck = new Deck();
	bool isCorrect = true; // флаг корректной работы с деком
	for (long i = 0; i < n; i++) {
		int command = 0;
		int number = 0;
		std::cin >> command >> number;
		switch (command) {
			case 1:
				deck->pushFront(number);
				break;
			case 2:
				if (number != deck->popFront()) {
					isCorrect = false;
				}
				break;
			case 3:
				deck->pushBack(number);			
				break;
			case 4:
				if (number != deck->popBack()) {
					isCorrect = false;
				}			
				break;
			default :
				isCorrect = false;		
				break;
		}
		if (!isCorrect) {
			break;
		}
	}	
	if (isCorrect) {
		std::cout << "YES" << std::endl;
	}
	else {
		std::cout << "NO" << std::endl;
	}
	delete deck;
	return 0;
}