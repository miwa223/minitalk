#include "minitalk.h"

int	g_received_signal;

void	is_valid_argv(int argc, char **argv)
{
	int		server_pid;
	size_t	size;

	server_pid = ft_atoi(argv[1]);
	if (argc != 3)
		exit(EXIT_FAILURE);
	if (server_pid < PID_MIN || server_pid > PID_MAX)
		exit(EXIT_FAILURE);
	size = ft_strlen(argv[1]);
	while (size-- > 0)
	{
		if (ft_isdigit((unsigned char)argv[1][size]) == 0)
			exit(EXIT_FAILURE);
	}
	if (argv[2] == NULL)
		exit(EXIT_FAILURE);
}

void	receive_confirmation(int signo)
{
	g_received_signal = signo;
}

void	send_bit(unsigned char ascii, char *server_pid)
{
	int	bit;
	int	j;

	j = 7;
	g_received_signal = 0;
	while (j >= 0)
	{
		bit = ascii >> j & 0x01;
		ft_printf("bit; %d\n", bit);
		if (kill((pid_t)ft_atoi(server_pid), SIGUSR1 + bit) == -1)
			exit(EXIT_FAILURE);
		pause();
		if (g_received_signal == SIGUSR1)
			ft_printf("confirmed by server\n");
		usleep(200);
		j--;
	}
}

int	main(int argc, char **argv)
{
	int	i;

	i = 0;
	is_valid_argv(argc, argv);
	if (signal(SIGUSR1, &receive_confirmation) == SIG_ERR)
		exit(EXIT_FAILURE);
	while (argv[2][i] != '\0')
	{
		send_bit((unsigned char)argv[2][i], argv[1]);
		i++;
	}
	send_bit((unsigned char)EOT, argv[1]);
	exit(EXIT_SUCCESS);
}
