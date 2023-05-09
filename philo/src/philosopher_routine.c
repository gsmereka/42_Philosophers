/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:36:04 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/09 12:35:11 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

long int	get_time(long int start_time)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - start_time);
}

int	philo_prepare_to_eat(t_philosopher *philo)
{
	int	forks;

	forks = 0;
	while (forks < 2)
	{
		pthread_mutex_lock(philo->shared->mutex);
		if (*philo->shared->need_stop)
		{
			pthread_mutex_unlock(philo->shared->mutex);
			return (0);
		}
		pthread_mutex_unlock(philo->shared->mutex);
		pthread_mutex_lock(philo->shared->left_fork->mutex);
		pthread_mutex_lock(philo->shared->right_fork->mutex);
		if (philo->shared->left_fork->available)
		{
			philo->shared->left_fork->available = FALSE;
			pthread_mutex_lock(philo->shared->mutex);
			printf("%ld %d has taken a fork\n", get_time((*philo->shared->start_time)), philo->id);
			pthread_mutex_unlock(philo->shared->mutex);
			forks++;
		}
		if (philo->shared->right_fork->available)
		{
			philo->shared->right_fork->available = FALSE;
			pthread_mutex_lock(philo->shared->mutex);
			printf("%ld %d has taken a fork\n", get_time((*philo->shared->start_time)), philo->id);
			pthread_mutex_unlock(philo->shared->mutex);
			forks++;
		}
		pthread_mutex_unlock(philo->shared->right_fork->mutex);
		pthread_mutex_unlock(philo->shared->left_fork->mutex);

	}
	return (1);
}

int	philo_eat(t_philosopher *philo)
{	
	pthread_mutex_lock(philo->shared->mutex);
	printf("%ld %d is eating\n", get_time((*philo->shared->start_time)), philo->id);
	pthread_mutex_unlock(philo->shared->mutex);
	usleep(philo->time_to_eat);
	pthread_mutex_lock(philo->shared->mutex);
	if (*philo->shared->need_stop)
	{
		pthread_mutex_unlock(philo->shared->mutex);
		return (0);
	}
	pthread_mutex_unlock(philo->shared->mutex);
	pthread_mutex_lock(philo->shared->right_fork->mutex);
	pthread_mutex_lock(philo->shared->left_fork->mutex);
	philo->shared->right_fork->available = TRUE;
	philo->shared->left_fork->available = TRUE;
	pthread_mutex_unlock(philo->shared->right_fork->mutex);
	pthread_mutex_unlock(philo->shared->left_fork->mutex);
	return (1);
}

int	philo_sleep_and_think(t_philosopher *philo)
{
	pthread_mutex_lock(philo->shared->mutex);
	printf("%ld %d is sleeping\n", get_time((*philo->shared->start_time)), philo->id);
	pthread_mutex_unlock(philo->shared->mutex);
	usleep(philo->time_to_sleep);
	pthread_mutex_lock(philo->shared->mutex);
	if (*philo->shared->need_stop)
	{
		pthread_mutex_unlock(philo->shared->mutex);
		return (0);
	}
	pthread_mutex_unlock(philo->shared->mutex);
	pthread_mutex_lock(philo->shared->mutex);
	printf("%ld %d is thinking\n", get_time((*philo->shared->start_time)), philo->id);
	pthread_mutex_unlock(philo->shared->mutex);
	usleep(philo->time_to_think);
	pthread_mutex_lock(philo->shared->mutex);
	if (*philo->shared->need_stop)
	{
		pthread_mutex_unlock(philo->shared->mutex);
		return (0);
	}
	pthread_mutex_unlock(philo->mutex);
	return (1);
}

// preciso colocar uma forma de parar o programa quando
// todos ja tiverem comido e quando um dos phios morrer.

void	*philosopher_routine(void *philosopher)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)philosopher;
	pthread_mutex_lock(philo->shared->mutex);
	philo->start_time = (*philo->shared->start_time);
	pthread_mutex_unlock(philo->shared->mutex);
	while (philo->eat_limit)
	{
		if (!philo_prepare_to_eat(philo))
			return (NULL);
		pthread_mutex_lock(philo->mutex);
		philo->last_meal_time = get_time(philo->start_time);
		pthread_mutex_unlock(philo->mutex);
		if (!philo_eat(philo))
			return (NULL);
		philo->eat_limit--;
		if (!philo_sleep_and_think(philo))
			return (NULL);
	}
}
