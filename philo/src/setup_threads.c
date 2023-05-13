/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:47:48 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/13 19:00:24 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static void	prepare_mutexes(t_data *data);
static void	define_forks(t_philosopher *philo, t_data *data);
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
		philo->missing_meals = philo->eat_limit;
		philo->id = index + 1;
		philo->time_to_die = data->config->time_to_die;
		philo->time_to_eat = data->config->time_to_eat * 1000;
		philo->time_to_sleep = data->config->time_to_sleep * 1000;
		philo->need_stop = &(data->need_stop);
		philo->need_stop_mutex = &(data->need_stop_mutex);
		define_forks(philo, data);
	}
}

static void	init_observer(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->config->number_of_philosophers)
	{
		data->observer->missing_meals[i]
			= data->config->number_of_times_each_philosopher_must_eat;
		i++;
	}
	data->observer->philosophers = &data->philosophers;
	data->observer->need_stop = &(data->need_stop);
	data->observer->need_stop_mutex = &(data->need_stop_mutex);
	data->observer->number_of_philosophers
		= data->config->number_of_philosophers;
	data->observer->time_to_die = data->config->time_to_die;
}

static void	define_forks(t_philosopher *philo, t_data *data)
{
	int	index;

	index = philo->id - 1;
	philo->right_fork = data->forks[index];
	if (index == 0)
		philo->left_fork
			= data->forks[data->config->number_of_philosophers - 1];
	else
		philo->left_fork = data->forks[index - 1];
	if (philo->id % 2 == 0)
	{
		philo->fork_order[0] = philo->left_fork;
		philo->fork_order[1] = philo->right_fork;
	}
	else
	{
		philo->fork_order[0] = philo->right_fork;
		philo->fork_order[1] = philo->left_fork;
	}
}

static void	prepare_mutexes(t_data *data)
{
	int	index;

	index = 0;
	pthread_mutex_init(data->need_stop_mutex, NULL);
	while ((index < data->config->number_of_philosophers))
	{
		pthread_mutex_init(data->forks[index]->mutex, NULL);
		pthread_mutex_init(data->philosophers[index]
			->philo_status_mutex, NULL);
		index++;
	}
}
