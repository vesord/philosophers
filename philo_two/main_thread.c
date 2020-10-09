/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 15:15:21 by matrus            #+#    #+#             */
/*   Updated: 2020/10/09 11:36:19 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static void	joining(t_philosopher **party, int count)
{
	int	i;
	int status;

	i = 0;
	while (i < count)
	{
		sem_post(party[i]->forks_sem);
		sem_post(party[i]->forks_sem);
		sem_post(party[i]->eatdeath_sem);
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
		sem_close(party[i]->eatdeath_sem);
	sem_close(party[0]->say_sem);
	sem_close(party[0]->forks_sem);
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
