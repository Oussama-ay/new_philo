/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayyoub <oayyoub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 08:26:11 by oayyoub           #+#    #+#             */
/*   Updated: 2025/02/15 08:20:44 by oayyoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLP "is sleeping"
# define THINK "is thinking"

typedef pthread_mutex_t	t_mutex;

typedef struct s_data
{
	int				nbr_philo;
	int				eat_limit;
	int				dining_over;
	size_t			time_start;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	t_mutex			check_finish;
	t_mutex			print_lock;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				index;
	int				meals_eaten;
	size_t			last_meal_time;
	pthread_t		thread;
	t_data			*data;
	t_mutex			*left_fork;
	t_mutex			*right_fork;
}	t_philo;

/*---------input------------*/
int			check_input(char **av);
void		_input(char **av, t_data *data);
void		print_error(char *str);
long long	ft_atoll(const char *str);
size_t		ft_strlen(char *str);

/*---------time-------------*/
size_t		get_time(void);
size_t		ft_current_time(size_t time_start);
int			ft_strcmp(const char *s1, const char *s2);

/*----------dining-----------*/
void		start_dining(t_data *data);
int			monitor_philosophers(t_philo *philo);
int			_print(t_philo *philo, const char *msg);

/*----------dining_utils-----*/
int			allocation(int n, t_philo **philo, t_mutex **forks);
void		init_dining(t_data *data, t_philo *philo, t_mutex *forks);
void		manage_threads(t_philo *philo, void *(*f)(void *), int n, int flag);
void		cleanup_the_table(t_data *data, t_philo *philo, t_mutex *forks);

#endif