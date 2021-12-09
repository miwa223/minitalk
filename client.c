#include "minitalk.h"
#include "client.h"

int g_received_signal = 0;

void	handler(int sig, siginfo_t *siginfo, void *str)
{
	printf("server\n");
}

void	receive_confirmation(int signo)
{
	g_received_signal = signo;
}

int	main(int argc, char **argv)
{
	struct sigaction	act;
	siginfo_t *siginfo;
	int	i;
	int j;
	unsigned char str;
	int	bit;
	t_send	send;

	(void)argc;
	i = 0;
	bit = 2; //適当
	// init_struct(&send);
	// act.sa_sigaction = handler;
	// act.sa_flags = SA_SIGINFO;
	// sigemptyset(&act.sa_mask);
	// sigaddset(&act, SIGUSR1);
	// sigaction(SIGUSR1, &act, NULL);
	signal(SIGUSR1, &receive_confirmation);
	while (argv[2][i] != '\0')
	{
		str = (unsigned char)argv[2][i];
		j = 7;
		while (j >= 0)
		{
			usleep(100);
			bit = str >> j & 0x01;
			printf("bit; %d\n", bit);
			kill((pid_t)atoi(argv[1]), SIGUSR1 + bit);
			if (g_received_signal == SIGUSR1)
				printf("received confirmation\n");
			j--;
			pause();
		}
		i++;
	}
	j = 7;
	while (j >= 0)
	{
		usleep(100);
		bit = (unsigned char)EOT >> j & 0x01;
		printf("bit; %d\n", bit);
		kill((pid_t)atoi(argv[1]), SIGUSR1 + bit);
		j--;
	}
	// while(1);
}
