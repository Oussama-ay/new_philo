/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayyoub <oayyoub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 08:38:40 by oayyoub           #+#    #+#             */
/*   Updated: 2025/02/26 17:52:12 by oayyoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	_print(t_philo *philo, const char *msg)
{
	int	is_eating;

	pthread_mutex_lock(&philo->data->print_lock);
	pthread_mutex_lock(&philo->data->check_finish);
	if (philo->data->dining_over)
	{
		pthread_mutex_unlock(&philo->data->print_lock);
		pthread_mutex_unlock(&philo->data->check_finish);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->check_finish);
	is_eating = ft_strcmp(msg, EAT);
	printf("%zu	%d	%s\n",
		ft_current_time(philo->data->time_start), philo->id, msg);
	if (is_eating == 0)
	{
		philo->last_meal_time = ft_current_time(philo->data->time_start);
		philo->meals_eaten++;
	}
	pthread_mutex_unlock(&philo->data->print_lock);
	return (0);
}

void	*single_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	_print(philo, THINK);
	_print(philo, FORK);
	usleep(philo->data->time_to_die * 1000);
	return (NULL);
}

int	_eating(t_philo *philo)
{
	(pthread_mutex_lock(philo->left_fork), _print(philo, FORK));
	(pthread_mutex_lock(philo->right_fork), _print(philo, FORK));
	if (_print(philo, EAT))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

void	*philos_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0 || philo->id == philo->data->nbr_philo)
		usleep(1000);
	while (1)
	{
		if (_print(philo, THINK))
			break ;
		if (philo->data->nbr_philo % 2)
			usleep(100);
		if (_eating(philo))
			break ;
		if (_print(philo, SLP))
			break ;
		_usleep(philo->data->time_to_sleep);
	}
	return (NULL);
}

void	start_dining(t_data *data)
{
	t_philo			*philo;
	t_mutex			*forks;

	if (allocation(data->nbr_philo, &philo, &forks))
		return ;
	init_dining(data, philo, forks);
	if (data->nbr_philo == 1)
		manage_threads(philo, &single_philo_routine, data->nbr_philo, 1);
	else
		manage_threads(philo, &philos_routine, data->nbr_philo, 1);
	monitor_philosophers(philo);
	manage_threads(philo, NULL, data->nbr_philo, 0);
	cleanup_the_table(data, philo, forks);
}
