/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayyoub <oayyoub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 08:24:12 by oayyoub           #+#    #+#             */
/*   Updated: 2025/02/16 14:52:48 by oayyoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6 || check_input(av + 1))
		print_error ("Error: Invalid input\n");
	_input(av + 1, &data);
	start_dining(&data);
	return (0);
}
