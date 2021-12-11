/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 21:04:36 by mmasubuc          #+#    #+#             */
/*   Updated: 2021/12/11 18:07:15 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	i = 0;
	j = ft_strlen(&s[start]);
	if (j < len)
		len = j;
	if (len <= 0 || start >= ft_strlen(s))
		return (subs = (char *)ft_calloc(1, 1));
	subs = (char *)malloc(len + 1);
	if (!subs)
		return (NULL);
	else
	{
		while (i < len)
		{
			subs[i] = s[start + i];
			i++;
		}
	}
	subs[i] = '\0';
	return (subs);
}
