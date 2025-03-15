#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string.h>


#define DRIVER_NAME "/dev/Dhruv_patel_1"
#define SET_SIZE_OF_QUEUE _IOW('a', 'a', int * )
#define PUSH_DATA _IOW('a', 'b', struct data * )
#define POP_DATA _IOR('a', 'c', struct data * )

struct data {
    int length;
    char * data;
};


int pop(void){
    int fd = open(DRIVER_NAME, O_RDWR);
    struct data * d = malloc(sizeof(struct data));
    d->length = 3;
    d->data = malloc(3);
    int ret = ioctl(fd, POP_DATA, d);
    if(ret<0){
        printf("underflow\n");
    }
    else{
        printf("%s\n", d->data);
    }
    
    close(fd);
    free(d->data);
    free(d);
    return ret;
}

int main(void) {

    pop();
}