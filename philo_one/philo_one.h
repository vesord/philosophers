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
	int				num;

	int				time_eat;
	int				time_sleep;
	time_t			time_to_die;

	time_t			*simulation;
	time_t			last_eat_time;
	int				count_eat; // add count eat check
	void			(*eat)(struct s_philosopher *self, time_t ts);
	void			(*sleep)(struct  s_philosopher *self);
	void			(*say)(struct s_philosopher *self, enum e_phrases phrase,
						   time_t ts);
	void			(*take_fork)(struct s_philosopher *self, enum e_forks frk);
	void			(*drop_forks)(struct s_philosopher *self, int order);
	pthread_mutex_t	*say_mutex;
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

extern int	officiant;
extern t_philosopher **g_party;
//


int		set_arg(t_args *arg, int argc, char **argv);

int		main_thread(t_args *arg);

t_philosopher	**initialization(t_args *arg,
						  time_t *simulation);

void	phil_say(t_philosopher *self, enum e_phrases what, time_t ts);
void	phil_sleep(t_philosopher *self);
void	phil_eat(t_philosopher *self, time_t ts);
void	phil_take_fork(t_philosopher *self, enum e_forks frk);
void	phil_drop_forks(t_philosopher *self, int order);

void	*philo_thread(void *arg);
//void	*time_to_death(void *arg);

void		print_help();
time_t		get_timestamp();
int			ft_ilen(int nb);
void	form_say_string(char *dst, time_t ts, int num, const char *phrase);
int			ft_strlen(char *str);

void		ft_putchar(char c);
void		ft_putunbr(unsigned long n);
void		ft_putstrln(const char *str);


#endif
