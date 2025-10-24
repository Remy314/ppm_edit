#include "file_extractor.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>



/*this function load in the in a pointer that must to
 * be no initialited the file on the path, and returns
 * the size of the file*/
int extract_file(char* path,char** file_local){
    int fd = open(path, O_RDONLY);
    if (fd == -1){
        perror("open: ");
        close(fd);
        return -1;
    }


    off_t file_size = lseek(fd,0,SEEK_END);
    if (file_size == -1) {
        perror("lseek");
        close(fd);
        return -1;
    }
    if (file_size == 0){
        perror("empty file");
        close(fd);
        return -1;
    }

    if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("lseek");
        close(fd);
        return -1;
    }

    *file_local = malloc((size_t)(file_size+1));
     if (*file_local == NULL) {
        perror("malloc");
        close(fd);
        return -1;
    }

    ssize_t rb = read(fd,*file_local,(size_t)file_size);
    if (rb == -1){
        perror("read");
        free(*file_local);
        close(fd);
        return -1;
    }
    close(fd);
    if (rb != file_size){
        perror("not complete read: ");
        free(*file_local);
        close(fd);
        return -1;
    }
    return (int)rb;
}



int store_file(char* path, char*file_local, int size_file){
    
    int fd= open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1){
        perror("open: ");
        return -1;
    }

    ssize_t wb = write(fd, file_local,(size_t)size_file);
    if(wb == -1){
        perror("write: ");
        close(fd);
        return -1;    
    }

    if(size_file != (int)wb){
        perror("somwthig int write went wrong");
        close(fd);
        return -1;
    }

    return 0;

}


