#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/stat.h>

int search(char* file, char* dir){

    DIR *dirptr = opendir(dir);
    struct dirent *entry = readdir(dirptr);

    while (entry != NULL) {

        if (strlen(entry->d_name) == strlen(file) &&
            strcmp(entry->d_name, file) == 0)
        {
            // success
            closedir(dirptr);
            return 0;   
        }

        entry = readdir(dirptr);
    }

    closedir(dirptr);
    return -1;   
}

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("Usage: %s file directory\n", argv[0]);
        return 1;
    }

    char *file = argv[1];
    char *dir = argv[2];

    if (search(file, dir) == 0) {

        printf("File found in directory\n");

        char path[500];
        sprintf(path, "%s/%s", dir, file);

        struct stat info;

        stat(path, &info);

        printf("File size: %ld bytes\n", info.st_size);
    }
    else {

        printf("File not found in directory\n");
    }

    return 0;
}