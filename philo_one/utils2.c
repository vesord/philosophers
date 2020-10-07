/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:21:02 by matrus            #+#    #+#             */
/*   Updated: 2020/10/06 13:21:23 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

time_t		g_cur_time;

void	*time_count_thread()
{
	time_t begin;

	begin = get_timestamp();
	while (1)
	{
		g_cur_time = (begin - get_timestamp()) / 1000;
	}
}

void	ft_usleep(time_t mcs)
{
	time_t		beg_time;

	beg_time = g_cur_time;
	while (g_cur_time - beg_time < mcs)
		usleep(20);
}

time_t	get_timestamp(void)
{
	struct timeval			t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000000 + t.tv_usec);
}
