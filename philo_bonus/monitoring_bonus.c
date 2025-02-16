/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayyoub <oayyoub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 09:21:34 by oayyoub           #+#    #+#             */
/*   Updated: 2025/02/16 14:53:14 by oayyoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	kill_philosophers(t_philo *philo, int all)
{
	int	j;

	j = 0;
	while (j < philo->data->nbr_philo)
	{
		kill(philo[j].pid, SIGKILL);
		j++;
	}
	if (all)
		printf("All philosophers ate at least %d times\n",
			philo->data->eat_limit);
	return (1);
}

void	*check_all_eat(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	i = 0;
	while (i < philo->data->nbr_philo)
	{
		sem_wait(philo->data->eat);
		i++;
	}
	kill_philosophers(philo, 1);
	return (NULL);
}

void	*check_die(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	sem_wait(philo->data->died);
	kill_philosophers(philo, 0);
	return (NULL);
}

int	monitor_philosophers(t_philo *philo)
{
	pthread_t	monitor_die;
	pthread_t	monitor_eat;

	pthread_create(&monitor_die, NULL, check_die, philo);
	pthread_detach(monitor_die);
	if (philo->data->eat_limit > 0)
	{
		pthread_create(&monitor_eat, NULL, check_all_eat, philo);
		pthread_detach(monitor_eat);
	}
	while (wait(NULL) > 0)
		;
	return (0);
}
