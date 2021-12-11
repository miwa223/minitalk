/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 00:29:40 by mmasubuc          #+#    #+#             */
/*   Updated: 2021/12/11 17:35:17 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	output_char(va_list *ap, t_tag *tag)
{
	int		i;
	char	c;

	i = 0;
	c = (char)va_arg(*ap, int);
	tag->len = 1;
	if (tag->flag[0] == 1)
		write(1, &c, 1);
	while (i++ < tag->field - tag->len)
		tag->print_len += write(1, " ", 1);
	if (tag->flag[0] != 1)
		write(1, &c, 1);
	tag->print_len++;
}

int	exist_flag0_str(t_tag tag, char *str)
{
	int	i;

	i = 0;
	if (tag.prec > 0)
	{
		while (i < tag.prec && str[i] != '\0')
		{
			tag.print_len += write(1, &str[i], 1);
			i++;
		}
	}
	else if (tag.prec == -1)
	{
		ft_putstr_fd(str, 1);
		tag.print_len += tag.len;
		i += tag.len;
	}
	while (i++ < tag.field)
		tag.print_len += write(1, " ", 1);
	return (tag.print_len);
}

int	check_precision(t_tag tag, char *str)
{
	int	i;

	i = 0;
	if (tag.prec == -1)
	{
		while (i++ < tag.field - tag.len)
		{
			if (tag.flag[1] == 1)
				tag.print_len += write(1, "0", 1);
			else
				tag.print_len += write(1, " ", 1);
		}
		ft_putstr_fd(str, 1);
		tag.print_len += tag.len;
	}
	else
	{
		while (i++ < tag.field - tag.prec)
			tag.print_len += write(1, " ", 1);
		if (tag.prec != 0)
			tag.print_len += write(1, str, tag.prec);
	}
	return (tag.print_len);
}

void	output_str(va_list *ap, t_tag *tag)
{
	char	*str;
	int		i;

	i = 0;
	str = va_arg(*ap, char *);
	if (str == NULL)
		str = "(null)";
	tag->len = ft_strlen_NULL(str);
	if (tag->flag[0] == 1)
		tag->print_len = exist_flag0_str(*tag, str);
	else if (tag->prec < tag->len)
		tag->print_len = check_precision(*tag, str);
	else
	{
		while (i++ < tag->field - tag->len)
			tag->print_len += write(1, " ", 1);
		ft_putstr_fd(str, 1);
		tag->print_len += tag->len;
	}
}
