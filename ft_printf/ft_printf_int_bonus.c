/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 00:29:59 by mmasubuc          #+#    #+#             */
/*   Updated: 2021/11/22 18:33:53 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	prep_len(t_tag tag, long d)
{
	long	tmp;

	if (d == 0 && tag.prec != 0)
		tag.len++;
	tmp = d;
	while (tmp > 0)
	{
		tmp /= 10;
		tag.len++;
	}
	return (tag.len);
}

void	output_int(va_list *ap, t_tag *tag)
{
	long	d;
	int		neg;

	neg = 0;
	d = va_arg(*ap, int);
	if (d < 0)
	{
		d = d * (-1);
		neg = 1;
		tag->print_len++;
	}
	tag->len = prep_len(*tag, d);
	if ((tag->flag[0] == 1 || (tag->flag[1] == 1 && tag->prec == -1)
			|| (tag->flag[0] != 1 && tag->prec >= tag->field)) && neg == 1)
		write(1, "-", 1);
	tag->print_len = print_space(*tag, neg);
	if (tag->flag[0] == 1)
		exist_flag0_u(tag, d, NULL, neg);
	else if (tag->flag[1] == 1 && tag->prec <= 0)
		exist_flag1(tag, d, neg);
	else
		not_exist_flag(tag, d, neg);
}

void	exist_flag1(t_tag *tag, long d, int neg)
{
	int	i;

	i = 0;
	if (tag->prec == -1)
	{
		while (i++ < tag->field - neg - tag->len)
			tag->print_len += write(1, "0", 1);
		ft_putnum(d);
		tag->print_len += tag->len;
	}
	else
	{
		if (tag->prec < tag->field && neg == 1)
			write(1, "-", 1);
		ft_putnum(d);
		tag->print_len += tag->len;
	}
}

void	not_exist_flag(t_tag *tag, long d, int neg)
{
	int	i;

	i = 0;
	if (neg == 1 && tag->field > tag->prec)
		write(1, "-", 1);
	while (i++ < tag->prec - tag->len)
		tag->print_len += write(1, "0", 1);
	if (d == 0 && tag->prec == 0)
		return ;
	else
	{
		ft_putnum(d);
		tag->print_len += tag->len;
	}
}
