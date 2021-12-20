#include "minitalk.h"

int	g_received_signal;

void	init_structure(t_send *send)
{
	send->count = 0;
	send->bit = 0;
	send->strings = NULL;
}

void	send_confirmation(int sig, siginfo_t *info, void *str)
{
	(void)*str;
	g_received_signal = sig;
	usleep(200);
	if (kill(info->si_pid, SIGUSR1) == -1)
		exit(EXIT_FAILURE);
}

void	set_signal(void)
{
	struct sigaction	act;
	siginfo_t			siginfo;

	siginfo.si_pid = 0;
	if (sigemptyset(&act.sa_mask) != 0)
		exit(EXIT_FAILURE);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = send_confirmation;
	if (sigaction(SIGUSR1, &act, NULL) != 0)
		exit(EXIT_FAILURE);
	if (sigaction(SIGUSR2, &act, NULL) != 0)
		exit(EXIT_FAILURE);
}

int	exit_server(t_send *send)
{
	free(send->strings);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_send				send;

	(void)**argv;
	if (argc != 1)
		exit(EXIT_FAILURE);
	g_received_signal = 0;
	ft_printf("server_pid: %d\n", (int)getpid());
	init_structure(&send);
	set_signal();
	while (1)
	{
		if (g_received_signal == SIGUSR1 || g_received_signal == SIGUSR2)
			set_bit(&send);
		else if (g_received_signal == SIGINT)
			exit(exit_server(&send));
		pause();
	}
	exit(EXIT_SUCCESS);
}
