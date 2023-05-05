/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:41:41 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/05 14:45:07 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static int	check_if_args_are_int(char *argv[], t_data *data);

void	check_args(int argc, char *argv[], t_data *data)
{
	if (argc < 5)
	{
		ft_putstr_fd("Invalid Number of args\n", 2);
		exit(2);
	}
	if (!check_if_args_are_int(argv, data))
	{
		ft_putstr_fd("Args are not Numeric\n", 2);
		exit(2);
	}
}

static int	check_if_args_are_int(char *argv[], t_data *data)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!validate_int(argv[i], data))
			return (0);
		i++;
	}
	return (1);
}
