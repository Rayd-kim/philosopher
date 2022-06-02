/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:13:57 by youskim           #+#    #+#             */
/*   Updated: 2022/06/02 15:14:05 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	check_time(double *time)
{
	struct timeval	now;

	gettimeofday (&now, NULL);
	*time = now.tv_sec + now.tv_usec * 0.000001;
}

void	ft_usleep(int spend_time)
{
	double	now_time;
	double	after_time;
	double	temp;

	check_time (&now_time);
	check_time (&after_time);
	temp = spend_time * 0.001;
	while ((after_time - now_time) <= temp)
	{
		usleep (10);
		check_time(&after_time);
	}
}

void	printf_with_time(double start, int philo, char *str, t_all *all)
{
	double	now;

	check_time (&now);
	pthread_mutex_lock (all->write);
	printf ("%d %d %s", (int)((now - start) * 1000), philo, str);
	pthread_mutex_unlock (all->write);
}
