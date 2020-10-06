/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 14:46:23 by matrus            #+#    #+#             */
/*   Updated: 2020/10/02 14:46:24 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	arg_atoi(char *str)
{
	long	nb;

	nb = 0;
	while ((unsigned char)(*str - '0') < 10)
	{
		nb = nb * 10 + *str - '0';
		if (nb > 2147483647)
			break ;
		str++;
	}
	if (*str)
		return (-1);
	return ((int)nb);
}

int set_arg(t_args *arg, int argc, char **argv)
{
	int		nb;

	if ((nb = arg_atoi(argv[1])) < 0)
		return (1);
	arg->philos = nb;
	if ((nb = arg_atoi(argv[2])) < 0)
		return (1);
	arg->time_die = nb;
	if ((nb = arg_atoi(argv[3])) < 0)
		return (1);
	arg->time_eat = nb;
	if ((nb = arg_atoi(argv[4])) < 0)
		return (1);
	arg->time_sleep = nb;
	arg->eat_count = 0;
	if (argc == 5)
		return (0);
	if ((nb = arg_atoi(argv[5])) < 0)
		return (1);
	arg->eat_count = nb;
	return (0);
}
