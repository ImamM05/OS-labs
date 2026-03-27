// Name: Imam Mishkat

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   
#include <fcntl.h>    

struct node {
    int data;
    struct node *next;
    struct node *prev;
};

struct node *head = NULL;

void insertAtEnd(int data) {
    struct node *newNode = malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (head == NULL) {
        head = newNode;
        return;
    }

    struct node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newNode;
    newNode->prev = temp;
}

void insertAfter(int data, int previous) {
    struct node *current = head;

    while (current != NULL && current->data != previous) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Previous node not found.\n");
        return;
    }

    struct node *newNode = malloc(sizeof(struct node));
    newNode->data = data;

    newNode->next = current->next;
    newNode->prev = current;

    if (current->next != NULL) {
        current->next->prev = newNode;
    }

    current->next = newNode;
}

void deleteByValue(int data) {
    struct node *current = head;

    while (current != NULL && current->data != data) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Node not found.\n");
        return;
    }

    if (current == head) {
        head = current->next;
        if (head != NULL)
            head->prev = NULL;
    } else {
        current->prev->next = current->next;
        if (current->next != NULL)
            current->next->prev = current->prev;
    }

    free(current);
}

void printForward() {
    struct node *temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void printReverse() {
    struct node *temp = head;

    if (temp == NULL) return;

    while (temp->next != NULL) {
        temp = temp->next;
    }

    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->prev;
    }
    printf("\n");
}

// Build list 
void buildListFromFile(char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("File open failed");
        exit(1);
    }

    char buffer[1024];
    int bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    buffer[bytesRead] = '\0';

    close(fd);

    int num = 0;
    for (int i = 0; i <= bytesRead; i++) {
        if (buffer[i] >= '0' && buffer[i] <= '9') {
            num = num * 10 + (buffer[i] - '0');
        } else {
            if (num != 0) {
                insertAtEnd(num);
                num = 0;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <inputfile>\n", argv[0]);
        return 1;
    }

    buildListFromFile(argv[1]);

    printf("Initial list:\n");
    printForward();

    int choice;

    while (1) {
        printf("\nWhat else do you want?\n");
        printf("1: Insert at end\n");
        printf("2: Insert after\n");
        printf("3: Delete node\n");
        printf("0: Exit\n");

        scanf("%d", &choice);

        if (choice == 1) {
            int value;
            printf("Insert your node number: ");
            scanf("%d", &value);
            insertAtEnd(value);
            printForward();

        } else if (choice == 2) {
            int value, prev;
            printf("Insert new node number and previous node number: ");
            scanf("%d %d", &value, &prev);
            insertAfter(value, prev);
            printForward();

        } else if (choice == 3) {
            int value;
            printf("Insert the node number you want to delete: ");
            scanf("%d", &value);
            deleteByValue(value);
            printForward();

        } else if (choice == 0) {
            printf("Forward:\n");
            printForward();
            printf("Reverse:\n");
            printReverse();
            break;
        }
    }

    return 0;
}