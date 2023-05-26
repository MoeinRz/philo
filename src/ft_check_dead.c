/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_dead.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezaei <mrezaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:53:42 by mrezaei           #+#    #+#             */
/*   Updated: 2023/05/26 20:53:39 by mrezaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

//===========================================================================//
//the main lifecycle of each philo                                          //
//===========================================================================//
void	update_last_meal(t_info *info, double init)
{
	int	i;
	int	j;

	i = -1;
	while (++i < info->philo_count)
	{
		info->last_meal[i] += 1;
		if (info->last_meal[i] >= info->time_die)
		{
			info->is_dead = 0;
			printf(RED"%.f ms philo[%d] died\n"RESET, get_time() - init, i + 1);
			j = info->time_die;
			while (j >= 0)
			{
				pthread_mutex_unlock(&info->mutex[j]);
				j--;
			}
			break ;
		}
	}
}

//===========================================================================//
//the main lifecycle of each philo                                          //
//===========================================================================//
void	*ft_check_life(void *arg)
{
	t_info	*info;
	double	start;
	double	init;

	info = (t_info *)arg;
	init = get_time();
	usleep(2000 * (info->philo_count - 1));
	while (info->is_dead)
	{
		start = get_time();
		while ((get_time() - start) < 1)
			usleep(1);
		if (info->goal == 1 && check_eat(info) == 1)
		{
			info->is_dead = 0;
			break ;
		}
		update_last_meal(info, init);
	}
	return (NULL);
}

//===========================================================================//
//check if all philosophers have reached their eat goal                      //
//===========================================================================//
int	check_eat(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->philo_count)
	{
		if (info->eat_time[i++] < info->eat_goal)
			return (-1);
	}
	return (1);
}
