/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:36:24 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/07 14:35:26 by gsmereka         ###   ########.fr       */
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

void	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->config->number_of_philosophers)
	{
		data->philosophers[i]->eat_limit = data->config->number_of_times_each_philosopher_must_eat;
		data->philosophers[i]->left_fork = data->forks[i];
		data->philosophers[i]->right_fork = data->forks[i];
		data->philosophers[i]->index = i;
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_data data;

	check_args(argc, argv, &data);
	init_data(argv, &data);
	init_philosophers(&data);
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
