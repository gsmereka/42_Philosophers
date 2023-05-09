/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:22:12 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/09 13:16:30 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static void	free_data(t_data *data);
void	free_generic_array(void **array, int limit);
void	free_array_list(void **list);

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

static void	free_data(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (data->forks[i])
		{
			if (data->forks[i]->mutex)
			{
				pthread_mutex_destroy(data->forks[i]->mutex);
				free(data->forks[i]->mutex);
			}
			i++;
		}
		free_generic_array((void **)data->forks, data->config->number_of_philosophers);
	}
	if (data->philosophers)
	{
		i = 0;
		while (data->philosophers[i])
		{
			if (data->philosophers[i]->shared)
			{
				pthread_mutex_destroy(data->philosophers[i]->shared->last_meal_mutex);
				free(data->philosophers[i]->shared->last_meal_mutex);
				free(data->philosophers[i]->shared);
			}
			free(data->philosophers[i]);
			i++;
		}
		free(data->philosophers);
	}
	if (data->philo_threads)
		free_generic_array((void **)data->philo_threads, data->config->number_of_philosophers);
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

void	free_array_list(void **list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		free(list[i]);
		list[i] = NULL;
		i++;
	}
	free(list);
	list = NULL;
}

void	free_generic_array(void **array, int limit)
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
