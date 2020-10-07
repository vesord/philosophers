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

void	ft_usleep(time_t mcs)
{
	time_t		cur_time;

	cur_time = get_timestamp();
	while (get_timestamp() - cur_time < mcs)
		usleep(2);
}
