/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:22:12 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/05 22:22:48 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static void	free_data(t_data *data);
void	free_array_list(void **list);

void	finalize(t_data *data)
{
	free_data(data);
	exit(0);
}

void	exit_error(int status, char *msg, t_data *data)
{
	ft_putstr_fd(msg, 2);
	free_data(data);
	exit(status);
}

static void	free_data(t_data *data)
{
	if (data->config)
		free(data->config);
	if (data->forks)
		free_array_list((void **)data->forks);
	if (data->philosophers)
		free_array_list((void **)data->philosophers);
}

void	free_array_list(void **list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
}
