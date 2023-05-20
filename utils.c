/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezaei <mrezaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 12:23:00 by mrezaei           #+#    #+#             */
/*   Updated: 2023/05/20 14:19:38 by mrezaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(char const *str)
{
	unsigned int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

double	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	check_eat(t_param *param)
{
	int	i;

	i = 0;
	while (i < param->philo_count)
	{
		if (param->eat_time[i++] < param->eat_goal)
			return (-1);
	}
	return (1);
}
