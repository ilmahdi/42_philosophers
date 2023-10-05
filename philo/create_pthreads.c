/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pthreads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 12:20:23 by eabdelha          #+#    #+#             */
/*   Updated: 2022/03/26 12:28:48 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(t_info *info, size_t time_limit, size_t time_record)
{
	unsigned int	mini_sleep;

	usleep((time_limit - (time_limit * 0.05)) * TO_USEC);
	mini_sleep = 500;
	while ((get_time(info) - time_record) < time_limit)
	{
		usleep(mini_sleep);
		if (mini_sleep > 100)
			mini_sleep /= 2;
	}
}

void	eat_stat(t_info *info, int index)
{
	pthread_mutex_lock(&info->mutex_fork[index - 1]);
	print_message(info, index, TAKE_FORK, 0);
	pthread_mutex_lock(&info->mutex_fork[(index) % info->philo_nbr]);
	print_message(info, index, TAKE_FORK, 0);
	change_tt_die_record(info, index - 1);
	info->tt_eat_record[index - 1] = get_time(info);
	(info->had_eat[index - 1])++;
	print_message(info, index, EAT_STAT, 0);
	pthread_mutex_lock(&info->mutex_is_eating);
	info->is_eating[index - 1] = 1;
	pthread_mutex_unlock(&info->mutex_is_eating);
	ft_usleep(info, info->time.tt_eat, info->tt_eat_record[index - 1]);
	pthread_mutex_unlock(&info->mutex_fork[index - 1]);
	pthread_mutex_unlock(&info->mutex_fork[(index) % info->philo_nbr]);
	pthread_mutex_lock(&info->mutex_is_eating);
	info->is_eating[index - 1] = 0;
	pthread_mutex_unlock(&info->mutex_is_eating);
}

void	*philo_cycle(void *info_ptr)
{
	t_info		*info;
	static int	philo_index;
	int			index;

	info = (t_info *)info_ptr;
	index = philo_index + 1;
	philo_index++;
	change_tt_die_record(info, index - 1);
	if (!(index % 2))
		usleep(100);
	if (info->philo_nbr == 1)
		return (print_message(info, index, THINK_STAT, 0), NULL);
	while (check_sim_over(info) && info->dead_philo != -1)
	{
		if (print_message(info, index, THINK_STAT, 0))
			break ;
		eat_stat(info, index);
		info->tt_slp_record[index - 1] = get_time(info);
		if (print_message(info, index, SLEEP_STAT, 0))
			break ;
		ft_usleep(info, info->time.tt_sleep, info->tt_slp_record[index - 1]);
	}
	return (NULL);
}

int	init(t_info *info)
{
	int	i;

	info->philo = (pthread_t *)allocate(sizeof(pthread_t), info->philo_nbr, 0);
	info->mutex_fork = (pthread_mutex_t *)allocate(sizeof(pthread_mutex_t), \
			info->philo_nbr, 0);
	info->tt_die_record = (size_t *)allocate(sizeof(long), info->philo_nbr, 0);
	info->tt_eat_record = (size_t *)allocate(sizeof(long), info->philo_nbr, 0);
	info->tt_slp_record = (size_t *)allocate(sizeof(long), info->philo_nbr, 0);
	info->had_eat = (unsigned int *)allocate(sizeof(int), info->philo_nbr, 0);
	info->is_eating = (bool *)allocate(sizeof(bool), info->philo_nbr, 0);
	if (!info->philo || !info->mutex_fork || !info->tt_die_record
		|| !info->tt_eat_record || !info->tt_slp_record || !info->is_eating
		|| !info->had_eat)
		return (1);
	i = -1;
	while ((unsigned int)++i < info->philo_nbr)
		pthread_mutex_init(&info->mutex_fork[i], NULL);
	pthread_mutex_init(&info->mutex_dead, NULL);
	pthread_mutex_init(&info->mutex_is_eating, NULL);
	pthread_mutex_init(&info->mutex_print_msg, NULL);
	return (0);
}

int	create_pthreads(t_info *info)
{
	int	i;

	if (init(info))
		return (1);
	i = -1;
	while ((unsigned int)++i < info->philo_nbr)
	{
		if (pthread_create(&info->philo[i], NULL, philo_cycle, (void *)info))
			return (1);
	}
	check_dead_stat(info);
	i = -1;
	while ((unsigned int)++i < info->philo_nbr)
		pthread_join(info->philo[i], NULL);
	i = -1;
	while ((unsigned int)++i < info->philo_nbr)
		pthread_mutex_destroy(&info->mutex_fork[i]);
	pthread_mutex_destroy(&info->mutex_dead);
	pthread_mutex_destroy(&info->mutex_is_eating);
	pthread_mutex_destroy(&info->mutex_print_msg);
	return (0);
}
