/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:38:31 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/11 18:01:40 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static void	destroy_forks(t_data *data);
static void	free_generic_array(void **array, int limit);
static void	destroy_philosophers(t_data *data);
static void	destroy_observer(t_data *data);

void	free_data(t_data *data)
{
	destroy_forks(data);
	destroy_philosophers(data);
	destroy_observer(data);
	if (data->philo_threads)
		free_generic_array((void **)data->philo_threads,
			data->config->number_of_philosophers);
	if (data->observer_thread)
		free(data->observer_thread);
	if (data->start_time_mutex)
	{
		pthread_mutex_destroy(data->start_time_mutex);
		free(data->start_time_mutex);
	}
	if (data->need_stop_mutex)
	{
		pthread_mutex_destroy(data->need_stop_mutex);
		free(data->need_stop_mutex);
	}
	if (data->config)
		free(data->config);
}

static void	destroy_philosophers(t_data *data)
{
	int	i;

	i = 0;
	if (data->philosophers)
	{
		while (data->philosophers[i])
		{
			if (data->philosophers[i]->shared)
			{
				pthread_mutex_destroy(data->philosophers[i]
					->shared->philo_status_mutex);
				free(data->philosophers[i]->shared->philo_status_mutex);
				free(data->philosophers[i]->shared);
			}
			free(data->philosophers[i]);
			i++;
		}
		free(data->philosophers);
	}
}

static void	destroy_observer(t_data *data)
{
	if (data->observer)
	{
		if (data->observer->philo_done)
			free(data->observer->philo_done);
		free(data->observer);
	}
}

static void	destroy_forks(t_data *data)
{
	int	i;

	i = 0;
	if (data->forks)
	{
		while (data->forks[i])
		{
			if (data->forks[i]->mutex)
			{
				pthread_mutex_destroy(data->forks[i]->mutex);
				free(data->forks[i]->mutex);
			}
			free(data->forks[i]);
			i++;
		}
		free(data->forks);
	}
}

static void	free_generic_array(void **array, int limit)
{
	int	i;

	i = 0;
	while (i < limit)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
