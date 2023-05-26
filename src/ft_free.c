/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezaei <mrezaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 19:02:03 by mrezaei           #+#    #+#             */
/*   Updated: 2023/05/26 20:48:35 by mrezaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

//===========================================================================//
//free mem and mutex				                                         //
//===========================================================================//
void	ft_cleanup(t_info *info)
{
	int	i;

	if (info->goal == 1)
		if (info->eat_time)
			free(info->eat_time);
	if (info->last_meal)
		free(info->last_meal);
	if (info->fork)
		free(info->fork);
	if (info->tid)
		free(info->tid);
	if (info->mutex)
		free(info->mutex);
	pthread_mutex_destroy(&info->stop);
	i = 0;
	while (i < info->philo_count)
	{
		pthread_mutex_destroy(&info->mutex[i]);
		i++;
	}
	return ;
}
