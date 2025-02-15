/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayyoub <oayyoub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 09:21:34 by oayyoub           #+#    #+#             */
/*   Updated: 2025/02/15 09:26:06 by oayyoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	kill_philosophers(t_philo *philo, int i, int all)
{
	int	j;

	j = 0;
	while (j < philo->data->nbr_philo)
	{
		if (j != i)
			kill(philo[j].pid, SIGTERM);
		j++;
	}
	if (all)
		printf("All philosophers ate at least %d times\n",
			philo->data->eat_limit);
	return (1);
}

int	check_other_philos(t_philo *philo, int i)
{
	int	j;

	philo[i].finished = 1;
	j = 0;
	while (j < philo->data->nbr_philo)
	{
		if (j != i && philo[j].finished == 0)
			return (1);
		j++;
	}
	return (0);
}

int	monitor_philosophers(t_philo *philo)
{
	int	i;
	int	all_ate;
	int	status;
	int	exit_status;

	while (1)
	{
		i = 0;
		while (i < philo->data->nbr_philo)
		{
			if (waitpid(philo[i].pid, &status, WNOHANG) > 0)
			{
				exit_status = WEXITSTATUS(status);
				all_ate = 1;
				if (exit_status == 1)
					return (kill_philosophers(philo, i, 0));
				else if (exit_status == 0 && check_other_philos(philo, i))
					all_ate = 0;
				if (all_ate)
					return (kill_philosophers(philo, i, 1));
			}
			i++;
		}
	}
}
