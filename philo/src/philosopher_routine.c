/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:36:04 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/08 17:54:21 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

long int	get_time(t_philosopher *philo)
{
	struct timeval	time;
	long int		new_time;

	gettimeofday(&time, NULL);
	new_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (new_time - (*philo->shared->start_time));
}

int	philo_prepare_to_eat(t_philosopher *philo)
{
	int	forks;

	forks = 0;
	while (forks < 2)
	{
		if (philo->shared->left_fork->available)
		{
			forks++;
			pthread_mutex_lock(philo->shared->left_fork->mutex);
			philo->shared->left_fork->available = FALSE;
			philo->shared->left_fork->holder = philo->id;
			pthread_mutex_unlock(philo->shared->left_fork->mutex);
			printf("%ld %d has taken a fork\n", get_time(philo), philo->id);
		}
		if (philo->shared->right_fork->available)
		{
			forks++;
			pthread_mutex_lock(philo->shared->right_fork->mutex);
			philo->shared->right_fork->available = FALSE;
			philo->shared->right_fork->holder = philo->id;
			pthread_mutex_unlock(philo->shared->right_fork->mutex);
			printf("%ld %d has taken a fork\n", get_time(philo), philo->id);
		}
		if (*philo->shared->need_stop)
			return (0);
	}
	return (1);
}

int	philo_eat(t_philosopher *philo)
{
	printf("%ld %d is eating\n", get_time(philo), philo->id);
	usleep(philo->time_to_eat * 1000);
	if (*philo->shared->need_stop)
		return (0);
	pthread_mutex_lock(philo->shared->right_fork->mutex);
	philo->shared->right_fork->available = TRUE;
	philo->shared->right_fork->holder = 0;
	pthread_mutex_unlock(philo->shared->right_fork->mutex);
	pthread_mutex_lock(philo->shared->left_fork->mutex);
	philo->shared->left_fork->available = TRUE;
	philo->shared->left_fork->holder = 0;
	pthread_mutex_unlock(philo->shared->left_fork->mutex);
	return (1);
}

int	philo_sleep_and_think(t_philosopher *philo)
{
	printf("%ld %d is sleeping\n", get_time(philo), philo->id);
	usleep(philo->time_to_sleep);
	if (*philo->shared->need_stop)
		return (0);
	printf("%ld %d is thinking\n", get_time(philo), philo->id);
	usleep(philo->time_to_think);
	if (*philo->shared->need_stop)
		return (0);
	return (1);
}

// preciso colocar uma forma de parar o programa quando
// todos ja tiverem comido e quando um dos phios morrer.

void	*philosopher_routine(void *philosopher)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)philosopher;
	while (philo->eat_limit != 0 && !*philo->shared->need_stop)
	{
		if (!philo_prepare_to_eat(philo))
			return (NULL);
		philo->last_meal_time = get_time(philo);
		if (!philo_eat(philo))
			return (NULL);
		philo->eat_limit--;
		if (!philo_sleep_and_think(philo))
			return (NULL);
		philo->time += 1000;
	}
}
