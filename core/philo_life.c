/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:54:15 by acarlott          #+#    #+#             */
/*   Updated: 2023/08/04 12:52:52 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static inline int	philo_eat(t_philo *philo)
{
	if (death_time_check(philo) == DIE)
		return (DIE);
	philo->t_last_eat = cur_time(philo);
	if (death_time_check(philo) == DIE)
		return (DIE);
	pthread_mutex_lock(&philo->data->exec);
	if (death_time_check(philo) == DIE)
		return (pthread_mutex_unlock(&philo->data->exec), DIE);
	ft_print(philo, EAT);
	pthread_mutex_unlock(&philo->data->exec);
	if (death_time_check(philo) == DIE)
		return (DIE);
	if (ft_sleep(philo, philo->data->t_eat) == DIE)
		return (DIE);
	if (death_time_check(philo) == DIE)
		return (DIE);
	return (ALIVE);
}

static inline int	philo_sleep_think(t_philo *philo)
{
	ft_print(philo, SLEEP);
	if (ft_sleep(philo, philo->data->t_sleep) == DIE)
		return (DIE);
	if (death_time_check(philo) == DIE)
		return (DIE);
	ft_print(philo, THINK);
	if (death_time_check(philo) == DIE)
		return (DIE);
	return (ALIVE);
}

void	philo_life(t_philo *philo)
{
	while (philo->nb_eat != philo->data->max_eat)
	{
		if (death_time_check(philo) == DIE)
			break ;
		if (wait_fork(philo, philo->fork_l_id) == DIE)
			break ;
		if (wait_fork(philo, philo->fork_r_id) == DIE)
			break ;
		if (philo_eat(philo) == DIE)
			break ;
		unlock_fork(philo, philo->fork_l_id);
		unlock_fork(philo, philo->fork_r_id);
		if (death_time_check(philo) == DIE)
			break ;
		if (philo_sleep_think(philo) == DIE)
			break ;
		philo->nb_eat++;
	}
}
