/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:04:02 by acarlott          #+#    #+#             */
/*   Updated: 2023/06/12 21:01:37 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define TRUE 0
# define FALSE 1
# define ERR_ARGS 2
# define ERR_MALLOC 3
# define FORK 4
# define EAT 5
# define SLEEP 6
# define THINK 7
# define DIE 8
# define ALIVE 9

typedef struct s_philo
{
	int				id;
	int				nb_eat;
	int				fork_l_id;
	int				fork_r_id;
	long long int	t_last_eat;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				is_die;
	int				nb_th;
	int				t_eat;
	int				t_die;
	int				t_sleep;
	int				max_eat;
	int				*locked;
	int				*args;
	long long int	time;
	pthread_mutex_t	*fork;
	pthread_mutex_t	die;
	pthread_mutex_t	exec;
	pthread_mutex_t	write;
	pthread_t		*thread;
	struct s_philo	*philo;
}	t_data;

long long int	in_time(void);
int				ft_isdigit(int c);
long long int	cur_time(t_philo *p);
void			ft_free(t_data *data);
int				init_philo(t_data *data);
int				ft_atoi(const char *str);
void    		philo_life(t_philo *philo);
int				death_time_check(t_philo *philo);
int				death_check(t_philo *philo);
int				wait_fork(t_philo *philo, int fork);
void			unlock_fork(t_philo *philo, int fork);
int				philosopher(t_data *data);
int				main(int argc, char **argv);
void			ft_print(t_philo *philo, int msg);
int				ft_sleep(t_philo *philo, int time);
void			death_checker(t_data *d, t_philo *p);
int				parse(t_data *data, int argc, char **argv);

#endif
