/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayyoub <oayyoub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 08:41:13 by oayyoub           #+#    #+#             */
/*   Updated: 2025/02/25 10:19:11 by oayyoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	allocation(int nbr_philo, t_philo **philo, t_mutex **forks)
{
	int	fail;

	fail = 0;
	*philo = (t_philo *)malloc(sizeof(t_philo) * nbr_philo);
	*forks = (t_mutex *)malloc(sizeof(t_mutex) * nbr_philo);
	if (!*philo || !*forks)
	{
		fail = 1;
		if (*philo)
			free(*philo);
		if (*forks)
			free(*forks);
	}
	return (fail);
}

static void	init_data_mutex(t_data *data, t_mutex *forks)
{
	int	i;

	data->dining_over = 0;
	data->time_start = get_time();
	i = -1;
	while (++i < data->nbr_philo)
		pthread_mutex_init(&forks[i], NULL);
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->check_finish, NULL);
}

void	init_dining(t_data *data, t_philo *philo, t_mutex *forks)
{
	int		i;
	size_t	tmp;

	init_data_mutex(data, forks);
	tmp = ft_current_time(data->time_start);
	i = 0;
	while (i < data->nbr_philo)
	{
		philo[i].last_meal_time = tmp;
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].left_fork = &forks[i];
		philo[i].right_fork = &forks[(i + 1) % data->nbr_philo];
		if (philo[i].id % 2 == 0)
		{
			philo[i].left_fork = &forks[(i + 1) % data->nbr_philo];
			philo[i].right_fork = &forks[i];
		}
		philo[i].meals_eaten = 0;
		i++;
	}
}

void	manage_threads(t_philo *philo, void *(*f)(void *), int n, int flag)
{
	int	i;

	i = -1;
	if (flag)
	{
		while (++i < n)
		{
			_print(&philo[i], THINK);
			pthread_create(&philo[i].thread, NULL, f, &philo[i]);
		}
		return ;
	}
	while (++i < n)
		pthread_join(philo[i].thread, NULL);
}

void	cleanup_the_table(t_data *data, t_philo *philo, t_mutex *forks)
{
	int	i;

	i = -1;
	while (++i < data->nbr_philo)
		pthread_mutex_destroy(&forks[i]);
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->check_finish);
	free(philo);
	free(forks);
}
