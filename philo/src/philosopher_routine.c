/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:36:04 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/07 16:48:24 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	philo_prepare_to_eat(t_philosopher *philo)
{
	int	forks;

	forks = 0;
	while (forks < 2)
	{
		if (philo->left_fork->available)
		{
			forks++;
			pthread_mutex_lock(philo->left_fork->mutex);
			philo->left_fork->available = FALSE;
			philo->left_fork->holder = philo->id;
			pthread_mutex_unlock(philo->left_fork->mutex);
			printf("%d %d has taken a fork\n", philo->time, philo->id);
		}
		if (philo->right_fork->available)
		{
			forks++;
			pthread_mutex_lock(philo->right_fork->mutex);
			philo->right_fork->available = FALSE;
			philo->right_fork->holder = philo->id;
			pthread_mutex_unlock(philo->right_fork->mutex);
			printf("%d %d has taken a fork\n", philo->time, philo->id);
		}
	}
}

void	philo_eat(t_philosopher *philo)
{
	printf("%d %d is eating\n", philo->time, philo->id);
	sleep(1);
	pthread_mutex_lock(philo->right_fork->mutex);
	philo->right_fork->available = TRUE;
	philo->right_fork->holder = 0;
	pthread_mutex_unlock(philo->right_fork->mutex);
	pthread_mutex_lock(philo->left_fork->mutex);
	philo->left_fork->available = TRUE;
	philo->left_fork->holder = 0;
	pthread_mutex_unlock(philo->left_fork->mutex);
}

void	philo_sleep_and_think(t_philosopher *philo)
{
	printf("%d %d is sleeping\n", philo->time, philo->id);
	sleep(1);
	printf("%d %d is thinking\n", philo->time, philo->id);
	sleep(1);
}

// preciso colocar uma forma de parar o programa quando
// todos ja tiverem comido e quando um dos phios morrer.

void	*philosopher_routine(void *philosopher)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)philosopher;
	while (philo->eat_limit != 0)
	{
		philo->time += 1000;
		philo_prepare_to_eat(philo);
		philo_eat(philo);
		philo->eat_limit--;
		philo_sleep_and_think(philo);
	}
}
