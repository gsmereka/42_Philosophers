/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:22:12 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/10 17:39:32 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	finalize(t_data *data)
{
	free_data(data);
	exit(0);
}

void	exit_error(int status, char *msg, t_data *data)
{
	ft_putstr_fd(msg, 2);
	free_data(data);
	exit(status);
}
