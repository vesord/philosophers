/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 18:36:27 by matrus            #+#    #+#             */
/*   Updated: 2020/10/09 11:48:11 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

const char				*g_forks_sem_name = "philo_forks";
const char				*g_say_sem_name = "philo_say";
const char				*g_eatdeath_sem_name_common = "philo_eatdeath";
const char				*g_finished_eat_sem_name_common = "philo_finished_eat";
const char				*g_servant_sem_name = "philo_servant";
const char				*g_simulation_sem_name = "philo_end";

static t_philosopher	*philosopher_init(t_args *arg, int i,
															time_t *simulation)
{
	t_philosopher	*kant;
	char			*sem_name;

	if (!(kant = (t_philosopher*)malloc(sizeof(t_philosopher))))
		return (NULL);
	kant->num = i + 1;
	kant->simulation = simulation;
	kant->last_eat_time = 0;
	kant->time_eat = arg->time_eat * 1000;
	kant->time_sleep = arg->time_sleep * 1000;
	kant->time_to_die = arg->time_die * 1000;
	kant->count_eat = 0;
	kant->need_to_eat_times = arg->eat_count;
	kant->philos = arg->philos;
	kant->eat = phil_eat;
	kant->sleep = phil_sleep;
	kant->say = phil_say;
	kant->take_fork = phil_take_fork;
	kant->drop_forks = phil_drop_forks;
	if (!(sem_name = form_sem_name(g_eatdeath_sem_name_common, i)))
		return (NULL);
	if (philo_sem_open(&kant->eatdeath_sem, sem_name, 0))
		return (NULL);
	free(sem_name);
	if (!(sem_name = form_sem_name(g_finished_eat_sem_name_common, i)))
		return (NULL);
	if (philo_sem_open(&kant->finished_eat, sem_name, 0))
		return (NULL);
	free(sem_name);
	return (kant);
}

static int				party_init(t_philosopher **party, t_args *arg,
															time_t *simulation)
{
	sem_t			*forks_sem;
	sem_t			*say_sem;
	sem_t			*servant_sem;
	sem_t			*simulation_sem;
	int				i;

	if (philo_sem_open(&say_sem, g_say_sem_name, 1))
		return (1);
	if (philo_sem_open(&forks_sem, g_forks_sem_name, arg->philos))
		return (1);
	if (philo_sem_open(&servant_sem, g_servant_sem_name, arg->philos / 2))
		return (1);
	if (philo_sem_open(&simulation_sem, g_simulation_sem_name, 0))
		return (1);
	i = -1;
	while (++i < arg->philos)
	{
		if (!(party[i] = philosopher_init(arg, i, simulation)))
			return (1);
		party[i]->forks_sem = forks_sem;
		party[i]->say_sem = say_sem;
		party[i]->servant_sem = servant_sem;
		party[i]->simulation_sem = simulation_sem;
	}
	return (0);
}

t_philosopher			**initialization(t_args *arg, time_t *simulation)
{
	t_philosopher **party;

	if (!(party = (t_philosopher**)malloc(sizeof(t_philosopher*) *
																arg->philos)))
		return (NULL);
	if (party_init(party, arg, simulation))
		return (NULL);
	return (party);
}
