#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>


int main()
{
    long int sec;
    long int mic;
    long int mili;
    struct timeval get_time;
    gettimeofday(&get_time, NULL);

    sec = get_time.tv_sec;
    mic = get_time.tv_usec;
    printf("seconds = %ld\nmicroseconds = %ld\n", get_time.tv_sec, get_time.tv_usec);
    usleep(4800000);
    gettimeofday(&get_time, NULL);
    sec = get_time.tv_sec - sec;
    mic = get_time.tv_usec - mic;
    printf("seconds = %ld\n", sec);
    printf("microseconds = %ld\n", mic);
    printf("seconds = %ld\nmicroseconds = %ld\n", get_time.tv_sec, get_time.tv_usec);
    sec = sec * 1000;
    mic = mic / 1000;
    mili = sec + mic;
    printf("miliseconds = %ld\n", mili);
    return (0);
}