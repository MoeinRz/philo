/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezaei <mrezaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 12:23:00 by mrezaei           #+#    #+#             */
/*   Updated: 2023/05/26 18:37:15 by mrezaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

//===========================================================================//
//find the len of str                                                        //
//===========================================================================//
size_t	ft_strlen(char const *str)
{
	unsigned int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

//===========================================================================//
//get time and return ms                                                     //
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
