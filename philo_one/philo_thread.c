/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 17:25:48 by matrus            #+#    #+#             */
/*   Updated: 2020/10/03 17:48:21 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int			officiant;
t_philosopher **g_party;
time_t		stamp[20];

void		*philo_thread(void *arg)
{
	t_philosopher	*dekart;
	int				order;
	int				permission;
	int				i;

	dekart = (t_philosopher*)arg;
	dekart->last_eat_time = get_timestamp();
	//
	stamp[dekart->num - 1] = dekart->last_eat_time;
	//

	while (!*dekart->simulation)
		;
	while (*dekart->simulation)
	{
//		order = 0;
//		if (dekart->num == officiant)
//			order = 1;
		order = dekart->num % 2;
		permission = 0;
		while (!permission)
		{
			i = -1;
			permission = 1;
			if (!*dekart->simulation)
				break ;
			while (++i < officiant)
				if (dekart->count_eat - g_party[i]->count_eat >= 1)
					permission = 0;
		}
		dekart->take_fork(dekart, order ? FORK_LEFT : FORK_RIGHT);
		dekart->say(dekart, SAY_TOOK_FORK, get_timestamp());
		dekart->take_fork(dekart, order ? FORK_RIGHT : FORK_LEFT);
		dekart->say(dekart, SAY_TOOK_FORK, get_timestamp());
		dekart->say(dekart, SAY_EAT, get_timestamp());
		dekart->eat(dekart, get_timestamp());
		dekart->drop_forks(dekart, order);
		dekart->say(dekart, SAY_SLEEP, get_timestamp());
		dekart->sleep(dekart);
		dekart->say(dekart, SAY_THINK, get_timestamp());
	}
	return (0);
}
