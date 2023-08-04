/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:23:45 by acarlott          #+#    #+#             */
/*   Updated: 2023/08/04 10:15:53 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	init_malloc(t_data *data)
{
	data->philo = malloc(sizeof(t_philo) * data->nb_th);
	if (!data->philo)
	{
		write(1, "Error with malloc\n", 18);
		free(data->locked);
		return (FALSE);
	}
	data->thread = malloc(sizeof(pthread_t) * data->nb_th);
	if (!data->thread)
	{
		write(1, "Error with malloc\n", 18);
		free(data->locked);
		free(data->philo);
		return (FALSE);
	}
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_th);
	if (!data->fork)
	{
		write(1, "Error with malloc\n", 18);
		free(data->locked);
		free(data->philo);
		free(data->thread);
		return (FALSE);
	}
	return (TRUE);
}
static int	init_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_th)
		if (pthread_mutex_init(&(data->fork[i]), NULL) != 0)
			return (FALSE);
	if (pthread_mutex_init(&(data->exec), NULL) != 0)
	{
		ft_destroy_fork(data);
		return (FALSE);
	}
	if (pthread_mutex_init(&(data->die), NULL) != 0)
	{
		ft_destroy_fork(data);
		pthread_mutex_destroy(&data->exec);
		return (FALSE);
	}
	return (TRUE);
}

int	init_philo(t_data *data)
{
	int	i;

	i = -1;
	if (init_malloc(data) == FALSE)
		return (FALSE);
	if (init_mutex(data) == FALSE)
	{
		free(data->locked);
		free(data->philo);
		free(data->thread);
		free(data->fork);
		write(1, "Error with mutex initialising\n", 31);
		return (FALSE);
	}
	while (++i < data->nb_th)
	{
		data->locked[i] = 0;
		data->philo[i].nb_eat = 0;
		data->philo[i].id = i + 1;
		data->philo[i].data = data;
		data->philo[i].fork_l_id = i;
		data->philo[i].t_last_eat = 0;
		data->philo[i].fork_r_id = (i + 1) % data->nb_th;
	}
	return (TRUE);
}
