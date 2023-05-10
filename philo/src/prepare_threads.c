/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:07:13 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/10 17:18:09 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static void	prepare_mutexes(t_data *data);

void	prepare_threads(t_data *data)
{
	int	philo;

	philo = 0;
	prepare_mutexes(data);
	data->start_time = get_time_now();
	pthread_create(data->observer_thread, NULL, &observer_routine, data);
	while ((philo < data->config->number_of_philosophers))
	{
		pthread_create(data->philo_threads[philo],
			NULL, &philosopher_routine, data->philosophers[philo]);
		philo++;
	}
	philo = 0;
	pthread_join((*data->observer_thread), NULL);
	while ((philo < data->config->number_of_philosophers))
	{
		pthread_join((*data->philo_threads[philo]), NULL);
		philo++;
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
