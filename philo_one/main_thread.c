/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 15:15:21 by matrus            #+#    #+#             */
/*   Updated: 2020/10/02 15:15:22 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int			main_thread(t_args *arg)
{
	t_philosopher	**party;
	suseconds_t		simulation;
	int				i;
	int				join_status;

	simulation = 0;
	if (initialization(party, arg, &simulation))
		return (1);
	i = -1;
	while (++i < arg->philos)
		if (pthread_create(&party[i]->thread_id, NULL, philo_thread, &party[i]))
			return (1);
	simulation = get_timestamp();
	while (simulation)
		;
	i = 0;
	while (i < arg->philos)
		if (!pthread_join(party[i]->thread_id, (void**)&join_status))
		{
			if (join_status)
				return (1);
			i++;
		}
	// close mutexes and free here
	return (0);
}