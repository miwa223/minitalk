/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 00:30:18 by mmasubuc          #+#    #+#             */
/*   Updated: 2021/12/11 17:39:44 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnum(long num)
{
	if (num > 9)
	{
		ft_putnum(num / 10);
		ft_putnum(num % 10);
	}
	else
		ft_putchar(num + '0');
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

size_t	ft_strlen_NULL(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin_strict(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	newstr = (char *)malloc(ft_strlen_NULL(s1) + ft_strlen_NULL(s2) + 1);
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
