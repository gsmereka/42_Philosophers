/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:36:24 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/08 18:04:07 by gsmereka         ###   ########.fr       */
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
		data->philosophers[index]->last_meal_time = 0;
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
