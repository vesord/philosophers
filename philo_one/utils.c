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

void	print_help()
{
	write(1, "don't forget about help!:)\n", 27);
}

useconds_t	get_timestamp()
{
	struct timeval t;

	gettimeofday(&t, NULL);
	return (t.tv_usec);
}
