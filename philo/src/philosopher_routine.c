/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:36:04 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/09 22:45:57 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	philo_need_stop(t_philosopher *philo)
{
	pthread_mutex_lock(*philo->shared->need_stop_mutex);
	if (*philo->shared->need_stop)
	{
		pthread_mutex_unlock(*philo->shared->need_stop_mutex);
		return (1);
	}
	pthread_mutex_unlock(*philo->shared->need_stop_mutex);
	return (0);
}

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
		pthread_mutex_lock(philo->shared->left_fork->mutex);
		pthread_mutex_lock(philo->shared->right_fork->mutex);
		if (philo->shared->left_fork->available)
		{
			philo->shared->left_fork->available = FALSE;
			printf("%ld %d has taken a fork\n", get_time(philo->start_time), philo->id);
			forks++;
		}
		pthread_mutex_unlock(philo->shared->left_fork->mutex);
		if (philo->shared->right_fork->available)
		{
			philo->shared->right_fork->available = FALSE;
			printf("%ld %d has taken a fork\n", get_time(philo->start_time), philo->id);
			forks++;
		}
		pthread_mutex_unlock(philo->shared->right_fork->mutex);
		if (philo_need_stop(philo))
			return (0);
	}
	return (1);	
}

int	philo_eat(t_philosopher *philo)
{
	long int	meal_time;

	meal_time = get_time(philo->start_time);
	pthread_mutex_lock(philo->shared->last_meal_mutex);
	philo->shared->last_meal_time = meal_time;
	pthread_mutex_unlock(philo->shared->last_meal_mutex);
	printf("%ld %d is eating\n", meal_time, philo->id);
	philo->eat_limit--;
	if (!philo->eat_limit)
	{
		pthread_mutex_lock(philo->shared->right_fork->mutex);
		philo->shared->right_fork->available = TRUE;
		pthread_mutex_unlock(philo->shared->right_fork->mutex);
		pthread_mutex_lock(philo->shared->left_fork->mutex);
		philo->shared->left_fork->available = TRUE;
		pthread_mutex_unlock(philo->shared->left_fork->mutex);
		pthread_mutex_lock(*philo->shared->philo_dones_mutex);
		*philo->shared->philo_dones += 1;
		pthread_mutex_unlock(*philo->shared->philo_dones_mutex);
		usleep(philo->time_to_eat);
		return (1);
	}
	usleep(philo->time_to_eat);
	pthread_mutex_lock(philo->shared->right_fork->mutex);
	philo->shared->right_fork->available = TRUE;
	pthread_mutex_unlock(philo->shared->right_fork->mutex);
	pthread_mutex_lock(philo->shared->left_fork->mutex);
	philo->shared->left_fork->available = TRUE;
	pthread_mutex_unlock(philo->shared->left_fork->mutex);
	return (1);
}

int	philo_sleep_and_think(t_philosopher *philo)
{
	printf("%ld %d is sleeping\n", get_time(philo->start_time), philo->id);
	usleep(philo->time_to_sleep);
	printf("%ld %d is thinking\n", get_time(philo->start_time), philo->id);
	return (1);
}

void	*philosopher_routine(void *philosopher)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)philosopher;
	pthread_mutex_lock((*philo->shared->start_time_mutex));
	philo->start_time = (*philo->shared->start_time);
	pthread_mutex_unlock((*philo->shared->start_time_mutex));
	while (philo->eat_limit)
	{
		philo_prepare_to_eat(philo);
		// if (philo_need_stop(philo))
		// 	return (NULL);
		philo_eat(philo);
		if (philo_need_stop(philo))
			return (NULL);
		philo_sleep_and_think(philo);
		if (philo_need_stop(philo))
			return (NULL);
	}
	return (NULL);
}
