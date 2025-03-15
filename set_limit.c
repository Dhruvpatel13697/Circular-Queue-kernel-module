#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string.h>


#define DRIVER_NAME "/dev/Dhruv_patel_1"
#define SET_SIZE_OF_QUEUE _IOW('a', 'a', int * )
#define PUSH_DATA _IOW('a', 'b', struct data * )

// struct data {
//     int length;
//     char * data;
// };


int set_linit(int size){
    int fd = open(DRIVER_NAME, O_RDWR);
    int ret = ioctl(fd, SET_SIZE_OF_QUEUE, &size);
    close(fd);
    return ret;
}

// int push(void){
//     int fd = open(DRIVER_NAME, O_RDWR);
//     struct data * d = malloc(sizeof(struct data));
//     d -> length = 3;
//     d -> data = malloc(3);
//     memcpy(d -> data, "xyz", 3);
//     int ret = ioctl(fd, PUSH_DATA, d);
//     close(fd);
//     free(d -> data);
//     free(d);
//     return ret;
// }

int main(void) {

    set_linit(4);
    // push();
}