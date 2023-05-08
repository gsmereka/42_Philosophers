/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:22:12 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/08 14:16:02 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static void	free_data(t_data *data);
void	free_generic_array(void **array, int limit);
void	free_array_list(void **list);

void	finalize(t_data *data)
{
	// usleep2);
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
			free(data->philosophers[i]->shared);
			i++;
		}
		free_generic_array((void **)data->philosophers, data->config->number_of_philosophers);
	}
	if (data->philo_threads)
		free_generic_array((void **)data->philo_threads, data->config->number_of_philosophers);
	if (data->observer_thread)
		free(data->observer_thread);
	if (data->mutex)
	{
		pthread_mutex_destroy(data->mutex);
		free(data->mutex);
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
