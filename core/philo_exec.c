/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:00:59 by acarlott          #+#    #+#             */
/*   Updated: 2023/08/04 10:54:06 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	*routine(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	pthread_mutex_lock(&philo->data->exec);
	pthread_mutex_unlock(&philo->data->exec);
	if (philo->data->max_eat == 0)
		return (NULL);
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
	philo_life(philo);
	return (NULL);
}

void	philosopher(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&data->exec);
	while (++i < data->nb_th)
	{
		if (pthread_create(&data->thread[i], NULL, &routine, (void *)&data->philo[i]))
		{
			printf("Failed to create thread\n");
			pthread_mutex_unlock(&data->exec);
			return ;
		}
	}
	i = -1;
	data->time = in_time();
	pthread_mutex_unlock(&data->exec);
	while (++i < data->nb_th)
	{
		if (pthread_join(data->thread[i], NULL) != 0)
		{
			printf("Failed to join thread\n");
			return ;
		}
	}
}
