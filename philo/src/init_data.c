/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:41:41 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/05 21:31:12 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static void	set_config(char *argv[], t_data *data);
static void	set_forks(t_data *data);
 
void	init_data(char *argv[], t_data *data)
{
	set_config(argv, data);
	set_forks(data);
}

static void	set_config(char *argv[], t_data *data)
{
	data->config = ft_calloc(1, sizeof(t_config));
	if (!data->config)
	{
		ft_putstr_fd("Fail to allocate data config\n", 2);
		exit(12);
	}
	data->config->number_of_philosophers = ft_atoi(argv[1]);
	data->config->time_to_die = ft_atoi(argv[2]);
	data->config->time_to_eat = ft_atoi(argv[3]);
	data->config->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->config->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		data->config->number_of_times_each_philosopher_must_eat = -1;
	data->config->time_to_think = 1000;
}

static void	set_forks(t_data *data)
{
	data->forks = ft_calloc(data->config->number_of_philosophers + 1, sizeof(t_fork));
	if (!data->forks)
	{
		ft_putstr_fd("Fail to allocate fork array\n", 2);
		exit(12);
	}
}
