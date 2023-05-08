/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:41:41 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/08 16:00:18 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static int	validate_numeric_values(char *argv[], t_data *data);
static int	no_philosophers(char *argv[]);

void	check_args(int argc, char *argv[], t_data *data)
{
	if (argc < 5 || argc > 6)
	{
		ft_putstr_fd("Invalid Number of args\n", 2);
		exit(2);
	}
	if (!validate_numeric_values(argv, data))
	{
		ft_putstr_fd("Args are not Numeric\n", 2);
		exit(2);
	}
	if (no_philosophers(argv))
	{
		ft_putstr_fd("No philosophers\n", 2);
		exit (2);
	}
}

static int	validate_numeric_values(char *argv[], t_data *data)
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

static int	no_philosophers(char *argv[])
{
	int	number_of_philosophers;

	number_of_philosophers = ft_atoi(argv[1]);
	if (number_of_philosophers < 1)
	{
		return (1);
	}
	return (0);
}
