/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezaei <mrezaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 17:24:57 by mrezaei           #+#    #+#             */
/*   Updated: 2023/05/26 15:09:09 by mrezaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

//===========================================================================//
//check it is digit or not                                                   //
//===========================================================================//
int	ft_isnumber(int a)
{
	if (a <= '9' && a >= '0')
		return (a);
	else
		return (0);
}

//===========================================================================//
//find the space or tab                                                      //
//===========================================================================//
int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || \
	c == '\f' || c == '\r');
}

//===========================================================================//
//check it is number or not and atoi it                                      //
//===========================================================================//
int	ft_is_pos_digit(char *str)
{
	while (*str && ft_isspace(*str))
	{
		str++;
	}
	if (*str == '-')
		return (0);
	if (*str == '+')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (!ft_isnumber(*str))
			return (0);
		str++;
	}
	return (1);
}

//===========================================================================//
//ascii to integer function                                                  //
//===========================================================================//
int	ft_atoi(const char *str)
{
	unsigned int	i;
	long			num;
	long			sign;

	i = 0;
	num = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
	i++;
	while (str[i] <= '9' && str[i] >= '0' && str[i] != '\0')
	{
		num = num * 10;
		num = num + str[i] - '0';
		i++;
	}
	return (num * sign);
}

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
	info->six = 0;
	if (argc == 6)
	{
		info->six = 1;
		info->eat_goal = ft_atoi(argv[5]);
	}
	return (0);
}
