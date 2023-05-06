/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:36:24 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/05 22:20:39 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

// void	*philosopher_routine(void *philosopher)
// {
// 	pthread_mutex_lock(&philosopher->mutex);
// 	printf("pegou o garfo %d\n", 2);
// 	pthread_mutex_unlock(&philosopher->mutex);
// }

int	main(int argc, char *argv[])
{
	t_data data;

	ft_bzero(&data, sizeof(t_data));
	check_args(argc, argv, &data);
	init_data(argv, &data);
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
