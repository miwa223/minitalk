#ifndef MINITALK_H
# define MINITALK_H
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <stdbool.h>
# include <sysexits.h>
# include "ft_printf/ft_printf.h"
# include "ft_printf/libft/libft.h"

# define EOT 0x4
# define PID_MIN 100
# define PID_MAX 99998

extern int	g_received_signal;

typedef struct s_send
{
	int		count;
	char	*strings;
	int32_t	bit;
}				t_send;

void	is_valid_argc(int argc, int valid_argc);
void	init_structure(t_send *send);
void	set_signal(void);
void	send_confirmation(int sig, siginfo_t *info, void *str);
int		exit_server(t_send *send);
void	set_bit(t_send *send);
void	concat_char_into_strings(t_send *send);
void	is_valid_argv(int argc, char **argv);
void	send_bit(unsigned char ascii, char *server_pid);
void	receive_confirmation(int signo);

#endif
