/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:29:40 by acarlott          #+#    #+#             */
/*   Updated: 2023/08/04 12:51:49 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_odd_philo_manager(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		printf("%lld %d %s\n", cur_time(philo), philo->id, "is thinking");
		usleep(50000);
	}
	else if (philo->id == philo->data->nb_th \
	&& philo->data->nb_th % 2 != 0 && philo->data->nb_th != 1)
	{
		printf("%lld %d %s\n", cur_time(philo), philo->id, "is thinking");
		usleep(1500);
	}
}

void	ft_print(t_philo *philo, int msg)
{
	pthread_mutex_lock(&philo->data->die);
	if (philo->data->is_die != 1)
	{
		if (msg == EAT)
		{
			printf("%lld %d has taken a fork\n", cur_time(philo), philo->id);
			printf("%lld %d has taken a fork\n", cur_time(philo), philo->id);
			printf("%lld %d is eating\n", cur_time(philo), philo->id);
		}
		else if (msg == SLEEP)
			printf("%lld %d is sleeping\n", cur_time(philo), philo->id);
		else if (msg == THINK)
			printf("%lld %d is thinking\n", cur_time(philo), philo->id);
	}
	pthread_mutex_unlock(&philo->data->die);
}

void	ft_destroy_fork(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_th)
		pthread_mutex_destroy(&data->fork[i]);
}

void	ft_free_destroy(t_data *data)
{
	ft_destroy_fork(data);
	pthread_mutex_destroy(&data->exec);
	pthread_mutex_destroy(&data->die);
	free(data->locked);
	free(data->philo);
	free(data->thread);
	free(data->fork);
}
