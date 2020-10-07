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

static void	joining(t_philosopher **party, int count)
{
	int	i;
	int status_1;
//	int status_2;

	i = 0;
	while (i < count)
	{
		status_1 = pthread_mutex_unlock(party[i]->l_fork);
//		status_2 = pthread_mutex_unlock(party[i]->eatdeath_mutex);
		if (status_1 == 0)
			i++;
	}
	i = 0;
	while (i < count)
	{
		status_1 = pthread_join(party[i]->thread_id, NULL);
//		status_2 = pthread_join(party[i]->thread_deathcheck_id, NULL);
		if (status_1 == 0)
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
//	int		min_eated;

	while (*simulation)
	{
		finished_eat = 0;
		i = -1;
//		min_eated = party[0]->count_eat;
		while (*simulation && ++i < arg->philos)
		{
			if (arg->eat_count && party[i]->count_eat >= arg->eat_count)
				finished_eat++;
//			if (party[i]->count_eat < min_eated)
//				min_eated = party[i]->count_eat;
//			if (party[i]->count_eat > min_eated)
//				party[i]->permission_to_eat = 0;
//			else
//				party[i]->permission_to_eat = 1;
		}
		if (finished_eat == arg->philos)
			*simulation = 0;
	}
}

#include <stdio.h>

int			main_thread(t_args *arg)
{
	t_philosopher	**party;
	time_t			simulation;
	int				i;

	if (!(get_timestamp()))
		return (1);
	party = NULL;
	if (!(party = initialization(arg, &simulation)))
		return (1);
	i = -1;
	simulation = 1;
	while (++i < arg->philos)
	{
		party[i]->last_eat_time = get_timestamp();
		if (pthread_create(&party[i]->thread_id, NULL, philo_thread, party[i]))
			return (1);
		usleep(600);
//		if (pthread_create(&party[i]->thread_deathcheck_id, NULL,
//											philo_deathcheck_thread, party[i]))
//			return (1);
	}
//	i = 0;
//	while (i < arg->philos)
//		if (party[i]->is_ready == 2)
//			i++;
	simulation = get_timestamp();
	control_simulation(party, arg, &simulation);

	printf("\n\n");
	i = -1;
	while (++i < arg->philos)
	{
		printf("Philo %i has eaten %i times\n", party[i]->num, party[i]->count_eat);
	}

	clear_restaurant(party, arg->philos);
	return (0);
}
