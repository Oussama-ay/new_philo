/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayyoub <oayyoub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 09:21:34 by oayyoub           #+#    #+#             */
/*   Updated: 2025/02/19 09:00:46 by oayyoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_status(const char *status, t_philo *philo, int flag)
{
	pthread_mutex_lock(&philo->data->check_finish);
	philo->data->dining_over = 1;
	pthread_mutex_unlock(&philo->data->check_finish);
	if (flag)
		printf("%zu	%d	%s\n",
			ft_current_time(philo->data->time_start), philo->id, status);
	else
		printf("All philosophers ate at least %d times\n",
			philo->data->eat_limit);
	return (1);
}

int	check_philosopher(t_philo *philo)
{
	size_t	time;
	int		died;

	died = 0;
	pthread_mutex_lock(&philo->data->print_lock);
	time = ft_current_time(philo->data->time_start) - philo->last_meal_time;
	if (time >= philo->data->time_to_die)
		died = 1;
	pthread_mutex_unlock(&philo->data->print_lock);
	if (died)
		return (print_status("died", philo, 1));
	return (0);
}

int	monitor_philosophers(t_philo *philo)
{
	int	i;
	int	all_ate;

	while (1)
	{
		i = 0;
		all_ate = 1;
		while (i < philo->data->nbr_philo)
		{
			if (check_philosopher(&philo[i]))
				return (1);
			pthread_mutex_lock(&philo->data->print_lock);
			if (philo->data->eat_limit < 0
				|| philo[i].meals_eaten < philo->data->eat_limit)
				all_ate = 0;
			pthread_mutex_unlock(&philo->data->print_lock);
			i++;
		}
		if (all_ate)
			return (print_status(NULL, philo, 0));
		usleep(1000);
	}
}
