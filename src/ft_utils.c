/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezaei <mrezaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 12:23:00 by mrezaei           #+#    #+#             */
/*   Updated: 2023/05/26 18:56:18 by mrezaei          ###   ########.fr       */
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
