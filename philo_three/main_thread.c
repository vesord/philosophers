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

#include "philo_three.h"
//
#include <stdio.h>


static void	killing(t_philosopher **party, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		kill(party[i]->philo_pid, 9);
		i++;
	}
}

static void	clear_restaurant(t_philosopher **party, int count)
{
	int	i;

	killing(party, count);
	i = -1;
	while (++i < count)
		sem_close(party[i]->eatdeath_sem);
	sem_close(party[0]->say_sem);
	sem_close(party[0]->forks_sem);
	sem_close(party[0]->simulation_sem);
	i = -1;
	while (++i < count)
		free(party[i]);
	free(party);
}

//static void	control_simulation(t_philosopher **party, t_args *arg,
//															time_t *simulation)
//{
//	int		i;
//	int		finished_eat;
//
//	while (*simulation)
//	{
//		finished_eat = 0;
//		i = -1;
//		while (*simulation && ++i < arg->philos)
//		{
//			if (arg->eat_count && party[i]->count_eat >= arg->eat_count)
//				finished_eat++;
//		}
//		if (finished_eat == arg->philos)
//			*simulation = 0;
//	}
//}

int			error_on_forking(t_philosopher **party, int i)
{
	while (i > 0)
	{
		kill(party[i - 1]->philo_pid, 9);
		i--;
	}
	return (1);
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

	// create thread for watching eat count
//	control_simulation(party, arg, &simulation);
		// wait say_sem in the end

	while (++i < arg->philos)
	{
		// do forks instead threading
		party[i]->philo_pid = fork();
		if (party[i]->philo_pid < 0)
			return (error_on_forking(party, i));
		else if (party[i]->philo_pid == 0)
			philo_process(party[i]);
	}

	// wait end_simulation_sem
	sem_wait(party[0]->simulation_sem);

	// kill processes cos they're all waiting to print smth
	clear_restaurant(party, arg->philos);
	return (0);
}
