/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:22:42 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/11 21:26:45 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	get_fork(t_fork *fork)
{
	pthread_mutex_lock(fork->mutex);
	if (fork->available == TRUE)
	{
		fork->available = FALSE;
		pthread_mutex_unlock(fork->mutex);
		return (1);
	}
	pthread_mutex_unlock(fork->mutex);
	return (0);
}

int	leave_fork(t_fork *fork)
{
	pthread_mutex_lock(fork->mutex);
	fork->available == TRUE;
	pthread_mutex_unlock(fork->mutex);
	return (0);
}
