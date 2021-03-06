/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:13:49 by youskim           #+#    #+#             */
/*   Updated: 2022/06/26 01:34:36 by youskim          ###   ########.fr       */
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

int	error_free_thread(t_all *all, int i)
{
	while (i > 0)
	{
		pthread_detach (all->philo[i].tid);
		i++;
	}
	free (all->philo);
	i = -1;
	while (++i < all->philo_num)
		pthread_mutex_destroy (&all->fork[i]);
	pthread_mutex_destroy (&(all->write));
	pthread_mutex_destroy (&(all->eating));
	free (all->fork);
	return (1);
}

int	error_free(t_all *all)
{
	int	i;

	free (all->philo);
	i = -1;
	while (++i < all->philo_num)
		pthread_mutex_destroy (&all->fork[i]);
	free (all->fork);
	return (1);
}

void	end_philo(t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->philo_num)
		pthread_detach (all->philo[i].tid);
	free (all->philo);
	i = -1;
	while (++i < all->philo_num)
		pthread_mutex_destroy (&all->fork[i]);
	pthread_mutex_destroy (&(all->write));
	pthread_mutex_destroy (&(all->eating));
	free (all->fork);
}
