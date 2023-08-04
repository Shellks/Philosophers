/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:08:13 by acarlott          #+#    #+#             */
/*   Updated: 2023/08/04 10:24:32 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	
	if (parse(&data, argc, argv) == FALSE)
		return (ERR_ARGS);
	if (init_philo(&data) == FALSE)
		return (ERR_ARGS);
	philosopher(&data);
	ft_free_destroy(&data);
	return (0);
}

