/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 09:29:58 by eabdelha          #+#    #+#             */
/*   Updated: 2022/03/26 12:32:54 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

# define TO_USEC 1000

# define TAKE_FORK "has taken a fork"
# define SLEEP_STAT "is sleeping"
# define THINK_STAT "is thinking"
# define EAT_STAT "is eating"
# define DEAD_STAT "died"

typedef struct s_times
{
	int		sim_over_nbr;
	size_t	tt_die;
	size_t	tt_eat;
	size_t	tt_sleep;
}	t_times;

typedef struct s_info
{
	bool			*is_eating;
	unsigned int	*had_eat;
	size_t			*tt_die_record;
	size_t			*tt_eat_record;
	size_t			*tt_slp_record;
	pthread_t		*philo;
	pthread_mutex_t	*mutex_fork;
	char			dead_philo;
	unsigned int	philo_nbr;
	size_t			time_refrence;
	t_times			time;
	pthread_mutex_t	mutex_dead;
	pthread_mutex_t	mutex_is_eating;
	pthread_mutex_t	mutex_print_msg;
}	t_info;

size_t	get_time(t_info *info);
int		ft_atoi(const char *str);
int		check_sim_over(t_info *info);
int		create_pthreads(t_info *info);
void	check_dead_stat(t_info *info);
void	*allocate(size_t size, int len, int init_var);
void	change_tt_die_record(t_info *info, int philo_index);
int		print_message(t_info *info, int philo_index, char *msg, int stop_sim);

#endif
