/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:27:20 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/09 12:43:41 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include <pthread.h>

# define TRUE 1
# define FALSE 0

typedef struct	s_fork
{
	int				holder;
	int 			available;
	pthread_mutex_t	*mutex;
}	t_fork;

typedef struct	s_shared
{
	t_fork			*left_fork;
	t_fork			*right_fork;
	long int		*start_time;
	int				*need_stop;
	pthread_mutex_t	**start_time_mutex;
	pthread_mutex_t	**need_stop_mutex;
	pthread_mutex_t	*last_meal_mutex;
	long int		last_meal_time;
}	t_shared;

typedef struct	s_philosopher
{
	t_shared		*shared;
	int				id;
	int				eat_limit;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	int				start_time;
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
	pthread_t		*observer_thread;
	pthread_mutex_t	*need_stop_mutex;
	pthread_mutex_t	*start_time_mutex;
	long int		start_time;
	int				need_stop;
}	t_data;

#endif