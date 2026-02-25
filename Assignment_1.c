#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/type.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define BUFFER_AMT 10000
#define CHAR_LENGTH 100

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Error: Missing filepath and txt file, ex: %s <filepath> <filename>\n", argv[0]);
        return -1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return -1;
    }

    char* buf = (char*)calloc(BUFFER_AMT, sizeof(char));
    if (buf == NULL) {
        perror("Memory allocation failed.");
        return -1;
    }

    ssize_t byteRead = read(fd, buf, BUFFER_AMT);
    if (byteRead == -1){
        perror("Error reading file");
        return -1;
    }
    char token[CHAR_LENGTH];
    int j = 0;

    // process bytes read from file
    for (unsigned int i = 0; i < byteRead; i++) {
        if (j < CHAR_LENGTH - 1 && isalnum(buf[i])) {
            token[j++] = buf[i];
        } else if (j==CHAR_LENGTH -1) {
            perror("Error token is longer than memory reserved for characters.")
        } else {
            if (j > 0) {
                token[j] = '\0';
                printf("%s\n", token);
                j = 0;
            }
        }
    }
    if (j > 0) {
        token[j] = '\0';
        printf("%s\n", token);
        j = 0;
    }


    free(buf);
    close(fd);
    return 0;
    
}