/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 14:31:29 by matrus            #+#    #+#             */
/*   Updated: 2020/10/02 14:31:33 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

enum	e_forks
{
	FORK_LEFT,
	FORK_RIGHT
};

enum	e_phrases
{
	SAY_TOOK_FORK,
	SAY_EAT,
	SAY_SLEEP,
	SAY_THINK,
	SAY_DEAD
};

typedef struct	s_philosopher
{
	pthread_t		thread_id;
	pthread_t		thread_id_die;
	int				num;

	int				time_eat;
	int				time_sleep;
	int				time_to_die;

	suseconds_t		*simulation;
	int				last_eat_time;
	int				is_dead;
	int				count_eat; // add count eat check
	void			(*eat)(struct s_philosopher *self, useconds_t ts);
	void			(*sleep)(struct  s_philosopher *self);
	void			(*say)(struct s_philosopher *self, enum e_phrases phrase,
						   suseconds_t ts);
	void			(*take_fork)(struct s_philosopher *self, enum e_forks frk);
	void			(*drop_forks)(struct s_philosopher *self);
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}				t_philosopher;

typedef struct	s_args
{
	int		philos;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		eat_count;
}				t_args;


int		set_arg(t_args *arg, int argc, char **argv);

int		main_thread(t_args *arg);

int		initialization(t_philosopher ***party, t_args *arg,
						  suseconds_t *simulation);

void	phil_say(t_philosopher *self, enum e_phrases what, suseconds_t ts);
void	phil_sleep(t_philosopher *self);
void	phil_eat(t_philosopher *self, useconds_t ts);
void	phil_take_fork(t_philosopher *self, enum e_forks frk);
void	phil_drop_forks(t_philosopher *self);

void	*philo_thread(void *arg);

void		print_help();
useconds_t	get_timestamp();
void		ft_putchar(char c);
void		ft_putunbr(unsigned long n);
void		ft_putstrln(const char *str);


#endif
