/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 00:28:14 by mmasubuc          #+#    #+#             */
/*   Updated: 2021/12/11 17:27:42 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	concat_sum(char **sum, char *tmp)
{
	char	*sum_str;

	if (*sum)
	{
		sum_str = ft_strjoin_strict(*sum, tmp);
		free(*sum);
		*sum = sum_str;
		free(tmp);
		tmp = NULL;
	}
	else
		*sum = tmp;
}

int	convert_to_hex(unsigned int num, char **sum, t_tag tag)
{
	char	*tmp;

	if (num > 15)
	{
		convert_to_hex(num / 16, sum, tag);
		convert_to_hex(num % 16, sum, tag);
	}
	else if (num < 16)
	{
		tmp = (char *)malloc(2);
		if (!tmp)
			return (-2);
		if (num < 10)
			tmp[0] = num + '0';
		else if (num > 9 && num < 16)
		{
			if (tag.type == 'x')
				tmp[0] = num + ('a' - 10);
			else
				tmp[0] = num + ('A' - 10);
		}
		tmp[1] = '\0';
		concat_sum(sum, tmp);
	}
	return (0);
}

int	convert_to_hex_ptr(uintptr_t num, char **sum)
{
	char	*tmp;

	if (num > 15)
	{
		convert_to_hex_ptr(num / 16, sum);
		convert_to_hex_ptr(num % 16, sum);
	}
	else if (num < 16)
	{
		tmp = (char *)malloc(2);
		if (!tmp)
			return (-2);
		if (num < 10)
			tmp[0] = num + '0';
		else if (num > 9 && num < 16)
			tmp[0] = num + ('a' - 10);
		tmp[1] = '\0';
		concat_sum(sum, tmp);
	}
	return (0);
}
