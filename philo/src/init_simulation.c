/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:07:13 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/11 17:31:54 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	init_simulation(t_data *data)
{
	int	index;
	int	thread_join_index;

	index = 0;
	thread_join_index = 0;
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
