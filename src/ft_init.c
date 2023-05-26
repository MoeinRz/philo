/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezaei <mrezaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 17:24:57 by mrezaei           #+#    #+#             */
/*   Updated: 2023/05/26 20:58:37 by mrezaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

//===========================================================================//
//initialize the data struct based on argv                                   //
//===========================================================================//
int	ft_init(int argc, char **argv, t_info *info)
{
	if (!ft_is_pos_digit(argv[1]) || !ft_is_pos_digit(argv[2])
		|| !ft_is_pos_digit(argv[3]) || !ft_is_pos_digit(argv[4]))
		return (-1);
	if (argc == 6 && !ft_is_pos_digit(argv[5]))
		return (-1);
	info->philo_count = ft_atoi(argv[1]);
	info->time_die = ft_atoi(argv[2]);
	info->time_eat = ft_atoi(argv[3]);
	info->time_sleep = ft_atoi(argv[4]);
	info->goal = 0;
	if (argc == 6)
	{
		info->goal = 1;
		info->eat_goal = ft_atoi(argv[5]);
	}
	return (0);
}

//===========================================================================//
//indexing the forks				                                         //
//===========================================================================//
void	ft_fork_index(t_info *info, t_each *each)
{
	pthread_mutex_lock(&info->stop);
	each->id = info->id;
	info->last_meal[each->id - 1] = 0;
	if (each->id == 1)
		each->left = 0;
	else
		each->left = each->id - 1;
	if (each->id == info->philo_count)
		each->right = 0;
	else
		each->right = each->id;
	if (each->left == each->right)
	{
		pthread_mutex_unlock(&info->stop);
		while (info->is_dead)
		{
		}
	}
	each->start = get_time();
	pthread_mutex_unlock(&info->stop);
	usleep((1 + info->philo_count - each->id) * 1000);
	return ;
}

//===========================================================================//
//get time and return time in ms 				                             //
//===========================================================================//
long	get_time(void)
{
	struct timeval	time;
	int				tmp;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	tmp = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (tmp);
}
