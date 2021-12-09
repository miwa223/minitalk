#ifndef MINITALK_H
# define MINITALK_H
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
#include <stdio.h>
# include <stdbool.h>

#define ERRNO 0
#define EOT 4

extern int g_received_signal;

typedef struct	s_send
{
	int	eot;
	int count;
	char *str;
	int str_counter;
	int32_t	bit;
}				t_send;


char	*ft_strjoin(char const *s1, char const *s2);

# endif
