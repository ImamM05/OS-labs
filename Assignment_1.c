#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/type.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define BUFFER_AMT 4
#define CHAR_LENGTH 100

struct DynamicArray {
    char **list;
    int size;
    int capacity;
};

void da_init(struct DynamicArray *arr) {
    arr->capacity = 5;
    arr->list = malloc(arr->capacity*sizeof(char *));
    arr->size = 0;
}

int da_resize(struct DynamicArray *arr) {
    int newCap = arr->capacity*2;
    char** newList = malloc((newCap)*sizeof(char *));
    if (newList == NULL) {
        return -1;
    }
    for (unsigned int i = 0; i < arr->size; i++) {
        newList[i] = arr->list[i];
    }
    arr->capacity = newCap;
    free(arr->list);
    arr->list = newList;
    return 0;
}

int da_insert_back(struct DynamicArray *arr, char* word) {
    if (arr->size == arr->capacity) {
        if (da_resize(arr) == -1) {
            return -1;
        }
    }
    arr->list[arr->size++] = word;
    return 0;
}

void da_del(struct DynamicArray *arr){
    free(arr->list);
}

int main(int argc, char* argv[]) {
    char buf[BUFFER_AMT];

    if (argc < 2) {
        printf("Error: Missing filepath and txt file, ex: %s <filepath> <filename>\n", argv[0]);
        return -1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return -1;
    }
    ssize_t bytesRead = read(fd, buf, 4);
    if (bytesRead == -1) {
        perror("Error reading file %s", argv[1]);
        return -1;
    }



    free(buf);
    close(fd);
    return 0;
    
}