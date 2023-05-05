/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:23:00 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/05 14:24:36 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*s_char;
	size_t			i;

	i = 0;
	s_char = (unsigned char *)s;
	while (i < n)
	{
		s_char[i] = '\0';
		i++;
	}
}
