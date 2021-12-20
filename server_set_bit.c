#include "minitalk.h"

int	g_received_signal;

void	concat_char_into_strings(t_send *send)
{
	char	*letter;
	char	*tmp;

	letter = (char *)malloc((char)2);
	if (!letter)
	{
		free(send->strings);
		exit(EXIT_FAILURE);
	}
	letter[0] = (char)send->bit;
	letter[1] = '\0';
	if (send->strings == NULL)
		send->strings = letter;
	else
	{
		tmp = ft_strjoin(send->strings, letter);
		free(send->strings);
		send->strings = tmp;
		free(letter);
		letter = NULL;
	}
	send->count = 0;
	send->bit = 0;
}

void	set_bit(t_send *send)
{
	send->bit <<= 1;
	if (g_received_signal == SIGUSR2)
		send->bit += 1;
	send->count += 1;
	if (send->count == 8)
	{
		if (send->bit == EOT)
		{
			ft_printf("%s", send->strings);
			free(send->strings);
			init_structure(send);
		}
		else
			concat_char_into_strings(send);
	}
}
