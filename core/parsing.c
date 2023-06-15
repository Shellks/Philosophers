/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:59:12 by acarlott          #+#    #+#             */
/*   Updated: 2023/06/12 21:02:29 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = -1;
		if (argv[i][0] == '\0')
			return (FALSE);
		while (argv[i][++j])
			if (ft_isdigit(argv[i][j]) == FALSE)
				return (FALSE);
	}
	return (TRUE);
}

static int	init_value(t_data *d, int argc, char **argv)
{
	d->is_die = 0;
	d->nb_th = ft_atoi(argv[1]);
	d->t_die = ft_atoi(argv[2]);
	d->t_eat = ft_atoi(argv[3]);
	d->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		d->max_eat = ft_atoi(argv[5]);
	else
		d->max_eat = -1;
	if (d->nb_th == 0 || d->t_die == 0 || d->t_sleep == 0 || d->t_eat == 0)
	{
		write(STDERR_FILENO, "Args needs to be non-zero value\n", 32);
		return (FALSE);
	}
	d->locked = (int *)malloc(sizeof(int) * d->nb_th);
	if (!d->locked)
	{
		write(1, "Error with malloc\n", 18);
		return (FALSE);
	}
	return (TRUE);
}

int	parse(t_data *data, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		write(STDERR_FILENO, "Wrong number of arguments\n", 26);
		return (FALSE);
	}
	if (check_args(argc, argv) == FALSE)
	{
		write(STDERR_FILENO, "Args needs to be a number\n", 26);
		return (FALSE);
	}
	if (init_value(data, argc, argv) == FALSE)
		return (FALSE);
	return (TRUE);
}
