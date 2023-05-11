/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:40:32 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/10 21:02:04 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static int		observe_philosophers(t_observer *observer, t_data *data);
static void	check_philo_status(int i, t_observer *observer, t_data *data);
// static int		philo_eat_all(int philo, t_data *data);
static void		kill_philosopher(int philo, t_observer *observer, t_data *data);

void	*observer_routine(void *observer_data)
{
	t_observer	observer;
	t_data		*data;

	data = (t_data *)observer_data;
	observer = (t_observer){0};
	pthread_mutex_lock(data->start_time_mutex);
	observer.start_time = data->start_time;
	pthread_mutex_unlock(data->start_time_mutex);
	while (TRUE)
	{
		if (!observe_philosophers(&observer, data))
			break ;
	}
	return (NULL);
}

static int	observe_philosophers(t_observer *observer, t_data *data)
{
	int	philo;

	philo = 0;
	if (observer->philo_dones == data->config->number_of_philosophers)
		return (0);
	while (philo < data->config->number_of_philosophers)
	{
		check_philo_status(philo, observer, data);
		observer->current_time = get_time_now() - observer->start_time;
		if (observer->philo_done == TRUE)
			observer->philo_dones++;
		else if (observer->current_time - observer->last_meal_time
			> data->config->time_to_die)
		{
			kill_philosopher(philo, observer, data);
			return (0);
		}
		philo++;
	}
	return (1);
}

static void	check_philo_status(int i, t_observer *observer, t_data *data)
{
	pthread_mutex_lock(data->philosophers[i]->shared->philo_status_mutex);
	observer->last_meal_time = data->philosophers[i]->shared->last_meal_time;
	observer->philo_done = data->philosophers[i]->shared->done;
	pthread_mutex_unlock(data->philosophers[i]->shared->philo_status_mutex);
}

static void	kill_philosopher(int philo, t_observer *observer, t_data *data)
{
	pthread_mutex_lock(data->need_stop_mutex);
	data->need_stop = TRUE;
	pthread_mutex_unlock(data->need_stop_mutex);
	printf("%ld %d died ----------------- DEAD\n", observer->current_time, data->philosophers[philo]->id);
}
