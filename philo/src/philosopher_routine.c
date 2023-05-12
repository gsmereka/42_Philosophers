/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:36:04 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/12 14:37:43 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static int	philo_eat(t_philosopher *philo);
static int	philo_need_stop(t_philosopher *philo);
static int	philo_prepare_to_eat(int forks, t_philosopher *philo);
static void	philo_sleep_and_think(t_philosopher *philo);

void	*philosopher_routine(void *philosopher)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)philosopher;
	while (philo->eat_limit)
	{
		if (!philo_prepare_to_eat(0, philo))
			return (NULL);
		philo->timer = get_time_now() - philo->start_time;
		if (!philo_eat(philo))
			return (NULL);
		philo->timer = get_time_now() - philo->start_time;
		philo_sleep_and_think(philo);
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
		usleep(100);
	}
	return (1);
}

static int	philo_eat(t_philosopher *philo)
{
	philo->eat_limit--;
	pthread_mutex_lock(philo->shared->philo_status_mutex);
	philo->shared->last_meal_time = philo->timer;
	if (!philo->eat_limit)
		philo->shared->done = TRUE;
	pthread_mutex_unlock(philo->shared->philo_status_mutex);
	if (philo_need_stop(philo))
		return (0);
	printf("%ld %d is eating\n", philo->timer, philo->id);
	usleep(philo->time_to_eat);
	return (1);
}

static void	philo_sleep_and_think(t_philosopher *philo)
{
	printf("%ld %d is sleeping\n", philo->timer, philo->id);
	pthread_mutex_lock(philo->shared->first_fork->mutex);
	philo->shared->first_fork->available = TRUE;
	pthread_mutex_unlock(philo->shared->first_fork->mutex);
	pthread_mutex_lock(philo->shared->last_fork->mutex);
	philo->shared->last_fork->available = TRUE;
	pthread_mutex_unlock(philo->shared->last_fork->mutex);
	usleep(philo->time_to_sleep);
	printf("%ld %d is thinking\n", philo->timer, philo->id);
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
