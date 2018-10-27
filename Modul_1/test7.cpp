/*
7_1. MSD для строк.
Дан массив строк. Количество строк не больше 105. 
Отсортировать массив методом поразрядной сортировки MSD по символам. 
Размер алфавита - 256 символов. Последний символ строки = ‘\0’.
In  
ab
a
aaa
aa  

Out
a
aa
aaa
ab
*/

#include <iostream>
#include <string>
#include <string.h>

const int alphabet_size = 256;


void clearData(char** array, const int array_size) {
    for (int i = 0; i < array_size; i++) {
        delete[] array[i];
    }
    delete[] array;
    array = nullptr;
}

void printData(char** array, const int array_size) {
    for (int i = 0; i < array_size; i++) {
        std::cout << array[i] << std::endl;
    }
}

void CountSort(char** array, int size, int* temp, int radix) {

    for (int i = 0; i < alphabet_size + 1; i++) {   
        temp[i] = 0;
    }    
    for (int i = 0; i < size; i++) {
        temp[(int)array[i][radix]]++;    
    }    
    for (int i = 1; i < alphabet_size + 1; i++) {
        temp[i] += temp[i - 1];    
    }     

    char** result = new char*[size];  

    for (int i = size - 1; i >= 0; i--) {
        result[temp[(int)array[i][radix]]-1] = array[i];   
        temp[(int)array[i][radix]]--;
    }    
    memcpy(array, result, size*sizeof(char*));
    delete[] result;
}

void MSD(char** array, int size, int radix = 0) {
    int* group = new int[alphabet_size+1];
    group[alphabet_size] = size;
    CountSort(array, size, group, radix);

    for (int i = 0; i < alphabet_size; i++) {
        int group_size = group[i+1] - group[i]; // кол-во строк с одиноковым началом

        // отбрасываем из группы "короткие" строки
        while (group_size > 1 && array[group[i]][radix] == '\0') {
            group[i]++;
            group_size--;
        }

        // рекурсивно вызываем MSD сортировку для строк с одинаковым началом
        if (group_size > 1) {
            MSD(array + group[i], group_size, radix + 1);
        }
    }
    delete[] group;
}

char** readData(int* p_array_size, int* p_array_buf_size) {    
    int array_size = 0;
    int array_buf_size = 100;
    char** array = new char*[array_buf_size];

    // построчно считываем в строки, преобразуем их в массив char
    std::string str = "";
    while(std::cin >> str) {
        char* line = new char[str.size() + 1];
        memcpy(line, str.c_str(), str.size()*sizeof(char));
        line[str.size()] = '\0';

        // реалоцируем память под массив строк
        if (array_size >= array_buf_size) {
            char** temp = new char*[2*array_buf_size];
            memcpy(temp, array, array_buf_size*sizeof(char*));
            array_buf_size *= 2;
            delete[] array;
            array = temp;
        }
        array[array_size] = line;
        array_size++;
    }
    *p_array_size = array_size;
    *p_array_buf_size = array_buf_size;
    return array;
}


int main(int argc, char const *argv[]) {
    int array_size = 0;
    int array_buf_size = 0;
    char** array = readData(&array_size, &array_buf_size);
  
    MSD(array, array_size);

    printData(array, array_size);
    clearData(array, array_size);

    return 0;
}