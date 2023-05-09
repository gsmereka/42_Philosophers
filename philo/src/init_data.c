/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:41:41 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/09 12:48:05 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static void	set_config(char *argv[], t_data *data);
static void	set_forks(t_data *data);
static void	set_philosophers(t_data *data);
static void	set_threads(t_data *data);
 
void	init_data(char *argv[], t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	set_config(argv, data);
	set_forks(data);
	set_philosophers(data);
	set_threads(data);
	data->start_time_mutex = ft_calloc(1, sizeof(pthread_mutex_t));
	if (!data->start_time_mutex)
		exit_error(12, "Fail to allocate start time mutex\n", data);
	data->need_stop_mutex = ft_calloc(1, sizeof(pthread_mutex_t));
	if (!data->need_stop_mutex)
		exit_error(12, "Fail to allocate need_stop_mutex\n", data);
}

static void	set_config(char *argv[], t_data *data)
{
	data->config = ft_calloc(1, sizeof(t_config));
	if (!data->config)
	{
		exit_error(12, "Fail to allocate data config\n", data);
		exit(12);
	}
	data->config->number_of_philosophers = ft_atoi(argv[1]);
	data->config->time_to_die = ft_atoi(argv[2]);
	data->config->time_to_eat = ft_atoi(argv[3]);
	data->config->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->config->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		data->config->number_of_times_each_philosopher_must_eat = -1;
	data->config->time_to_think = 1000;
}

static void	set_forks(t_data *data)
{
	int	i;

	data->forks = ft_calloc(data->config->number_of_philosophers + 1, sizeof(t_fork));
	if (!data->forks)
		exit_error(12, "Fail to allocate forks array\n", data);
	i = 0;
	while (i < data->config->number_of_philosophers)
	{
		data->forks[i] = ft_calloc(1, sizeof(t_fork));
		if (!data->forks[i])
			exit_error(12, "Fail to allocate fork struct\n", data);
		data->forks[i]->mutex = ft_calloc(1, sizeof(pthread_mutex_t));
		if (!data->forks[i]->mutex)
			exit_error(12, "Fail to allocate fork struct\n", data);
		data->forks[i]->available = TRUE;
		i++;
	}
}

static void	set_philosophers(t_data *data)
{
	int	i;

	data->philosophers = ft_calloc(data->config->number_of_philosophers + 1, sizeof(t_philosopher));
	if (!data->philosophers)
		exit_error(12, "Fail to allocate philosophers array\n", data);
	i = 0;
	while (i < data->config->number_of_philosophers)
	{
		data->philosophers[i] = ft_calloc(1, sizeof(t_philosopher));
		if (!data->philosophers[i])
			exit_error(12, "Fail to allocate philosopher struct\n", data);
		data->philosophers[i]->shared = ft_calloc(1, sizeof(t_shared));
		if (!data->philosophers[i]->shared)
			exit_error(12, "Fail to allocate philosopher shared struct\n", data);
		data->philosophers[i]->shared->last_meal_mutex = ft_calloc(1, sizeof(pthread_mutex_t));
		if (!data->philosophers[i]->shared->last_meal_mutex)
			exit_error(12, "Fail to allocate philosopher mutex\n", data);
		i++;
	}
}

static void	set_threads(t_data *data)
{
	int	i;

	data->philo_threads = ft_calloc(data->config->number_of_philosophers, sizeof(pthread_t));
	if (!data->philo_threads)
		exit_error(12, "Fail to allocate threads array\n", data);
	i = 0;
	while (i < data->config->number_of_philosophers)
	{
		data->philo_threads[i] = ft_calloc(1, sizeof(pthread_t));
		if (!data->philo_threads[i])
			exit_error(12, "Fail to allocate philosopher struct\n", data);
		i++;
	}
	data->observer_thread = ft_calloc(1, sizeof(pthread_t));
	if (!data->observer_thread)
		exit_error(12, "Fail to allocate observer threads\n", data);
}
