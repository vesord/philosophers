/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 14:38:18 by matrus            #+#    #+#             */
/*   Updated: 2020/10/02 14:38:20 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

time_t get_timestamp()
{
	struct timeval t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000000 + t.tv_usec);
}

int	ft_ilen(int nb)
{
	if (nb < 0)
	{
		if (nb > -10)
			return (2);
		else
			return (ft_ilen(nb / 10 * -1) + 2);
	}
	if (nb < 10)
		return (1);
	return (ft_ilen(nb / 10) + 1);
}

static long	ft_pow(long a, long n)
{
	long i;
	long res;

	i = -1;
	res = 1;
	while (++i < n)
		res *= a;
	return (res);
}

int			ft_strlen(char *str)
{
	char *beg;

	beg = str;
	while (*str)
		str++;
	return ((int)(str - beg));
}

void	form_say_string(char *dst, time_t ts, int num, const char *phrase)
{
	int i;
	int num_len;

	i = -1;
	while (++i < 13)
		dst[i] = (ts / ft_pow(10, 12 - i)) % 10 + '0';
	dst[i] = ' ';
	num_len = ft_ilen(num);
	while (-14 + ++i < num_len)
		dst[i] = (num / ft_pow(10, 13 + num_len - i)) % 10 + '0';
	dst[i] = ' ';
	while (*phrase)
		dst[++i] = *phrase++;
	dst[i + 1] = '\n';
}
