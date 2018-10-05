class MyDeck
{
public:
	MyDeck();
	MyDeck(long deckSize);
	~MyDeck();
	
	void push_front(int number);
	void push_back(int number);
	int pop_front();
	int pop_back();

private:
	long deckSize;
	bool isDeckEmpty();
};

MyDeck::MyDeck(long deckSize) {
	this.deckSize = deckSize;
}

void MyDeck::push_front(int number) {

}


int main() {
	int n;
	std::cin >> n;
	for (int i = 0; i < n; i++) {
		int command;
		std::cin >> command;
		std::cin >> number;
		switch (command) {
			case 1:

				break;
			case 2:
			
				break;
			case 3:
			
				break;
			case 4:
			
				break;
			default :
			
				break;
		}
	}
}