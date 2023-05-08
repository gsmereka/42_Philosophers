/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:36:24 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/08 14:55:42 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	get_start_time(t_data *data)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	data->start_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (0);
}

long int	get_time_data(t_data *data)
{
	struct timeval	time;
	long int		new_time;

	gettimeofday(&time, NULL);
	new_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (new_time - data->start_time);
}

void	*observer_routine(void *observer_data)
{
	t_data		*data;
	int			i;
	long int	time;

	data = (t_data *)observer_data;
	printf("START\n");
	while (!data->need_stop)
	{
		i = 0;
		time = get_time_data(data);
		if (time > 3000)
		{
			printf("STOP\n");
			data->need_stop = TRUE;
		}
		// while (i < data->config->number_of_philosophers)
		// {
		// 	if (data->philosophers[i]->last_meal_time - data->start_time > data->config->time_to_die)
		// 	{
		// 		data->need_stop = TRUE;
		// 		break ;
		// 	}
		// 	i++;
		// }
	}
}

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
	get_start_time(data);
	philo = 0;
	pthread_create(data->observer_thread, NULL, &observer_routine, data);
	while ((philo < data->config->number_of_philosophers))
	{
		pthread_create(data->philo_threads[philo], NULL, &philosopher_routine, data->philosophers[philo]);
		philo++;
	}
	philo = 0;
	pthread_join((*data->observer_thread), NULL);
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
		data->philosophers[index]->shared->left_fork = data->forks[index];
		if (index < data->config->number_of_philosophers - 1)
			data->philosophers[index]->shared->right_fork = data->forks[index + 1];
		else
			data->philosophers[index]->shared->right_fork = data->forks[0];
		data->philosophers[index]->id = index + 1;
		data->philosophers[index]->time_to_die = data->config->time_to_die;
		data->philosophers[index]->time_to_eat = data->config->time_to_eat;
		data->philosophers[index]->time_to_sleep = data->config->time_to_sleep;
		data->philosophers[index]->time_to_think = data->config->time_to_think;
		data->philosophers[index]->shared->start_time = &(data->start_time);
		data->philosophers[index]->shared->need_stop = &(data->need_stop);
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
// 	usleep3);
// 	free(count);
// 	free(threads);
// 	(void)argv;
// }
