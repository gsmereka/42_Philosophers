/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 02:48:45 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/05 14:24:36 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

char	*ft_strchr(const char *s, int c)
{
	char	char_c;

	char_c = c;
	if (!s)
		return (0);
	if (char_c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (*s != char_c)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char *)s);
}
