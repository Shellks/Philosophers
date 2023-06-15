/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:29:40 by acarlott          #+#    #+#             */
/*   Updated: 2023/06/12 20:47:25 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_print(t_philo *philo, int msg)
{
	char	str_eat[10] = "is eating";
	char	str_fork[17] = "has taken a fork";
	char	str_sleep[12] = "is sleeping";
	char	str_think[12] = "is thinking";
	char	str_die[8] = "died";
	pthread_mutex_lock(&philo->data->write);
		if (philo->data->is_die != 1)
		{		
		if (msg == EAT)
			printf("%lld %d %s\n", cur_time(philo), philo->id, str_eat);
		else if (msg == FORK)
			printf("%lld %d %s\n", cur_time(philo), philo->id, str_fork);
		else if (msg == SLEEP)
			printf("%lld %d %s\n", cur_time(philo), philo->id, str_sleep);
		else if (msg == THINK)
			printf("%lld %d %s\n", cur_time(philo), philo->id, str_think);
		else
			printf("%lld %d %s\n", cur_time(philo), philo->id, str_die);
		}
	pthread_mutex_unlock(&philo->data->write);
}

void	ft_free(t_data *data)
{
	int	i;
	
	i = -1;
	while (++i < data->nb_th)
		pthread_mutex_destroy(&data->fork[i]);
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->exec);
	pthread_mutex_destroy(&data->die);
	free(data->locked);
	free(data->philo);
	free(data->thread);
	free(data->fork);
}