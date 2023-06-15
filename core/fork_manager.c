/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:41:39 by acarlott          #+#    #+#             */
/*   Updated: 2023/06/12 19:37:25 by acarlott         ###   ########lyon.fr   */
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
		ft_print(philo, FORK);
		ft_sleep(philo, philo->data->t_die);
		ft_print(philo, DIE);
		return (DIE);
	}
	while (check_fork(philo, fork) != TRUE)
	{
		if (philo->nb_eat != 0)
		{
			if (death_time_check(philo) == DIE)
				return (DIE);
		}
			if (death_check(philo) == DIE)
				return (DIE);
		usleep(250);
	}
	pthread_mutex_lock(&philo->data->fork[fork]);
	philo->data->locked[fork] = 1;
	pthread_mutex_unlock(&philo->data->fork[fork]);
	return (ALIVE);
}