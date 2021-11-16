#include "minitalk.h"

int client(int pid, char *words)
{
    server(words);
    return (0);
}