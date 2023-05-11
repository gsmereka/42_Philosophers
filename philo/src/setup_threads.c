/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:47:48 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/11 17:31:58 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static void	prepare_mutexes(t_data *data);
static void	init_philosophers_shared_vars(t_philosopher *philo, t_data *data);
static void	init_philosophers(t_data *data);
static void	init_observer(t_data *data);

void	setup_threads(t_data *data)
{
	init_philosophers(data);
	init_observer(data);
	prepare_mutexes(data);
}

static void	init_philosophers(t_data *data)
{
	int				index;
	t_philosopher	*philo;

	index = -1;
	while (++index < data->config->number_of_philosophers)
	{
		philo = data->philosophers[index];
		philo->eat_limit
			= data->config->number_of_times_each_philosopher_must_eat;
		philo->shared->right_fork = data->forks[index];
		if (index == 0)
			philo->shared->left_fork
				= data->forks[data->config->number_of_philosophers - 1];
		else
			philo->shared->left_fork = data->forks[index - 1];
		philo->id = index + 1;
		philo->time_to_die = data->config->time_to_die;
		philo->time_to_eat = data->config->time_to_eat * 1000;
		philo->time_to_sleep = data->config->time_to_sleep * 1000;
		init_philosophers_shared_vars(philo, data);
	}
}

static void	init_observer(t_data *data)
{
	data->observer->need_stop = &(data->need_stop);
	data->observer->need_stop_mutex = &(data->need_stop_mutex);
}

static void	init_philosophers_shared_vars(t_philosopher *philo, t_data *data)
{
	philo->shared->start_time = &(data->start_time);
	philo->shared->need_stop = &(data->need_stop);
	philo->shared->start_time_mutex = &(data->start_time_mutex);
	philo->shared->need_stop_mutex = &(data->need_stop_mutex);
}


static void	prepare_mutexes(t_data *data)
{
	int	index;

	index = 0;
	pthread_mutex_init(data->need_stop_mutex, NULL);
	pthread_mutex_init(data->start_time_mutex, NULL);
	while ((index < data->config->number_of_philosophers))
	{
		pthread_mutex_init(data->forks[index]->mutex, NULL);
		pthread_mutex_init(data->philosophers[index]
			->shared->philo_status_mutex, NULL);
		index++;
	}
}
