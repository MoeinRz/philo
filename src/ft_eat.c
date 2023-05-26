/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezaei <mrezaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 19:59:53 by mrezaei           #+#    #+#             */
/*   Updated: 2023/05/26 20:57:35 by mrezaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

//===========================================================================//
//unlock forks with strategy                                                 //
//===========================================================================//
void	unlok_mutex_fork(t_info *info, t_each each)
{
	if (each.state == 0)
	{
		pthread_mutex_unlock(&info->mutex[each.right]);
		pthread_mutex_unlock(&info->mutex[each.left]);
	}
	else if (each.state == 1)
	{
		pthread_mutex_unlock(&info->mutex[each.left]);
		pthread_mutex_unlock(&info->mutex[each.right]);
	}
	info->fork[each.right] = 0;
	info->fork[each.left] = 0;
	return ;
}

//===========================================================================//
//make free forks                                                            //
//===========================================================================//
void	free_fork(t_info *info, t_each each)
{
	if (each.id % 2 == 0)
	{
		each.state = 0;
		unlok_mutex_fork(info, each);
	}
	else
	{
		each.state = 1;
		unlok_mutex_fork(info, each);
	}
	return ;
}

//===========================================================================//
//the eating function                                                        //
//===========================================================================//
int	ft_eat(t_info *info, t_each each)
{
	double	start;

	each.state = 0;
	if (info->is_dead == 0)
	{	
		each.state = 0;
		unlok_mutex_fork(info, each);
		return (-1);
	}
	printf(GREEN"%.f ms philo[%d] is eating\n"RESET, \
			get_time() - each.start, each.id);
	info->last_meal[each.id - 1] = 0;
	start = get_time();
	while ((get_time() - start) <= info->time_eat)
	{
		if (info->is_dead == 0)
			break ;
		usleep(1000);
	}
	free_fork(info, each);
	info->eat_time[each.id - 1]++;
	return (1);
}
