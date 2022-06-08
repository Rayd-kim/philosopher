/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:13:53 by youskim           #+#    #+#             */
/*   Updated: 2022/06/03 13:24:32 by youskim          ###   ########.fr       */
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
	pthread_mutex_destroy (&(all->write));
	free (all->fork);
	free (all);
}

int	eat_check(t_all *all)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (i < all->philo_num && all->eat_num > 0)
	{
		if (all->philo[i].eat_num >= all->eat_num)
			check ++;
		i++;
	}
	if (check == all->philo_num)
		return (1);
	else
		return (0);
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
				pthread_mutex_lock (&(all->write));
				printf_died(all->start, i + 1, "died\n");
				all->death = 1;
				break ;
			}
		}
		if (all->death != 0 || eat_check(all) == 1)
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
	return (0);
}

int	main(int argc, char *argv[])
{
	t_all			*all;
	int				i;

	if (argc < 5 || argc > 6)
		return (1);
	all = make_all (argc, argv);
	if (all == NULL)
		return (1);
	if (pthread_mutex_init (&(all->write), NULL) == -1)
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
