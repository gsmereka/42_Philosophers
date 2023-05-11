/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:36:04 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/10 21:35:57 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static int	philo_eat(t_philosopher *philo);
static int	philo_need_stop(t_philosopher *philo);
static int	philo_prepare_to_eat(t_philosopher *philo);
static int	philo_sleep_and_think(t_philosopher *philo);

void	*philosopher_routine(void *philosopher)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)philosopher;
	pthread_mutex_lock((*philo->shared->start_time_mutex));
	philo->start_time = (*philo->shared->start_time);
	pthread_mutex_unlock((*philo->shared->start_time_mutex));
	// printf("eat limit %d\n ", philo->eat_limit);
	// sleep(1111111111);
	while (philo->eat_limit)
	{
		if (!philo_prepare_to_eat(philo))
			return (NULL);
		if (!philo_eat(philo))
			return (NULL);
		if (!philo_sleep_and_think(philo))
			return (NULL);
	}
	return (NULL);
}

static int	philo_prepare_to_eat(t_philosopher *philo)
{
	int	forks;

	forks = 0;
	if (philo->id % 2 == 0)
		usleep(2000);
	while (forks < 2)
	{
		if (philo_need_stop(philo))
			return (0);
		pthread_mutex_lock(philo->shared->left_fork->mutex);
		pthread_mutex_lock(philo->shared->right_fork->mutex);
		if (philo->shared->left_fork->available)
		{
			philo->shared->left_fork->available = FALSE;
			printf("%ld %d has taken a fork\n",
				get_time_now() - philo->start_time, philo->id);
			forks++;
		}
		pthread_mutex_unlock(philo->shared->left_fork->mutex);
		if (philo->shared->right_fork->available)
		{
			philo->shared->right_fork->available = FALSE;
			printf("%ld %d has taken a fork\n",
				get_time_now() - philo->start_time, philo->id);
			forks++;
		}
		pthread_mutex_unlock(philo->shared->right_fork->mutex);
	}
	return (1);
}


static int	philo_eat(t_philosopher *philo)
{
	long int	meal_time;

	meal_time = get_time_now() - philo->start_time;
	philo->eat_limit--;
	if (!philo->eat_limit)
	{
		pthread_mutex_lock(philo->shared->philo_status_mutex);
		philo->shared->done = TRUE;
		pthread_mutex_unlock(philo->shared->philo_status_mutex);
	}
	else
	{
		pthread_mutex_lock(philo->shared->philo_status_mutex);
		philo->shared->last_meal_time = meal_time;
		pthread_mutex_unlock(philo->shared->philo_status_mutex);
	}
	if (philo_need_stop(philo))
		return (0);
	printf("%ld %d is eating\n", meal_time, philo->id);
	usleep(philo->time_to_eat);
	return (1);
}

static int	philo_sleep_and_think(t_philosopher *philo)
{
	if (philo_need_stop(philo))
		return (0);
	printf("%ld %d is sleeping\n",
		get_time_now() - philo->start_time, philo->id);
	pthread_mutex_lock(philo->shared->right_fork->mutex);
	philo->shared->right_fork->available = TRUE;
	pthread_mutex_unlock(philo->shared->right_fork->mutex);
	pthread_mutex_lock(philo->shared->left_fork->mutex);
	philo->shared->left_fork->available = TRUE;
	pthread_mutex_unlock(philo->shared->left_fork->mutex);
	usleep(philo->time_to_sleep);
	if (philo_need_stop(philo))
		return (0);
	printf("%ld %d is thinking\n",
		get_time_now() - philo->start_time, philo->id);
	return (1);
}

static int	philo_need_stop(t_philosopher *philo)
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
