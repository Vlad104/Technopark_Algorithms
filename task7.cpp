#include <iostream>
#include <string>
#include <vector>

const int alphabet_size = 256;

void count_sort(vector<int> &A, int m) {
    std::vector<int> A(n);
    std::vector<int> B(M+1);
    std::vector<int> C(n);
    for (int i = 0; i < n; i++) {
        std::cin >> A[i];    
    }        
    for (int i = 0; i < M; i++) {   
        B[i] = 0;
    }    
    for (int i = 0; i < n; i++) {
        B[A[i]] = B[A[i]] + 1;    
    }    
    for (int i = 1; i < M; i++) {
        B[i] = B[i] + B[i - 1];    
    } 
    for (int i = n - 1; i >= 0; i--) {
        C[B[A[i]]-1] = A[i];   
        B[A[i]] = B[A[i]] - 1;
    }
}


void msd(std::vector<std::string>& array, int size) {
	char* bytes = new char[size];
	
}

int main(int argc, char const *argv[])
{
	std::vector<std::string> array;
	while (true) {
		std::string str;
		getline(std::cin, str);
		if (str.empty()) {
			break;
		}
		array.push_back(str);
	}


	return 0;
}