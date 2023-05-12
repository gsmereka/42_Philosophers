/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:36:04 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/11 22:41:49 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static int	philo_eat(t_philosopher *philo);
static int	philo_need_stop(t_philosopher *philo);
static int	philo_prepare_to_eat(int forks, t_philosopher *philo);
static int	philo_sleep_and_think(t_philosopher *philo);

void	*philosopher_routine(void *philosopher)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)philosopher;
	while (philo->eat_limit)
	{
		if (!philo_prepare_to_eat(0, philo))
			return (NULL);
		if (!philo_eat(philo))
			return (NULL);
		if (!philo_sleep_and_think(philo))
			return (NULL);
	}
	return (NULL);
}

static int	philo_prepare_to_eat(int forks, t_philosopher *philo)
{
	while (forks < 2)
	{
		pthread_mutex_lock(philo->shared->first_fork->mutex);
		pthread_mutex_lock(philo->shared->last_fork->mutex);
		if (philo->shared->first_fork->available)
		{
			philo->shared->first_fork->available = FALSE;
			printf("%ld %d has taken a fork\n",
				get_time_now() - philo->start_time, philo->id);
			forks++;
		}
		pthread_mutex_unlock(philo->shared->first_fork->mutex);
		if (philo->shared->last_fork->available)
		{
			philo->shared->last_fork->available = FALSE;
			printf("%ld %d has taken a fork\n",
				get_time_now() - philo->start_time, philo->id);
			forks++;
		}
		pthread_mutex_unlock(philo->shared->last_fork->mutex);
		if (philo_need_stop(philo))
			return (0);
	}
	return (1);
}

static int	philo_eat(t_philosopher *philo)
{
	long int	meal_time;

	meal_time = get_time_now() - philo->start_time;
	if (philo_need_stop(philo))
		return (0);
	printf("%ld %d is eating\n", meal_time, philo->id);
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
	usleep(philo->time_to_eat);
	return (1);
}

static int	philo_sleep_and_think(t_philosopher *philo)
{
	if (philo_need_stop(philo))
		return (0);
	printf("%ld %d is sleeping\n",
		get_time_now() - philo->start_time, philo->id);
	pthread_mutex_lock(philo->shared->first_fork->mutex);
	philo->shared->first_fork->available = TRUE;
	pthread_mutex_unlock(philo->shared->first_fork->mutex);
	pthread_mutex_lock(philo->shared->last_fork->mutex);
	philo->shared->last_fork->available = TRUE;
	pthread_mutex_unlock(philo->shared->last_fork->mutex);
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
