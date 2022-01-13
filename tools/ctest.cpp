#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <cerrno>

// 8GB
//#define FILE_SIZE 1073741824L

// 2GB
#define FILE_SIZE 268435456L

// 1GB
//#define FILE_SIZE 134217728L

#define BLOCK_SIZE 4096

int main(int argc, const char * argv[])
{
    const char * filename;
    std::string choice;
    int fd;
    int ret;

    if (argc == 2) {
        filename = "temp.dat";
    }
    else if (argc == 3) {
        filename = argv[2];
    }
    else {
        std::cerr << "usage: " << argv[0] << " fallocate|fill [PATH=temp.dat]\n";
        return EXIT_FAILURE;
    }
    
    choice = std::string(argv[1]);
    fd = open(filename, O_RDWR | O_CREAT, 0600);
    
    if (choice == "fallocate") {
        if ((ret = posix_fallocate(fd, 0, FILE_SIZE)) != 0) {
            std::cout << "posix_fallocate failed: " << errno << std::endl;
        }
    }
    else if (choice == "fill") {
        long pos = 0;
        
        while (pos < FILE_SIZE) {
            const char byte = 1;
       
            // lseek returns -1 even if it succeeds
            (void)lseek(fd, pos, SEEK_SET);
            
            if ((ret = write(fd, &byte, 1)) != 1) {
                std::cout << "write failed: " << errno << std::endl;
                goto done;
            } 
                        
            pos += BLOCK_SIZE;
        }
    }
    else {
        std::cout << "unknown option: " << choice << std::endl;
        ret = EXIT_FAILURE;
    }

done:    
    close(fd);
    return ret;
}
