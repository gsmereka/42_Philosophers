/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:07:13 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/12 13:57:44 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static void	define_start_time(t_data *data);

void	init_simulation(t_data *data)
{
	int	index;
	int	thread_join_index;

	index = 0;
	thread_join_index = 0;
	define_start_time(data);
	while ((index < data->config->number_of_philosophers))
	{
		pthread_create(data->philo_threads[index],
			NULL, &philosopher_routine, data->philosophers[index]);
		index++;
	}
	pthread_create(data->observer_thread,
		NULL, &observer_routine, data->observer);
	while ((thread_join_index < data->config->number_of_philosophers))
	{
		pthread_join((*data->philo_threads[thread_join_index]), NULL);
		thread_join_index++;
	}
	pthread_join((*data->observer_thread), NULL);
}

static void	define_start_time(t_data *data)
{
	int	philo;

	philo = 0;
	data->start_time = get_time_now();
	data->observer->start_time = data->start_time;
	while (philo < data->config->number_of_philosophers)
	{
		data->philosophers[philo]->start_time = data->start_time;
		philo++;
	}
}
