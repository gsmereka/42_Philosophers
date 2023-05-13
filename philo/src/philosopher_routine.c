/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:36:04 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/13 18:04:16 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static int	philo_eat(t_philosopher *philo);
static int	philo_need_stop(t_philosopher *philo);
static int	wait_forks(int forks, t_philosopher *philo);
static void	philo_sleep_and_think(t_philosopher *philo);

void	*philosopher_routine(void *philosopher)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)philosopher;
	while (philo->eat_limit)
	{
		if (!wait_forks(0, philo))
			return (NULL);
		if (!philo_eat(philo))
			return (NULL);
		philo_sleep_and_think(philo);
		if (philo_need_stop(philo))
			return (NULL);
	}
	return (NULL);
}

static int	wait_forks(int forks, t_philosopher *philo)
{
	int	index;

	index = 0;
	if (philo->id % 2 == 1)
		usleep(200);
	while (forks < 2)
	{
		pthread_mutex_lock(philo->fork_order[index]->mutex);
		if (philo->fork_order[index]->available)
		{
			philo->fork_order[index]->available = FALSE;
			printf("%d %d has taken a fork\n",
				get_time_now() - philo->start_time, philo->id);
			forks++;
		}
		pthread_mutex_unlock(philo->fork_order[index]->mutex);
		if (!index)
			index++;
		else
			index--;
		if (philo_need_stop(philo))
			return (0);
	}
	return (1);
}

static int	philo_eat(t_philosopher *philo)
{
	philo->timer = get_time_now() - philo->start_time;
	printf("%d %d is eating\n", philo->timer, philo->id);
	philo->eat_limit--;
	pthread_mutex_lock(philo->philo_status_mutex);
	philo->last_meal_time = philo->timer;
	philo->missing_meals = philo->eat_limit;
	pthread_mutex_unlock(philo->philo_status_mutex);
	if (philo_need_stop(philo))
		return (0);
	usleep(philo->time_to_eat);
	return (1);
}

static void	philo_sleep_and_think(t_philosopher *philo)
{
	philo->timer = get_time_now() - philo->start_time;
	printf("%d %d is sleeping\n", philo->timer, philo->id);
	pthread_mutex_lock(philo->fork_order[0]->mutex);
	philo->fork_order[0]->available = TRUE;
	pthread_mutex_unlock(philo->fork_order[0]->mutex);
	pthread_mutex_lock(philo->fork_order[1]->mutex);
	philo->fork_order[1]->available = TRUE;
	pthread_mutex_unlock(philo->fork_order[1]->mutex);
	usleep(philo->time_to_sleep);
	if (philo_need_stop(philo))
		return ;
	philo->timer = get_time_now() - philo->start_time;
	printf("%d %d is thinking\n", philo->timer, philo->id);
}

static int	philo_need_stop(t_philosopher *philo)
{
	pthread_mutex_lock(*philo->need_stop_mutex);
	if (*philo->need_stop)
	{
		pthread_mutex_unlock(*philo->need_stop_mutex);
		return (1);
	}
	pthread_mutex_unlock(*philo->need_stop_mutex);
	return (0);
}
