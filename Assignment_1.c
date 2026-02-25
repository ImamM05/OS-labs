#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define BUFFER_AMT 100

int main(int argc, char* argv[]) {
    unsigned int fd = open(argv[1], O_RDONLY);
    
}