/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:27:20 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/14 16:38:23 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include <pthread.h>

# define TRUE 1
# define FALSE 0

typedef struct s_config
{
	int			number_of_philosophers;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			number_of_times_each_philosopher_must_eat;
}	t_config;

typedef struct s_fork
{
	int				available;
	pthread_mutex_t	*mutex;
}	t_fork;

typedef struct s_status
{
	pthread_mutex_t	**need_stop_mutex;
	int				*need_stop;
	pthread_mutex_t	*status_mutex;
	int				missing_meals;
	int				last_meal_time;
}	t_status;

typedef struct s_philosopher
{
	int				is_alone;
	t_status		*status;
	int				id;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_fork			**fork_order;
	int				eat_limit;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				start_time;
	int				timer;
	int				delay_timer;
	pthread_mutex_t	**print_mutex;
}	t_philosopher;

typedef struct s_observer
{
	t_status		**philo_status;
	pthread_mutex_t	**need_stop_mutex;
	int				*need_stop;
	int				start_time;
	int				current_time;
	int				*missing_meals;
	int				last_meal_time;
	int				number_of_philosophers;
	int				time_to_die;
	pthread_mutex_t	**print_mutex;
}	t_observer;

typedef struct s_data
{
	t_status		**philo_status;
	t_config		*config;
	t_fork			**forks;
	pthread_t		*observer_thread;
	t_observer		*observer;
	pthread_t		**philo_threads;
	t_philosopher	**philosophers;
	int				start_time;
	pthread_mutex_t	*need_stop_mutex;
	int				need_stop;
	pthread_mutex_t	*print_mutex;
}	t_data;

#endif