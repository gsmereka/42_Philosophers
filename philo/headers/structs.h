/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:27:20 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/06 17:36:56 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include <pthread.h>

typedef struct	s_fork
{
	int	holder;
	int look;
}	t_fork;

typedef struct	s_philosopher
{
	int	holder;
	int	left_fork;
	int	right_fork;
}	t_philosopher;

typedef	struct	s_config
{
	int			number_of_philosophers;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			number_of_times_each_philosopher_must_eat;
	int			time_to_think;
}	t_config;

typedef struct s_data
{
	t_config		*config;
	t_fork			**forks;
	t_philosopher	**philosophers;
	pthread_t		**philo_threads;
	pthread_mutex_t	*mutex;
}	t_data;

#endif