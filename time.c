/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:13:57 by youskim           #+#    #+#             */
/*   Updated: 2022/07/05 22:04:25 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

double	check_time(void)
{
	struct timeval	now;
	double			ret;

	gettimeofday (&now, NULL);
	ret = now.tv_sec + now.tv_usec * 0.000001;
	return (ret);
}

void	ft_usleep(int spend_time)
{
	double	now_time;
	double	after_time;
	double	temp;

	now_time = check_time ();
	after_time = check_time ();
	temp = spend_time * 0.001;
	while ((after_time - now_time) <= temp)
	{
		usleep (250);
		after_time = check_time();
	}
}

void	printf_with_time(double start, int philo, char *str, t_all *all)
{
	double	now;

	now = check_time ();
	pthread_mutex_lock (&(all->write));
	printf ("%d %d %s", (int)((now - start) * 1000), philo, str);
	pthread_mutex_unlock (&(all->write));
}

void	printf_died(double start, int philo, char *str)
{
	double	now;

	now = check_time ();
	printf ("%d %d %s", (int)((now - start) * 1000), philo, str);
}
