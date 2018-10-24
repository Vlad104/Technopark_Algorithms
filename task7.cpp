#include <iostream>
#include <string>
#include <vector>

const int alphabet_size = 256;

void count_sort(char* line, int size) {
    char* temp(alphabet_size + 1);
    char* result(n);     
    for (int i = 0; i < M; i++) {   
        temp[i] = 0;
    }    
    for (int i = 0; i < n; i++) {
        temp[line[i]] = temp[line[i]] + 1;    
    }    
    for (int i = 1; i < M; i++) {
        temp[i] = temp[i] + temp[i - 1];    
    } 
    for (int i = n - 1; i >= 0; i--) {
        result[temp[line[i]]-1] = line[i];   
        temp[line[i]] = temp[line[i]] - 1;
    }
    line = result;

    delete[] temp;
    delete[] result;
}

void MSD(char** array, int size, int radix = 0) {
    int group_pos = 0;
    while (group_pos < size) { ///??????
        CountSort(array, size, radix);
        int group_size = 0;
        while ( array[0][radix] == array[group_size][radix] ) {
            group_size++;
        }
        MSD(array, group_size, radix + 1);
        group_pos++;
    }
}

int reallocate(char* buffer, int buff_size) {
    char* temp[2*buff_size];
    memcpy(temp, buffer, buff_size*sizeof(char));
    buff_size *= 2;
    buffer = temp;
    delete[] temp;
    return buff_size;
}

int main(int argc, char const *argv[])
{
    int array_buf_size = 100;
    char** array = new char*[array_buf_size];
    int array_size = 0
    while(std::cin) {
        int str_size = 100;
        char* str = new char[str_size];
        int str_index = 0
        char symbol = getchar();
        while(symbol != '\0') {
            if (str_index >= str_size) {
                str_size = reallocate(str, &str_size);
            }
            str[str_index] = symbol;
            str_index++;
        }
        str[str_index] = '\0';
        if (array_size >= array_buf_size) {
            reallocate(*array, array_buf_size);
        }
        array[array_size] = str;
        array_size++;
        delete[] str;
    }

	for (int i = 0; i < array_buf_size; i++) {
        delete[] array[i];
    }
    delete[] array;
    return 0;
}