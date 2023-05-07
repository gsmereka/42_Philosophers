/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:36:24 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/07 16:55:37 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

// void	init_philosophers(t_data *data)
// {
// 	int	philo;

// 	philo = 0;
// 	pthread_mutex_init(data->mutex, NULL);
// 	while ((philo < data->config->number_of_philosophers))
// 	{
// 		pthread_create(data->philo_threads[philo], NULL, &philosopher_routine, data);
// 		philo++;
// 	}
// 	philo = 0;
// 	while ((philo < data->config->number_of_philosophers))
// 	{
// 		pthread_join((*data->philo_threads[philo]), NULL);
// 		philo++;
// 	}
// }

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
	while ((philo < data->config->number_of_philosophers))
	{
		pthread_create(data->philo_threads[philo], NULL, &philosopher_routine, data->philosophers[philo]);
		philo++;
	}
	philo = 0;
	while ((philo < data->config->number_of_philosophers))
	{
		pthread_join((*data->philo_threads[philo]), NULL);
		philo++;
	}
}

void	init_philosophers(t_data *data)
{
	int	index;

	index = 0;
	while (index < data->config->number_of_philosophers)
	{
		data->philosophers[index]->eat_limit
			= data->config->number_of_times_each_philosopher_must_eat;
		data->philosophers[index]->left_fork = data->forks[index];
		if (index < data->config->number_of_philosophers - 1)
			data->philosophers[index]->right_fork = data->forks[index + 1];
		else
			data->philosophers[index]->right_fork = data->forks[0];
		data->philosophers[index]->id = index + 1;
		data->philosophers[index]->time_to_die = data->config->time_to_die;
		data->philosophers[index]->time_to_eat = data->config->time_to_eat;
		data->philosophers[index]->time_to_sleep = data->config->time_to_sleep;
		data->philosophers[index]->time_to_think = data->config->time_to_think;
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


// int	main(int argc, char *argv[])
// {
// 	int				i;
// 	int				*count;
// 	int				another_count;
// 	pthread_t		*threads;

// 	i = 0;
// 	threads = malloc(10 * sizeof(pthread_t));
// 	count = malloc(sizeof(int));
// 	pthread_mutex_init(&mutex, NULL);
// 	*count = 0;
// 	while ((i < 10))
// 	{
// 		pthread_create(&threads[i], NULL, &routine, count);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < 10)
// 	{
// 		pthread_join(threads[i], NULL);
// 		i++;
// 	}
// 	sleep(3);
// 	free(count);
// 	free(threads);
// 	(void)argv;
// }
