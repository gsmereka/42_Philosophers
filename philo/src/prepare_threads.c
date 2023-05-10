/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:07:13 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/10 18:39:05 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static void	prepare_mutexes(t_data *data);

void	prepare_threads(t_data *data)
{
	int	index;
	int	thread_join_index;

	index = 0;
	thread_join_index = 0;
	prepare_mutexes(data);
	data->start_time = get_time_now();
	pthread_create(data->observer_thread, NULL, &observer_routine, data);
	while ((index < data->config->number_of_philosophers))
	{
		pthread_create(data->philo_threads[index],
			NULL, &philosopher_routine, data->philosophers[index]);
		index++;
	}
	pthread_join((*data->observer_thread), NULL);
	while ((thread_join_index < data->config->number_of_philosophers))
	{
		pthread_join((*data->philo_threads[thread_join_index]), NULL);
		thread_join_index++;
	}
}

static void	prepare_mutexes(t_data *data)
{
	int	index;

	index = 0;
	pthread_mutex_init(data->need_stop_mutex, NULL);
	pthread_mutex_init(data->start_time_mutex, NULL);
	pthread_mutex_init(data->philo_dones_mutex, NULL);
	while ((index < data->config->number_of_philosophers))
	{
		pthread_mutex_init(data->forks[index]->mutex, NULL);
		pthread_mutex_init(data->philosophers[index]->shared->last_meal_mutex,
			NULL);
		index++;
	}
}
