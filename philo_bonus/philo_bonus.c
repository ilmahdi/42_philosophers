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

#include "philo_bonus.h"

void	parse_args_time(t_info *info, char **av)
{
	info->time.tt_die = (size_t)ft_atoi(av[2]);
	info->time.tt_eat = (size_t)ft_atoi(av[3]);
	info->time.tt_sleep = (size_t)ft_atoi(av[4]);
	info->time.sim_over_nbr = -1;
	if (av[5])
		info->time.sim_over_nbr = ft_atoi(av[5]);
}

int	init(t_info *info)
{
	mode_t	sem_perm;

	sem_unlink("SEM_FORKS");
	sem_unlink("SEM_PRINT_MSG");
	sem_perm = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	info->sem_forks = sem_open("SEM_FORKS", O_CREAT, sem_perm, info->philo_nbr);
	if (info->sem_forks == SEM_FAILED)
		return (1);
	info->sem_print_msg = sem_open("SEM_PRINT_MSG", O_CREAT, sem_perm, 1);
	if (info->sem_print_msg == SEM_FAILED)
		return (1);
	info->pid_child = (pid_t *)malloc(sizeof(pid_t) * info->philo_nbr);
	if (!info->pid_child)
		return (1);
	return (0);
}

int	create_process(t_info *info)
{
	int		i;
	int		status;

	if (init(info))
		return (1);
	i = -1;
	info->tt_die_record = get_time(info);
	while ((unsigned int)++i < info->philo_nbr)
	{
		info->pid_child[i] = fork();
		if (info->pid_child[i] == -1)
		{
			info->philo_nbr = i + 1;
			kill_process(info);
			return (1);
		}
		if (!info->pid_child[i])
		{
			info->index = i + 1;
			child_process(info);
		}
	}
	waitpid(-1, &status, 0);
	kill_process(info);
	return (0);
}

int	main(int ac, char **av)
{
	t_info	info;
	char	main_return;

	info = (t_info){};
	main_return = 0;
	if (ac != 5 && ac != 6)
		return (write(2, "invalid number of arguments\n", 28), 1);
	parse_args_time(&info, av);
	info.philo_nbr = ft_atoi(av[1]);
	if (!info.philo_nbr || info.philo_nbr > 200)
		return (write(2, "invalid number of Philosophers\n", 31), 1);
	if (create_process(&info))
		main_return = 1;
	sem_close(info.sem_forks);
	sem_close(info.sem_print_msg);
	sem_unlink("SEM_FORKS");
	sem_unlink("SEM_PRINT_MSG");
	free(info.pid_child);
	return (0);
}
