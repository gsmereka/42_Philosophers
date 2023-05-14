/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:41:41 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/14 16:08:12 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static void	set_config(char *argv[], t_data *data);
static void	set_forks(t_data *data);
static void	set_philosophers(int i, t_data *data);
static void	set_observer(t_data *data);

void	init_data(char *argv[], t_data *data)
{
	int	i;

	ft_bzero(data, sizeof(t_data));
	set_config(argv, data);
	set_forks(data);
	set_philosophers(-1, data);
	set_observer(data);
	data->need_stop_mutex = ft_calloc(1, sizeof(pthread_mutex_t));
	if (!data->need_stop_mutex)
		exit_error(12, "fail to allocate need_stop_mutex\n", data);
	data->philo_status = ft_calloc(data->config->number_of_philosophers + 1, sizeof(t_status *));
	if (!data->philo_status)
		exit_error(12, "fail to allocate philo status array\n", data);
	i = 0;
	while (i < data->config->number_of_philosophers)
	{
		data->philo_status[i] = ft_calloc(1, sizeof(t_status));
		if (!data->philo_status[i])
			exit_error(12, "fail to allocate philo status\n", data);
		data->philo_status[i]->status_mutex
			= ft_calloc(1, sizeof(pthread_mutex_t));
		if (!data->philo_status[i]->status_mutex)
			exit_error(12, "fail to allocate status mutex\n", data);
		i++;
	}
}

static void	set_config(char *argv[], t_data *data)
{
	data->config = ft_calloc(1, sizeof(t_config));
	if (!data->config)
		exit_error(12, "fail to allocate data config\n", data);
	data->config->number_of_philosophers = ft_atoi(argv[1]);
	data->config->time_to_die = ft_atoi(argv[2]);
	data->config->time_to_eat = ft_atoi(argv[3]);
	data->config->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->config->number_of_times_each_philosopher_must_eat
			= ft_atoi(argv[5]);
	else
		data->config->number_of_times_each_philosopher_must_eat = -1;
}

static void	set_forks(t_data *data)
{
	int	i;

	data->forks = ft_calloc(data->config->number_of_philosophers + 1,
			sizeof(t_fork *));
	if (!data->forks)
		exit_error(12, "fail to allocate forks array\n", data);
	i = 0;
	while (i < data->config->number_of_philosophers)
	{
		data->forks[i] = ft_calloc(1, sizeof(t_fork));
		if (!data->forks[i])
			exit_error(12, "fail to allocate fork struct\n", data);
		data->forks[i]->mutex = ft_calloc(1, sizeof(pthread_mutex_t));
		if (!data->forks[i]->mutex)
			exit_error(12, "fail to allocate fork struct\n", data);
		data->forks[i]->available = TRUE;
		i++;
	}
}

static void	set_philosophers(int i, t_data *data)
{
	data->philo_threads
		= ft_calloc(data->config->number_of_philosophers, sizeof(pthread_t *));
	if (!data->philo_threads)
		exit_error(12, "fail to allocate threads array\n", data);
	data->philosophers = ft_calloc(data->config->number_of_philosophers + 1,
			sizeof(t_philosopher *));
	if (!data->philosophers)
		exit_error(12, "fail to allocate philosophers array\n", data);
	while (++i < data->config->number_of_philosophers)
	{
		data->philo_threads[i] = ft_calloc(1, sizeof(pthread_t));
		if (!data->philo_threads[i])
			exit_error(12, "fail to allocate philosopher struct\n", data);
		data->philosophers[i] = ft_calloc(1, sizeof(t_philosopher));
		if (!data->philosophers[i])
			exit_error(12, "fail to allocate philosopher struct\n", data);
		data->philosophers[i]->fork_order = ft_calloc(3, sizeof(t_fork *));
	}
}

static void	set_observer(t_data *data)
{
	data->observer_thread = ft_calloc(1, sizeof(pthread_t));
	if (!data->observer_thread)
		exit_error(12, "fail to allocate observer threads\n", data);
	data->observer = ft_calloc(1, sizeof(t_observer));
	if (!data->observer)
		exit_error(12, "fail to allocate observer memory\n", data);
	data->observer->missing_meals
		= ft_calloc(data->config->number_of_philosophers, sizeof(int));
	if (!data->observer->missing_meals)
		exit_error(12, "fail to allocate observer memory\n", data);
}
