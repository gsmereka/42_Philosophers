/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:40:32 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/11 20:07:41 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static int		observe_philosophers(t_observer *observer);
static void		check_philo_status(int i, t_observer *observer);
static void		kill_philosopher(int philo, t_observer *observer);

void	*observer_routine(void *observer_data)
{
	t_observer	*observer;

	observer = (t_observer *)observer_data;
	while (TRUE)
	{
		if (!observe_philosophers(observer))
			break ;
	}
	return (NULL);
}

static int	observe_philosophers(t_observer *observer)
{
	int	philo;
	int	dones;

	philo = 0;
	dones = 0;
	while (philo < observer->number_of_philosophers)
	{
		if (observer->philo_done[philo] == TRUE)
			dones++;
		philo++;
	}
	if (dones == observer->number_of_philosophers)
	{
		pthread_mutex_lock(*observer->need_stop_mutex);
		*observer->need_stop = TRUE;
		pthread_mutex_unlock(*observer->need_stop_mutex);
		return (0);
	}
	philo = 0;
	while (philo < observer->number_of_philosophers)
	{
		check_philo_status(philo, observer);
		observer->current_time = get_time_now() - observer->start_time;
		if (observer->philo_done[philo] == TRUE)
		{
			(void)philo;
		}
		else if (observer->current_time - observer->last_meal_time
			> observer->time_to_die)
		{
			kill_philosopher(philo, observer);
			return (0);
		}
		philo++;
	}
	return (1);
}

static void	check_philo_status(int i, t_observer *observer)
{
	pthread_mutex_lock((observer->philosophers[0][i]->shared->philo_status_mutex));
	observer->last_meal_time = (observer->philosophers[0][i]->shared->last_meal_time);
	if ((observer->philosophers[0][i]->shared->done))
		observer->philo_done[i] = TRUE;
	pthread_mutex_unlock((observer->philosophers[0][i]->shared->philo_status_mutex));
}

static void	kill_philosopher(int philo, t_observer *observer)
{
	pthread_mutex_lock(*observer->need_stop_mutex);
	*observer->need_stop = TRUE;
	pthread_mutex_unlock(*observer->need_stop_mutex);
	printf("%ld %d died ----------------- DEAD\n", observer->current_time, observer->philosophers[0][philo]->id);
}
