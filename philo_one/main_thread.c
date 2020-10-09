/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 15:15:21 by matrus            #+#    #+#             */
/*   Updated: 2020/10/09 11:33:21 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	joining(t_philosopher **party, int count)
{
	int	i;
	int status;

	i = 0;
	while (i < count)
	{
		status = pthread_mutex_unlock(party[i]->l_fork);
		if (status == 0)
			i++;
	}
	i = 0;
	while (i < count)
	{
		status = pthread_join(party[i]->thread_id, NULL);
		if (status == 0)
			i++;
	}
}

static void	clear_restaurant(t_philosopher **party, int count)
{
	int	i;

	joining(party, count);
	i = -1;
	while (++i < count)
		pthread_mutex_destroy(party[i]->l_fork);
	pthread_mutex_destroy(party[count - 1]->l_fork + sizeof(pthread_mutex_t));
	free(party[0]->l_fork);
	i = -1;
	while (++i < count)
		free(party[i]);
	free(party);
}

static void	control_simulation(t_philosopher **party, t_args *arg,
															time_t *simulation)
{
	int		i;
	int		finished_eat;

	while (*simulation)
	{
		finished_eat = 0;
		i = -1;
		while (*simulation && ++i < arg->philos)
		{
			if (arg->eat_count >= 0 && party[i]->count_eat >= arg->eat_count)
				finished_eat++;
		}
		if (finished_eat == arg->philos)
			*simulation = 0;
	}
}

int			main_thread(t_args *arg)
{
	t_philosopher	**party;
	time_t			simulation;
	int				i;

	party = NULL;
	if (!(party = initialization(arg, &simulation)))
		return (1);
	i = -1;
	simulation = 0;
	while (++i < arg->philos)
	{
		pthread_mutex_lock(party[i]->eatdeath_mutex);
		if (pthread_create(&party[i]->thread_id, NULL, philo_thread, party[i]))
			return (1);
	}
	i = 0;
	while (i < arg->philos)
		if (party[i]->is_ready == 2)
			i++;
		else if (party[i]->is_ready == -1)
			return (1);
	simulation = get_timestamp();
	control_simulation(party, arg, &simulation);
	clear_restaurant(party, arg->philos);
	return (0);
}
