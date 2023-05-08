/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:36:04 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/08 13:16:31 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

long int	get_time(t_philosopher *philo)
{
	struct timeval	time;
	long int		new_time;

	gettimeofday(&time, NULL);
	new_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	// printf("Tempo: \n%ld\n%ld\n", new_time, (*philo->start_time));
	return (new_time - (*philo->start_time));
}

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
			printf("%ld %d has taken a fork\n", get_time(philo), philo->id);
		}
		if (philo->right_fork->available)
		{
			forks++;
			pthread_mutex_lock(philo->right_fork->mutex);
			philo->right_fork->available = FALSE;
			philo->right_fork->holder = philo->id;
			pthread_mutex_unlock(philo->right_fork->mutex);
			printf("%ld %d has taken a fork\n", get_time(philo), philo->id);
		}
	}
}

void	philo_eat(t_philosopher *philo)
{
	printf("%ld %d is eating\n", get_time(philo), philo->id);
	usleep(philo->time_to_eat * 1000);
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
	printf("%ld %d is sleeping\n", get_time(philo), philo->id);
	usleep(philo->time_to_sleep);
	printf("%ld %d is thinking\n", get_time(philo), philo->id);
	usleep(philo->time_to_think);
}

// preciso colocar uma forma de parar o programa quando
// todos ja tiverem comido e quando um dos phios morrer.


void	*philosopher_routine(void *philosopher)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)philosopher;
	// get_start_time(philo);
	while (philo->eat_limit != 0)
	{
		philo_prepare_to_eat(philo);
		philo_eat(philo);
		philo->eat_limit--;
		philo_sleep_and_think(philo);
		philo->time += 1000;
	}
}
