/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:47:48 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/10 17:03:13 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static void	init_philosophers_shared_vars(t_philosopher *philo, t_data *data);

void	init_philosophers(t_data *data)
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

static void	init_philosophers_shared_vars(t_philosopher *philo, t_data *data)
{
	philo->shared->start_time = &(data->start_time);
	philo->shared->need_stop = &(data->need_stop);
	philo->shared->philo_dones = &(data->philo_dones);
	philo->shared->philo_dones_mutex = &(data->philo_dones_mutex);
	philo->shared->start_time_mutex = &(data->start_time_mutex);
	philo->shared->need_stop_mutex = &(data->need_stop_mutex);
}