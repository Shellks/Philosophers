/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:00:59 by acarlott          #+#    #+#             */
/*   Updated: 2023/08/03 15:56:15 by acarlott         ###   ########lyon.fr   */
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
	ft_odd_philo_manager(philo);
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
			write(STDERR_FILENO, "Failed to create thread\n", 24);
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
			write(STDERR_FILENO, "Failed to join thread\n", 22);
			return ;
		}
	}
}
