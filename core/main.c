/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:08:13 by acarlott          #+#    #+#             */
/*   Updated: 2023/06/12 18:57:06 by acarlott         ###   ########lyon.fr   */
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
	ft_free(&data);
	return (0);
}

