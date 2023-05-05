/* ************************************************************************** */
/*                                                                          */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:10:10 by gsmereka          #+#    #+#             */
/*   Updated: 2022/11/16 17:39:59 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static int	compare_absolute_values(char *nbr_copy, char *original_nbr);
static int	check_integer_size(char *original_nbr, t_data *data);
static int	check_if_is_numeric(char *arg, t_data *data);

int	validate_int(char *arg, t_data *data)
{
	if (!check_if_is_numeric(arg, data))
		return (0);
	if (!check_integer_size(arg, data))
		return (0);
	return (1);
}

static int	check_if_is_numeric(char *arg, t_data *data)
{
	int	i;

	i = 0;
	while ((arg[i] >= '\t' && arg[i] <= '\r') || arg[i] == ' ')
		i++;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (!ft_isdigit(arg[i]))
		return (0);
	while (ft_isdigit(arg[i]))
		i++;
	if (arg[i] != '\0')
		return (0);
	return (1);
}

static int	check_integer_size(char *original_nbr, t_data *data)
{
	char	*nbr_copy;
	int		diff;
	int		nbr;

	nbr = ft_atoi(original_nbr);
	nbr_copy = ft_itoa(nbr);
	if (!nbr_copy)
		return (0);
	diff = compare_absolute_values(nbr_copy, original_nbr);
	free(nbr_copy);
	if (diff != 0)
		return (0);
	return (1);
}

static int	compare_absolute_values(char *nbr_copy, char *original_nbr)
{
	int	diff;

	if ((*original_nbr != '-') && *nbr_copy == '-')
		return (-1);
	while ((*original_nbr >= '\t' && *original_nbr <= '\r')
		|| *original_nbr == ' ')
		original_nbr++;
	if (*original_nbr == '+' || *original_nbr == '-')
		original_nbr++;
	while (*original_nbr == '0' && *original_nbr + 1 != '\0')
		original_nbr++;
	if (*nbr_copy == '-')
		nbr_copy++;
	diff = ft_strncmp(nbr_copy, original_nbr,
			ft_strlen(original_nbr));
	return (diff);
}
