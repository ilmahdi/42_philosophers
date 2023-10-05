/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 09:29:17 by eabdelha          #+#    #+#             */
/*   Updated: 2022/03/26 12:45:14 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_res(t_info *info)
{
	free(info->philo);
	free(info->mutex_fork);
	free(info->tt_die_record);
	free(info->tt_eat_record);
	free(info->tt_slp_record);
	free(info->is_eating);
	free(info->had_eat);
}

void	parse_args_time(t_info *info, char **av)
{
	info->time.tt_die = (size_t)ft_atoi(av[2]);
	info->time.tt_eat = (size_t)ft_atoi(av[3]);
	info->time.tt_sleep = (size_t)ft_atoi(av[4]);
	info->time.sim_over_nbr = -1;
	if (av[5])
		info->time.sim_over_nbr = ft_atoi(av[5]);
}

int	main(int ac, char **av)
{
	t_info	info;

	info = (t_info){};
	if (ac != 5 && ac != 6)
		return (write(2, "invalid number of arguments\n", 28), 1);
	parse_args_time(&info, av);
	info.philo_nbr = ft_atoi(av[1]);
	if (!info.philo_nbr || info.philo_nbr > 200)
		return (write(2, "invalid number of Philosophers\n", 31), 1);
	if (create_pthreads(&info))
		return (free_res(&info), 1);
	free_res(&info);
	return (0);
}
