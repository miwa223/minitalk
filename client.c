#include "minitalk.h"
#include "client.h"

int g_received_signal = 0;

void	receive_confirmation(int signo)
{
	g_received_signal = signo;
}

int	main(int argc, char **argv)
{
	int	i;
	int j;
	unsigned char str;
	int	bit;

	(void)argc;
	i = 0;
	bit = 3; //適当
	signal(SIGUSR1, &receive_confirmation);
	while (argv[2][i] != '\0')
	{
		str = (unsigned char)argv[2][i];
		j = 7;
		while (j >= 0)
		{
			usleep(1000);
			bit = str >> j & 0x01;
			ft_printf("bit; %d\n", bit);
			kill((pid_t)ft_atoi(argv[1]), SIGUSR1 + bit);
			if (g_received_signal == SIGUSR1)
				ft_printf("received confirmation\n");
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
		ft_printf("bit; %d\n", bit);
		kill((pid_t)ft_atoi(argv[1]), SIGUSR1 + bit);
		j--;
	}
}
