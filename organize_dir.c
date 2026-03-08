#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>

struct Node {
    char ext[20];
    struct Node *next;
};

struct Node *head = NULL;

void insert(char *ext) {
    struct Node *newNode = malloc(sizeof(struct Node));
    strcpy(newNode->ext, ext);
    newNode->next = head;
    head = newNode;
}

int excluded(char *ext) {
    struct Node *curr = head;
    while (curr != NULL) {
        if (strcmp(curr->ext, ext) == 0)
            return 1;
        curr = curr->next;
    }
    return 0;
}


void loadFile(char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening the file");
        exit(1);
    }
    char buffer[1000];

    int bytes = read(fd, buffer, 999);
    buffer[bytes] = '\0';

    char *token = strtok(buffer, " \n");
    while (token != NULL) {
        insert(token);
        token = strtok(NULL, " \n");
    }

    close(fd);
}


/* organize files */
void organize(char *directory) {

    DIR *dir = opendir(directory);

    if (!dir) {
        perror("error opening directory");
        exit(1);
    }

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {

        if (entry->d_type != DT_REG)
            continue;

        char *dot = strrchr(entry->d_name, '.');

        if (dot == NULL)
            continue;

        char *ext = dot;
        char *extOnly = dot+1;

        if (excluded(ext))
            continue;

        char folder[500];
        sprintf(folder, "%s/%s", directory, extOnly);

        mkdir(folder, 0755);

        char oldPath[500];
        char newPath[500];

        sprintf(oldPath, "%s/%s", directory, entry->d_name);
        sprintf(newPath, "%s/%s/%s", directory, extOnly, entry->d_name);

        rename(oldPath, newPath);
    }

    closedir(dir);
}


int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("Usage: %s directory exclude_file\n", argv[0]);
        return 1;
    }

    loadFile(argv[2]);

    organize(argv[1]);

    return 0;
}