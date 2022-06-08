/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:13:53 by youskim           #+#    #+#             */
/*   Updated: 2022/06/03 12:16:53 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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
	pthread_mutex_destroy (all->write);
	free (all->fork);
	free (all);
}

void	death_check(t_all *all)
{
	int		i;
	double	now;

	while (all->death == 0)
	{
		i = -1;
		check_time (&now);
		while (++i < all->philo_num)
		{
			if ((int)((now - all->philo[i].life_time) * 1000) > all->life)
			{
				printf_with_time (all->start, i + 1, "diead\n", all);
				all->death = 1;
				break ;
			}
		}
		if (all->death != 0 || (all->eat_check == all->eat_num && all->eat_num != 0))c
		{
			end_philo (all);
			break ;
		}
		usleep (50);
	}
}

void	*check_philo(void *data)
{
	t_all	*all;
	int		n;

	all = (t_all *)data;
	n = all->num;
	if (all->eat_num != 0)
	{
		while (all->death == 0 && all->philo[n].eat_num < all->eat_num)
		{
			pthread_mutex_lock (&(all->fork[all->philo[n].right]));
			printf_with_time (all->start, n + 1, "has taken a fork\n", all);
			pthread_mutex_lock (&(all->fork[all->philo[n].left]));
			printf_with_time (all->start, n + 1, "has taken a fork\n", all);
			printf_with_time (all->start, n + 1, "is eating\n", all);
			ft_usleep (all->philo[n].eat_time);
			check_time (&(all->philo[n].life_time));
			all->philo[n].eat_num += 1;
			pthread_mutex_unlock (&(all->fork[all->philo[n].right]));
			pthread_mutex_unlock (&(all->fork[all->philo[n].left]));
			printf_with_time (all->start, n + 1, "is sleeping\n", all);
			ft_usleep (all->philo[n].sleep_time);
			printf_with_time (all->start, n + 1, "is thinking\n", all);
			if (all->philo[n].eat_num == all->eat_num)
			{
				all->eat_check += 1;
				break ;
			}
		}
	}
	else
	{
		while (all->death == 0)
		{
			pthread_mutex_lock (&(all->fork[all->philo[n].right]));
			printf_with_time (all->start, n + 1, "has taken a fork\n", all);
			pthread_mutex_lock (&(all->fork[all->philo[n].left]));
			printf_with_time (all->start, n + 1, "has taken a fork\n", all);
			printf_with_time (all->start, n + 1, "is eating\n", all);
			ft_usleep (all->philo[n].eat_time);
			check_time (&(all->philo[n].life_time));
			all->philo[n].eat_num += 1;
			pthread_mutex_unlock (&(all->fork[all->philo[n].right]));
			pthread_mutex_unlock (&(all->fork[all->philo[n].left]));
			printf_with_time (all->start, n + 1, "is sleeping\n", all);
			ft_usleep (all->philo[n].sleep_time);
			printf_with_time (all->start, n + 1, "is thinking\n", all);
		}
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_all			*all;
	pthread_mutex_t	mutex;
	int				i;

	if (argc < 5 || argc > 6)
		return (1);
	all = make_all (argc, argv);
	if (all == NULL)
		return (1);
	all->write = &mutex;
	if (pthread_mutex_init (all->write, NULL) == -1)
		return (error_free(all));
	i = -1;
	while (++i < all->philo_num)
	{
		all->num = i;
		if (pthread_create (&(all->philo[i].tid), NULL, \
			check_philo, (void *)all) != 0)
			return (error_free_thread (all, i));
		usleep (50);
	}
	death_check (all);
	return (0);
}