/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:36:04 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/07 00:07:49 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	philo_eat(t_philosopher *philosopher)
{
	printf("timestamp_in_ms %d has taken a fork\n", philosopher->index + 1);
	printf("timestamp_in_ms %d has taken a fork\n", philosopher->index + 1);
	printf("timestamp_in_ms %d is eating\n", philosopher->index + 1);
}

void	philo_think(t_philosopher *philosopher)
{
	printf("timestamp_in_ms %d is thinking\n", philosopher->index + 1);
}

void	philo_sleep(t_philosopher *philosopher)
{
	printf("timestamp_in_ms %d is sleeping\n", philosopher->index + 1);
}

int		setup_philosopher(t_philosopher *philosopher, t_data *data)
{
	int	philo_index;
	int	eat_limit;

	*philosopher = (t_philosopher){0};
	pthread_mutex_lock(data->mutex);
	philo_index = data->philo_count;
	eat_limit = data->config->number_of_philosophers;
	data->philo_count++;
	pthread_mutex_unlock(data->mutex);
	philosopher->index = philo_index;
	philosopher->eat_limit = eat_limit;
}

void	*philosopher_routine(void *data)
{
	t_philosopher	philosopher;

	setup_philosopher(&philosopher, (t_data *)data);
	while (philosopher.eat_limit != 0)
	{
		philo_eat(&philosopher);
		philosopher.eat_limit--;
		philo_sleep(&philosopher);
		philo_think(&philosopher);
	}
}
