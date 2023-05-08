/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:04:11 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/08 18:04:25 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	get_start_time(t_data *data)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	data->start_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (0);
}

long int	get_time_data(t_data *data)
{
	struct timeval	time;
	long int		new_time;

	gettimeofday(&time, NULL);
	new_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (new_time - data->start_time);
}

void	*observer_routine(void *observer_data)
{
	t_data		*data;
	int			i;
	long int	time;
	long int	last_meal_time;

	data = (t_data *)observer_data;
	printf("START\n");
	while (!data->need_stop)
	{
		i = 0;
		while (i < data->config->number_of_philosophers)
		{
			time = get_time_data(data);
			last_meal_time = data->philosophers[i]->last_meal_time;
			// printf("%d\n", last_meal_time);
			if (time - last_meal_time > data->config->time_to_die)
			{
				printf("%d e %d - %d\n", last_meal_time, time, data->philosophers[i]->id);
				data->need_stop = TRUE;
				break ;
			}
			i++;
		}
	}
	printf("STOP\n");
}

void	prepare_threads(t_data *data)
{
	int	philo;

	philo = 0;
	pthread_mutex_init(data->mutex, NULL);
	while ((philo < data->config->number_of_philosophers))
	{
		pthread_mutex_init(data->forks[philo]->mutex, NULL);
		philo++;
	}
	get_start_time(data);
	philo = 0;
	pthread_create(data->observer_thread, NULL, &observer_routine, data);
	while ((philo < data->config->number_of_philosophers))
	{
		pthread_create(data->philo_threads[philo], NULL, &philosopher_routine, data->philosophers[philo]);
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
