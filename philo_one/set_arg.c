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

static int	ft_strlen(char *str)
{
	char *beg;

	beg = str;
	while (*str)
		str++;
	return ((int)(str - beg));
}

static int	arg_atoi(char *str)
{
	int	nb;

	nb = 0;
	while ((unsigned char)(*str - '0') < 10)
	{
		nb = nb * 10 + *str - '0';
		str++;
	}
	if (*str)
		return (-1);
	return (nb);
}

int set_arg(t_args *arg, int argc, char **argv)
{
	int		nb;

	if (ft_strlen(argv[1]) > 9 || (nb = arg_atoi(argv[1])) < 0)
		return (1);
	arg->philos = nb;
	if (ft_strlen(argv[2]) > 9 || (nb = arg_atoi(argv[2])) < 0)
		return (1);
	arg->time_die = nb;
	if (ft_strlen(argv[3]) > 9 || (nb = arg_atoi(argv[3])) < 0)
		return (1);
	arg->time_eat = nb;
	if (ft_strlen(argv[4]) > 9 || (nb = arg_atoi(argv[4])) < 0)
		return (1);
	arg->time_sleep = nb;
	arg->eat_count = -1;
	if (argc == 5)
		return (0);
	if (ft_strlen(argv[5]) > 9 || (nb = arg_atoi(argv[5])) < 0)
		return (1);
	arg->eat_count = nb;
	return (0);
}
