/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:13:49 by youskim           #+#    #+#             */
/*   Updated: 2022/06/02 15:13:51 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	result_value(const char *str, int index, int sign)
{
	unsigned long long int	result;

	result = 0;
	while (str[index] >= '0' && str[index] <= '9')
	{
		result = result * 10 + str[index] - '0';
		index++;
	}
	if (result > 9223372036854775807 && sign == 1)
		return (-1);
	else if (result - 1 > 9223372036854775807 && sign == -1)
		return (0);
	else
		return (result * sign);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;
	int	pm_num;

	i = 0;
	sign = 1;
	pm_num = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		pm_num++;
		i++;
	}
	if (pm_num > 1)
		return (0);
	result = result_value(str, i, sign);
	return (result);
}

void	error_free (t_all *all)
{
	int	i;

	i = 0;
	while (i < all->philo_num)
	{
		pthread_detach (all->philo[i].tid);
		i++;
	}
	free (all->philo);
	i = 0;
	while (i < all->philo_num)
	{
		pthread_mutex_destroy (&all->fork[i]);
		i++;
	}
	pthread_mutex_destroy (all->write);
	free (all->fork);
	free (all);
}