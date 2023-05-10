/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:40:32 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/09 21:55:17 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

long int get_time_now(t_observer *observer)
{
    struct timeval time;

    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - observer->start_time);
}

long int	check_philo_last_meal(int i, t_data *data)
{
	long int	last_meal_time;

	pthread_mutex_lock(data->philosophers[i]->shared->last_meal_mutex);
	last_meal_time = data->philosophers[i]->shared->last_meal_time;
	pthread_mutex_unlock(data->philosophers[i]->shared->last_meal_mutex);
	return (last_meal_time);
}

int	all_philo_complete(t_data *data)
{;
	pthread_mutex_lock(data->philo_dones_mutex);
	if (data->philo_dones == data->config->number_of_philosophers)
	{
		pthread_mutex_unlock(data->philo_dones_mutex);
		return (1);
	}
	pthread_mutex_unlock(data->philo_dones_mutex);
	return (0);
}

void	kill_philosopher(int philo, t_observer *observer, t_data *data)
{
	printf("%ld %d died\n", observer->current_time, data->philosophers[philo]->id);
	pthread_mutex_lock(data->need_stop_mutex);
	data->need_stop = TRUE;
	pthread_mutex_unlock(data->need_stop_mutex);
}

int	observe_philosophers(t_observer *observer, t_data *data)
{
	int	philo;

	philo = 0;
	if (all_philo_complete(data))
		return (0);
	while (philo < data->config->number_of_philosophers)
	{
		observer->last_meal_time = check_philo_last_meal(philo, data);
		observer->current_time = get_time_now(observer);
		if (observer->current_time - observer->last_meal_time > data->config->time_to_die)
		{
			kill_philosopher(philo, observer, data);
			return (0);
		}
		philo++;
	}
	return (1);
}

void	*observer_routine(void *observer_data)
{
	t_observer	observer;
	t_data		*data;

	data = data = (t_data *)observer_data;
	observer = (t_observer){0};
	pthread_mutex_lock((data->start_time_mutex));
	observer.start_time = (data->start_time);
	pthread_mutex_unlock((data->start_time_mutex));
	while (TRUE)
	{
		// usleep(200);
		if (!observe_philosophers(&observer, data))
			break ;
	}
	return (NULL);
}
