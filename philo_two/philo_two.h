/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
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
# include <semaphore.h>
# include <string.h>
# include <errno.h>
# include <sys/time.h>

enum			e_phrases
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
	pthread_t		deathcheck_id;
	int				num;
	int				time_eat;
	int				time_sleep;
	time_t			time_to_die;
	time_t			*simulation;
	time_t			last_eat_time;
	int				count_eat;
	int				is_ready;
	void			(*eat)(struct s_philosopher *self);
	void			(*sleep)(struct s_philosopher *self);
	void			(*say)(struct s_philosopher *self, enum e_phrases phrase);
	void			(*take_fork)(struct s_philosopher *self);
	void			(*drop_forks)(struct s_philosopher *self);
	sem_t			*forks_sem;
	sem_t			*eatdeath_sem;
	sem_t			*say_sem;
}				t_philosopher;

typedef struct	s_args
{
	int		philos;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		eat_count;
}				t_args;

int				set_arg(t_args *arg, int argc, char **argv);

int				main_thread(t_args *arg);

t_philosopher	**initialization(t_args *arg, time_t *simulation);

void			phil_say(t_philosopher *self, enum e_phrases what);
void			phil_sleep(t_philosopher *self);
void			phil_eat(t_philosopher *self);
void			phil_take_fork(t_philosopher *self);
void			phil_drop_forks(t_philosopher *self);

void			*philo_thread(void *arg);
void			*deathcheck_thread(void *arg);

void			print_help();

time_t			get_timestamp();
int				ft_ilen(int nb);
void			form_say_string(char *dst, time_t ts, int num,
															const char *phrase);
int				ft_strlen(const char *str);
void			ft_usleep(time_t mcs);
long			ft_pow(long a, long n);
void			form_eatdeath_sem_name(char *dst, const char *common_part,
																	int num);
void			ft_putnbr_fd(long n, int fd);
void			ft_putchar_fd(char c, int fd);
int				philo_sem_open(sem_t **dst, const char *name, int value);

#endif
