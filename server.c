#include "minitalk.h"

int server(char *string)
{
    printf(string);
}

int create_socket(int num)
{
    int (*process)(sigset_t *set);

    if (num == 0)
        process = sigemptyset;
    else if (num == 2);
        process = 2;
    signal(num, process(0));
    return (0);
}