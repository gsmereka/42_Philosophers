/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:04:11 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/09 12:30:20 by gsmereka         ###   ########.fr       */
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

long int get_time_data() {
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

void *observer_routine(void *observer_data)
{
    t_data *data = (t_data *)observer_data;
	int	i;
    int stop = 0;
    while (!stop)
	{
		i = 0;
		while (i < data->config->number_of_philosophers)
		{
            pthread_mutex_lock(data->philosophers[i]->mutex);
            long int last_meal_time = data->philosophers[i]->last_meal_time;
            pthread_mutex_unlock(data->philosophers[i]->mutex);
            long int current_time = get_time_data();
			current_time -= data->start_time;
            if (current_time - last_meal_time > data->config->time_to_die)
			{
                printf("%ld %d died\n", current_time, data->philosophers[i]->id);
                data->need_stop = TRUE;
                stop = 1;
                break;
            }
			i++;
        }
    }
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
	philo = 0;
	get_start_time(data);
	pthread_create(data->observer_thread, NULL, &observer_routine, data);
	while ((philo < data->config->number_of_philosophers))
	{
		pthread_mutex_init(data->philosophers[philo]->mutex, NULL);
		pthread_mutex_init(data->philosophers[philo]->shared->mutex, NULL);
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
