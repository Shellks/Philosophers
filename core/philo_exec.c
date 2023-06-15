/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:00:59 by acarlott          #+#    #+#             */
/*   Updated: 2023/06/12 21:01:48 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	*routine(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	pthread_mutex_lock(&philo->data->exec);
	pthread_mutex_unlock(&philo->data->exec);
	if (philo->id % 2 == 0)
	{
		ft_print(philo, THINK);
		usleep(50000);
	}
	else if (philo->id == philo->data->nb_th \
	&& philo->data->nb_th % 2 != 0 && philo->data->nb_th != 1)
	{
		ft_print(philo, THINK);
		usleep(1500);
	}
	philo_life(philo);
	return (NULL);
}

int	philosopher(t_data *data)
{
	int	i;
	
	if (data->max_eat == 0)
		return (TRUE);
	i = -1;
	pthread_mutex_lock(&data->exec);
	while (++i < data->nb_th)
	{
		if (pthread_create(&data->thread[i], NULL, &routine, (void *)&data->philo[i]))
		{
			write(STDERR_FILENO, "Failed to create thread\n", 24);
			return (FALSE);
		}
	}
	data->time = in_time();
	pthread_mutex_unlock(&data->exec);
	i = -1;
	while (++i < data->nb_th)
	{
		if (pthread_join(data->thread[i], NULL) != 0)
		{
			write(STDERR_FILENO, "Failed to join thread\n", 22);
			return (FALSE);
		}
	}
	return (TRUE);
}
