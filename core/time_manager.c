/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:39:55 by acarlott          #+#    #+#             */
/*   Updated: 2023/08/01 11:33:41 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_sleep(t_philo *philo, int time)
{
	int	cur;

	cur = cur_time(philo);
	while (cur_time(philo) - cur < time)
	{
		if (death_time_check(philo) == DIE)
			return (DIE);
		usleep(250);
	}
	if (death_time_check(philo) == DIE)
		return (DIE);
	return (ALIVE);
}

long long int	cur_time(t_philo *p)
{
	return (in_time() - p->data->time);
}

long long int	in_time(void)
{
	struct timeval	time;
	unsigned long	s;
	unsigned long	u;
	unsigned long	res;
	
	gettimeofday(&time, NULL);
	s = (time.tv_sec * 1000);
	u = (time.tv_usec / 1000);
	res = s + u;
	return (res);
}

int	death_time_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->die);
	if ((cur_time(philo) - philo->t_last_eat >= philo->data->t_die) && \
	philo->data->is_die == 0)
	{
		printf("%lld %d %s\n", cur_time(philo), philo->id, "died");
		philo->data->is_die = 1;
		pthread_mutex_unlock(&philo->data->die);
		return (DIE);
	}
	if (philo->data->is_die == 1)
	{
		pthread_mutex_unlock(&philo->data->die);
		return (DIE);
	}
	pthread_mutex_unlock(&philo->data->die);
	return (ALIVE);
}

// int	death_check(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->data->die);
// 	if (philo->data->is_die == 1)
// 	{
// 		pthread_mutex_unlock(&philo->data->die);
// 		return (DIE);
// 	}
// 	pthread_mutex_unlock(&philo->data->die);
// 	return (ALIVE);
// }