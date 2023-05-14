/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:36:04 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/14 16:26:52 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static void	wait_eating_time(t_philosopher *philo);
static void	wait_sleeping_time(t_philosopher *philo);
static void	att_status(t_philosopher *philo);

int	philo_eat(t_philosopher *philo)
{
	att_status(philo);
	if (philo_need_stop(philo))
		return (0);
	pthread_mutex_lock(*philo->print_mutex);
	printf("%d %d is eating\n", philo->timer, philo->id);
	pthread_mutex_unlock(*philo->print_mutex);
	wait_eating_time(philo);
	return (1);
}

void	philo_sleep_and_think(t_philosopher *philo)
{
	pthread_mutex_lock(*philo->print_mutex);
	printf("%d %d is sleeping\n", philo->timer, philo->id);
	pthread_mutex_unlock(*philo->print_mutex);
	pthread_mutex_lock(philo->fork_order[0]->mutex);
	pthread_mutex_lock(philo->fork_order[1]->mutex);
	philo->fork_order[0]->available = TRUE;
	philo->fork_order[1]->available = TRUE;
	pthread_mutex_unlock(philo->fork_order[0]->mutex);
	pthread_mutex_unlock(philo->fork_order[1]->mutex);
	wait_sleeping_time(philo);
	if (philo_need_stop(philo))
		return ;
	philo->timer = get_time_now() - philo->start_time;
	pthread_mutex_lock(*philo->print_mutex);
	printf("%d %d is thinking\n", philo->timer, philo->id);
	pthread_mutex_unlock(*philo->print_mutex);
}

static void	wait_eating_time(t_philosopher *philo)
{
	philo->delay_timer
		= (get_time_now() - philo->start_time - philo->timer) * 1000;
	if (philo->time_to_eat - philo->delay_timer < 0)
		philo->delay_timer = 0;
	usleep(philo->time_to_eat - philo->delay_timer);
	philo->timer = get_time_now() - philo->start_time;
}

static void	wait_sleeping_time(t_philosopher *philo)
{
	philo->delay_timer
		= (get_time_now() - philo->start_time - philo->timer) * 1000;
	if (philo->time_to_sleep - philo->delay_timer < 0)
		philo->delay_timer = 0;
	usleep(philo->time_to_sleep - philo->delay_timer);
}

static void	att_status(t_philosopher *philo)
{
	philo->eat_limit--;
	pthread_mutex_lock(philo->status->status_mutex);
	philo->status->last_meal_time = philo->timer;
	philo->status->missing_meals--;
	pthread_mutex_unlock(philo->status->status_mutex);
}
