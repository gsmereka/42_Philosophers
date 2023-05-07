/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:36:04 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/07 15:50:05 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	philo_eat(t_philosopher *philosopher)
{
	int	forks;

	forks = 0;
	while (forks < 2)
	{
		if (philosopher->left_fork->available)
		{
			forks++;
			pthread_mutex_lock(philosopher->left_fork->mutex);
			philosopher->left_fork->available--;
			philosopher->left_fork->holder = philosopher->index + 1;
			pthread_mutex_unlock(philosopher->left_fork->mutex);
			printf("%d %d has taken a fork\n", philosopher->time, philosopher->index + 1);
		}
		if (philosopher->right_fork->available)
		{
			forks++;
			pthread_mutex_lock(philosopher->right_fork->mutex);
			philosopher->right_fork->available--;
			philosopher->right_fork->holder = philosopher->index + 1;
			pthread_mutex_unlock(philosopher->right_fork->mutex);
			printf("%d %d has taken a fork\n", philosopher->time, philosopher->index + 1);
		}
	}
	printf("%d %d is eating\n", philosopher->time, philosopher->index + 1);
	sleep(1);
	pthread_mutex_lock(philosopher->right_fork->mutex);
	philosopher->right_fork->available++;
	philosopher->right_fork->holder = 0;
	pthread_mutex_unlock(philosopher->right_fork->mutex);
	pthread_mutex_lock(philosopher->left_fork->mutex);
	philosopher->left_fork->available++;
	philosopher->left_fork->holder = 0;
	pthread_mutex_unlock(philosopher->left_fork->mutex);
}

void	philo_think(t_philosopher *philosopher)
{
	printf("%d %d is thinking\n", philosopher->time, philosopher->index + 1);
	sleep(1);
}

void	philo_sleep(t_philosopher *philosopher)
{
	printf("%d %d is sleeping\n", philosopher->time, philosopher->index + 1);
	sleep(1);
}
// preciso colocar uma forma de parar o programa quando todos ja tiverem comido e quando um dos phios morrer.
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
