/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:41:39 by acarlott          #+#    #+#             */
/*   Updated: 2023/08/01 11:10:57 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	unlock_fork(t_philo *philo, int fork)
{
	pthread_mutex_lock(&philo->data->fork[fork]);
	philo->data->locked[fork] = 0;
	pthread_mutex_unlock(&philo->data->fork[fork]);
}

static int	check_fork(t_philo *philo, int fork)
{
	pthread_mutex_lock(&philo->data->fork[fork]);
	if (philo->data->locked[fork] == 1)
	{
		pthread_mutex_unlock(&philo->data->fork[fork]);
		return (FALSE);
	}
	pthread_mutex_unlock(&philo->data->fork[fork]);
	return (TRUE);
}

int	wait_fork(t_philo *philo, int fork)
{
    if (philo->data->nb_th == 1)
	{
		printf("%lld %d %s\n", cur_time(philo), philo->id, "has taken a fork");
		ft_sleep(philo, philo->data->t_die);
		printf("%lld %d %s\n", cur_time(philo), philo->id, "died");
		return (DIE);
	}
	while (check_fork(philo, fork) != TRUE)
	{
		// if (philo->nb_eat != 0)
		// {
		if (death_time_check(philo) == DIE)
			return (DIE);
		// }
		// 	if (death_check(philo) == DIE)
		// 		return (DIE);
		usleep(250);
	}
	if (death_time_check(philo) == DIE)
		return (DIE);
	pthread_mutex_lock(&philo->data->fork[fork]);
	philo->data->locked[fork] = 1;
	pthread_mutex_unlock(&philo->data->fork[fork]);
	if (death_time_check(philo) == DIE)
		return (DIE);
	return (ALIVE);
}