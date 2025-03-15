#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string.h>


#define DRIVER_NAME "/dev/Dhruv_patel_1"
#define SET_SIZE_OF_QUEUE _IOW('a', 'a', int * )
#define PUSH_DATA _IOW('a', 'b', struct data * )



int set_linit(int size){
    int fd = open(DRIVER_NAME, O_RDWR);
    int ret = ioctl(fd, SET_SIZE_OF_QUEUE, &size);
    close(fd);
    return ret;
}


int main(void) {

    set_linit(4);
}