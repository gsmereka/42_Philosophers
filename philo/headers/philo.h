/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:27:17 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/10 11:37:06 by gsmereka         ###   ########.fr       */
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

// Init Data
void	init_data(char *argv[], t_data *data);
void	check_args(int argc, char *argv[]);
void	exit_error(int status, char *msg, t_data *data);
void	finalize(t_data *data);

// philosopher_routine
void	*philosopher_routine(void *data);

// prepare_threads
void	prepare_threads(t_data *data);

// observer thread
void	*observer_routine(void *observer_data);

// Utils
int		validate_int(char *arg);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(char *s);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_printf(const char *s, ...);
int		ft_toupper(int c);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
char	*ft_utoa(unsigned int n);
char	*ft_itohex(unsigned long long n);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);

#endif
