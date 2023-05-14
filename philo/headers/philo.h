/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:27:17 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/14 19:25:03 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include "structs.h"

// FUNCTIONS: LIBRARIES |
// memset: string.h |
// printf: stdio.h |
// malloc, free: stdlib.h |
// write: unistd.h |
// usleep: unistd.h |
// gettimeofday: sys/time.h |
// pthread_create, pthread_detach,
// pthread_join, pthread_mutex_init, 
// pthread_mutex_destroy, pthread_mutex_lock,
// pthread_mutex_unlock: pthread.hs |

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>

// init Data
void		init_data(char *argv[], t_data *data);

// setup_threads
void		setup_threads(t_data *data);

// check_args
void		check_args(int argc, char *argv[]);

// get_time_now
int			get_time_now(void);

// finalize
void		exit_error(int status, char *msg, t_data *data);
void		finalize(t_data *data);
void		free_data(t_data *data);

// philosopher_routine
void		*philosopher_routine(void *data);
int			philo_need_stop(t_philosopher *philo);

// philosopher actions
int			philo_eat(t_philosopher *philo);
void		philo_sleep_and_think(t_philosopher *philo);

// prepare_threads
void		init_simulation(t_data *data);

// observer thread
void		*observer_routine(void *observer_data);

// validate int
int			validate_int(char *arg);

// utils
size_t		ft_strlen(const char *s);
void		ft_putstr_fd(char *s, int fd);
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_bzero(void *s, size_t n);
int			ft_atoi(const char *str);
int			ft_isdigit(int c);
char		*ft_itoa(int n);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strdup(char *s);

#endif
