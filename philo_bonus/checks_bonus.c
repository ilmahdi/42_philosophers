/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 12:20:38 by eabdelha          #+#    #+#             */
/*   Updated: 2022/03/26 12:23:36 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_sim_over(t_info *info)
{
	int	i;

	i = -1;
	if (info->time.sim_over_nbr == -1)
		return (1);
	while ((unsigned int)++i < info->philo_nbr)
	{
		if (info->had_eat < (unsigned int)info->time.sim_over_nbr)
			return (1);
	}
	info->dead_philo = -1;
	return (0);
}

void	check_dead_stat(t_info *info)
{
	int		i;
	size_t	time_ms;

	while (info->dead_philo != -1)
	{
		i = -1;
		while ((unsigned int)++i < info->philo_nbr && !usleep(1000))
		{
			if (info->is_eating)
				continue ;
			if ((get_time(info) - info->tt_die_record) > info->time.tt_die)
			{
				info->dead_philo = -1;
				sem_wait(info->sem_print_msg);
				time_ms = get_time(info);
				printf("%ld %d %s\n", time_ms, info->index, DEAD_STAT);
				break ;
			}
		}
	}
}
