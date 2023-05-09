/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:36:24 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/09 20:04:24 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	init_philosophers(t_data *data)
{
	int	index;

	index = 0;
	while (index < data->config->number_of_philosophers)
	{
		data->philosophers[index]->eat_limit
			= data->config->number_of_times_each_philosopher_must_eat;
		data->philosophers[index]->shared->right_fork = data->forks[index];
		if (index == 0)
			data->philosophers[index]->shared->left_fork = data->forks[data->config->number_of_philosophers - 1];
		else
			data->philosophers[index]->shared->left_fork = data->forks[index - 1];
		data->philosophers[index]->id = index + 1;
		data->philosophers[index]->time_to_die = data->config->time_to_die;
		data->philosophers[index]->time_to_eat = data->config->time_to_eat * 1000;
		data->philosophers[index]->time_to_sleep = data->config->time_to_sleep * 1000;
		data->philosophers[index]->time_to_think = data->config->time_to_think * 1000;
		data->philosophers[index]->shared->start_time = &(data->start_time);
		data->philosophers[index]->shared->need_stop = &(data->need_stop);
		data->philosophers[index]->shared->philo_dones = &(data->philo_dones);
		data->philosophers[index]->shared->start_time_mutex = &(data->start_time_mutex);
		data->philosophers[index]->shared->need_stop_mutex = &(data->need_stop_mutex);
		index++;
	}
}

int	main(int argc, char *argv[])
{
	t_data	data;

	check_args(argc, argv, &data);
	init_data(argv, &data);
	init_philosophers(&data);
	prepare_threads(&data);
	finalize(&data);
}
