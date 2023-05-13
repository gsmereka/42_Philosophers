/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:41:41 by gsmereka          #+#    #+#             */
/*   Updated: 2023/05/13 19:58:38 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static int	validate_numeric_values(char *argv[]);
static int	null_or_negative_args(char *argv[]);

void	check_args(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
	{
		ft_putstr_fd("error: invalid number of args\n", 2);
		exit(2);
	}
	if (!validate_numeric_values(argv))
	{
		ft_putstr_fd("error: not numeric args\n", 2);
		exit(2);
	}
	if (null_or_negative_args(argv))
	{
		ft_putstr_fd("error: null or negative args\n", 2);
		exit (2);
	}
}

static int	validate_numeric_values(char *argv[])
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!validate_int(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	null_or_negative_args(char *argv[])
{
	if (ft_atoi(argv[1]) < 1)
		return (1);
	if (ft_atoi(argv[2]) < 0)
		return (1);
	if (ft_atoi(argv[2]) < 0)
		return (1);
	if (ft_atoi(argv[2]) < 0)
		return (1);
	if (argv[5] && ft_atoi(argv[5]) < 1)
		return (1);
	return (0);
}
