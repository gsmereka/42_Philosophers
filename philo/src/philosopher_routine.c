/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:36:04 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/06 19:46:08 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	philo_eat(int philo_index, t_data *data)
{
	printf("timestamp_in_ms %d has taken a fork\n", philo_index + 1);
	printf("timestamp_in_ms %d has taken a fork\n", philo_index + 1);
	printf("timestamp_in_ms %d is eating\n", philo_index + 1);
}

void	philo_think(int philo_index, t_data *data)
{
	printf("timestamp_in_ms %d is thinking\n", philo_index + 1);
}

void	philo_sleep(int philo_index, t_data *data)
{
	printf("timestamp_in_ms %d is sleeping\n", philo_index + 1);
}

void	*philosopher_routine(void *arg)
{
	t_data	*data;
	int		philo_index;
	int		i;

	i = 0;
	data = (t_data *)arg;
	pthread_mutex_lock(data->mutex);
	philo_index = data->philo_count;
	data->philo_count++;
	pthread_mutex_unlock(data->mutex);
	while (i++ < 5)
	{
		philo_eat(philo_index, data);
		philo_sleep(philo_index, data);
		philo_think(philo_index, data);
	}
}
