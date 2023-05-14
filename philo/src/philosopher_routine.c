/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:36:04 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/14 16:10:16 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static int	wait_forks(int forks, t_philosopher *philo);

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
	while (!forks)
	{
		pthread_mutex_lock(philo->fork_order[0]->mutex);
		pthread_mutex_lock(philo->fork_order[1]->mutex);
		if (philo->fork_order[0]->available && philo->fork_order[1])
		{
			philo->timer = get_time_now() - philo->start_time;
			philo->fork_order[0]->available = FALSE;
			philo->fork_order[1]->available = FALSE;
			// printf("%d %d has taken a fork\n",
			// 	2, 2);
			// printf("%d %d has taken a fork\n",
			// 	2, 2);
			forks++;
		}
		pthread_mutex_unlock(philo->fork_order[0]->mutex);
		pthread_mutex_unlock(philo->fork_order[1]->mutex);
		if (philo_need_stop(philo))
			return (0);
	}
	philo->timer = get_time_now() - philo->start_time;
	return (1);
}

int	philo_need_stop(t_philosopher *philo)
{
	pthread_mutex_lock(*philo->status->need_stop_mutex);
	if (*philo->status->need_stop)
	{
		pthread_mutex_unlock(*philo->status->need_stop_mutex);
		return (1);
	}
	pthread_mutex_unlock(*philo->status->need_stop_mutex);
	return (0);
}
