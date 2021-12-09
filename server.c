#include "minitalk.h"

int g_received_signal = 0;

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	newstr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (newstr == NULL)
		return (NULL);
	while (s1[i] != '\0' && s1[i] != '\n')
	{
		newstr[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0' && s2[j] != '\n')
	{
		newstr[i] = s2[j];
		i++;
		j++;
	}
	newstr[i] = '\0';
	return (newstr);
}

void	init_struct(t_send *send)
{
	send->eot = 0;
	send->count = 0;
	send->str = NULL;
	send->str_counter = 0;
	send->bit = 0;
}

void	init_siginfo(siginfo_t *siginfo)
{
	siginfo->si_pid = 0;
}

void	recieve_bit(int num)
{
	g_received_signal = num;
}

int	set_bit(t_send *send, char **string)
{
	int str;
	char	*tmp;
	char	*tmp_string;

	str = 0;
	tmp = NULL;
	send->bit <<= 1;
	if (g_received_signal == SIGUSR2)
		send->bit += 1;
	send->count += 1;
	if (send->count == 8)
	{
		send->str_counter += 1;
		tmp = (char *)malloc(2);
		// if (!tmp)
		// 	return (NULL);
		tmp[0] = (char)send->bit;
		tmp[1] = '\0';
		printf("bits; %d, ", send->bit);
		if (send->bit == EOT)
		{
			printf("EOT!");
			return (-1);
		}
		if (*string == NULL)
			*string = tmp;
		else
		{
			tmp_string = ft_strjoin(*string, tmp);
			free(*string);
			*string = tmp_string;
			free(tmp);
			tmp = NULL;
		}
		send->count = 0;
	}
	return (0);
}

void	confirm_signal_from_client(siginfo_t *siginfo)
{
	printf("si_pid; %d\n", siginfo->si_pid);
	kill(siginfo->si_pid, SIGUSR1);
}

void	take_client_pid(int sig, siginfo_t *info, void *str)
{
	g_received_signal = sig;
	confirm_signal_from_client(info);
}

int	main(void)
{
	t_send	send;
	int j;
	int i;
	int n;
	int str;
	char *string;
	struct sigaction	act;
	siginfo_t	siginfo;

	j = 0;
	i = 0;
	str = 0;
	string = NULL;
	fflush(stdout);
	init_struct(&send);
	init_siginfo(&siginfo);
	printf("server_pid: %d\n", (int)getpid());
	// signal(SIGUSR1, &recieve_bit);
	// signal(SIGUSR2, &recieve_bit);
	// sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = take_client_pid;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
	{
		if (g_received_signal == SIGUSR1 || g_received_signal == SIGUSR2)
		{
			if (set_bit(&send, &string) == -1)
				printf("EOT\n");
			usleep(100);
			i++;
		}
		if (string)
			printf("str; %s\n", string);
		pause();
	}
	return (0);
}
