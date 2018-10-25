#include <iostream>
#include <string>
#include <vector>

const int alphabet_size = 256;

char* CountSort(char* line, int size) {
    int* temp = new int[alphabet_size + 1];
    char* result = new char[size];  

    for (int i = 0; i < alphabet_size + 1; i++) {   
        temp[i] = 0;
    }    
    for (int i = 0; i < size; i++) {
        temp[(int)line[i]]++;    
    }    
    for (int i = 1; i < alphabet_size + 1; i++) {
        temp[i] += temp[i - 1];    
    } 
    for (int i = size - 1; i >= 0; i--) {
        result[temp[(int)line[i]]-1] = line[i];   
        temp[(int)line[i]]--;
    }
    return result;
    delete[] temp;
}

void MSD(char** array, int size, int radix = 0) {
    int group_pos = 0;
    while (group_pos < size) { ///??????
        char* line = new char[size];
        for (int i = 0; i < size; i++) {
            line[i] = array[i][radix];
        }
        array = CountSort(array, size, radix); ///
        int group_size = 0;
        while ( array[0][radix] == array[group_size][radix] ) {
            group_size++;
        }
        MSD(line, group_size, radix + 1);
        group_pos++;
    }
}

int reallocate(char* buffer, int buff_size) {
    char* temp = new char[2*buff_size];
    memcpy(temp, buffer, buff_size*sizeof(char));
    buff_size *= 2;
    delete[] buffer;
    buffer = temp;
    return buff_size;
}

char** readData(int* p_array_size, int* p_array_buf_size) {    
    int array_size = 0;
    int array_buf_size = 100;
    char** array = new char*[array_buf_size];

    std::string str = "";
    while(std::cin >> str) {
        char* line = new char[str.size()];
        memcpy(line, str.c_str(), str.size()*sizeof(char));
        if (array_size >= array_buf_size) {
            array_buf_size = reallocate(*array, array_buf_size);
        }
        array[array_size] = line;
        array_size++;
        //line = nullptr;
        //str = "";
    }
    *p_array_size = array_size;
    *p_array_buf_size = array_buf_size;
    return array;
}

void clearData(char** array, const int array_size, const int array_buf_size) {

    for (int i = 0; i < array_size; i++) {
        std::cout << array[i] << std::endl;
    }

    for (int i = 0; i < array_size; i++) {
        delete[] array[i];
    }
    delete[] array;
}

int main(int argc, char const *argv[]) {
    int array_size = 0;
    int array_buf_size = 0;
    char** array = readData(&array_size, &array_buf_size);

    char line[9] = "72312221";
    char* res = CountSort(line, 9);    
    for (int i = 0; i < 9; i++) {
        std::cout << res[i] << " ";
    }
    std::cout << std::endl;

    clearData(array, array_size, array_buf_size);

    return 0;
}