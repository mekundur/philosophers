/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekundur <mekundur@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 20:02:19 by mekundur          #+#    #+#             */
/*   Updated: 2025/02/09 20:28:26 by mekundur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	limit_check(char **arr)
{
	int	num;
	int	i;

	num = 0;
	while (arr[num])
	{
		i = 0;
		if (arr[num][i] == '-' || arr[num][i] == '+')
		{
			if (arr[num][++i] == '0')
				return (1);
		}
		else if (arr[num][i] != '0' && ft_atoi(arr[num]) == 0)
			return (0);
		num++;
	}
	return (1);
}

static int	minusplus_check(char **arr)
{
	int	num;
	int	i;

	i = 0;
	num = 0;
	while (arr[num])
	{
		if (arr[num][i] == '-')
			return (0);
		i = 0;
		if (arr[num][i] == '+' ||
			(arr[num][i] >= '0' && arr[num][i] <= '9'))
		{
			i++;
			while (arr[num][i])
			{
				if (!(arr[num][i] >= '0' && arr[num][i] <= '9'))
					return (0);
				i++;
			}
		}
		num++;
	}
	return (1);
}

bool	input_check(char **argv)
{
	if (argv[5] && ft_atoi(argv[5]) == 0)
		return (0);
	if (!minusplus_check(argv))
		return (0);
	if (!limit_check(argv))
		return (-1);
	return (1);
}
