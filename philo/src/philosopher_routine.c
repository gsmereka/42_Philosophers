/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:36:04 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/07 14:52:51 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	philo_eat(t_philosopher *philosopher)
{
	printf("%d %d has taken a fork\n", philosopher->time, philosopher->index + 1);
	printf("%d %d has taken a fork\n", philosopher->time, philosopher->index + 1);
	printf("%d %d is eating\n", philosopher->time, philosopher->index + 1);
}

void	philo_think(t_philosopher *philosopher)
{
	printf("%d %d is thinking\n", philosopher->time, philosopher->index + 1);
}

void	philo_sleep(t_philosopher *philosopher)
{
	printf("%d %d is sleeping\n", philosopher->time, philosopher->index + 1);
}

void	*philosopher_routine(void *philosopher_pointer)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)philosopher_pointer;
	while (philosopher->eat_limit != 0)
	{
		philosopher->time += 1000;
		philo_eat(philosopher);
		philosopher->eat_limit--;
		philo_sleep(philosopher);
		philo_think(philosopher);
	}
}
