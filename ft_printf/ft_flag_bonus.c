/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 00:28:35 by mmasubuc          #+#    #+#             */
/*   Updated: 2021/11/22 18:30:09 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	print_unsigned_int(t_tag tag, long num, char *str)
{
	if ((tag.type == 'd' || tag.type == 'i' || tag.type == 'u')
		&& !(num == 0 && tag.prec == 0))
	{
		ft_putnum(num);
		tag.print_len += tag.len;
	}
	else
	{
		if (tag.type == '%')
			write(1, "%", 1);
		if (!(tag.prec == 0 && num == 0))
		{
			ft_putstr_fd(str, 1);
			tag.print_len += tag.len;
		}
	}
	return (tag.print_len);
}

void	exist_flag0_u(t_tag *tag, long num, char *str, int neg)
{
	int	i;

	i = 0;
	while (tag->prec > tag->len + i)
	{
		tag->print_len += write(1, "0", 1);
		i++;
	}
	tag->print_len = print_unsigned_int(*tag, num, str);
	while (tag->field > tag->len + neg + i++)
		tag->print_len += write(1, " ", 1);
}

void	exist_flag1_u(t_tag *tag, char *str, unsigned int num)
{
	int	i;

	i = 0;
	while ((tag->prec == -1 && i++ < tag->field - tag->len)
		|| (tag->prec != -1 && i++ < tag->prec - tag->len))
		tag->print_len += write(1, "0", 1);
	if (tag->type == 'u' && !(tag->prec == 0 && num == 0))
	{
		ft_putnum(num);
		tag->print_len += tag->len;
	}
	else
	{
		if (tag->type == '%')
			write(1, "%", 1);
		if (!(tag->prec == 0 && num == 0))
		{
			ft_putstr_fd(str, 1);
			tag->print_len += tag->len;
		}
	}
}

void	no_flag_u(t_tag *tag, char *str, unsigned int num)
{
	int	i;

	i = 0;
	while ((tag->type == 'p' && tag->prec - tag->len + 2 > i++)
		|| (tag->type != 'p' && tag->prec - tag->len > i++))
		tag->print_len += write(1, "0", 1);
	if (tag->type == 'u' && !(tag->prec == 0 && num == 0))
	{
		ft_putnum(num);
		tag->print_len += tag->len;
	}
	else
	{
		if (tag->type == '%')
			write(1, "%", 1);
		if (!(tag->prec == 0 && num == 0))
		{
			ft_putstr_fd(str, 1);
			tag->print_len += tag->len;
		}
		else if (tag->prec == 0 && tag->type == 'p')
			tag->print_len += tag->len - 1;
	}
}
