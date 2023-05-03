/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:36:24 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/03 15:08:21 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../headers/philo.h"

void	*routine()
{
	static int	i;

	printf("thread %d\n", i);
}

void	*routine_2()
{
	static int	i;

	printf("thread %d\n", i  + 1);
}

int	main(int argc, char *argv[])
{
	pthread_t	t1, t2;

	pthread_create(&t1, NULL, &routine, NULL); // se não retornou 0, falhou em criar a thread
	// pthread_create(&t2, NULL, &routine_2, NULL);
	// pthread_join(t2, NULL); // se não retornou 0, falhou em criar a thread
	pthread_join(t1, NULL);
	pthread_join(t1, NULL);

	printf("Buenas Tardes %d\n", argc);
	(void)argv;
}
