/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:13:53 by youskim           #+#    #+#             */
/*   Updated: 2022/06/26 23:41:15 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	philo_do(t_philo *philo)
{
	pthread_mutex_lock (&(philo->all->fork[philo->right]));
	printf_with_time (philo->all->start, philo->num, "has taken a fork\n", \
	philo->all);
	pthread_mutex_lock (&(philo->all->fork[philo->left]));
	printf_with_time (philo->all->start, philo->num, "has taken a fork\n", \
	philo->all);
	printf_with_time (philo->all->start, philo->num, "is eating\n", philo->all);
	// pthread_mutex_lock (&(philo->all->eating));
	// philo->eat_num += 1;
	// if (philo->eat_num == philo->all->eat_num)
	// 	philo->all->eat_check += 1;
	// if (philo->all->eat_check == philo->all->philo_num)
	// 	end_philo(philo->all);
	// pthread_mutex_unlock (&(philo->all->eating));
	ft_usleep (philo->eat_time);
	pthread_mutex_lock (&(philo->all->eating));
	philo->life_time = check_time ();
	philo->eat_num += 1;
	if (philo->eat_num == philo->all->eat_num)
		philo->all->eat_check += 1;
	if (philo->all->eat_check == philo->all->philo_num)
		end_philo(philo->all);
	pthread_mutex_unlock (&(philo->all->eating));
	pthread_mutex_unlock (&(philo->all->fork[philo->right]));
	pthread_mutex_unlock (&(philo->all->fork[philo->left]));
}

void	*check_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->num % 2 == 0)
		usleep (10000);
	pthread_mutex_lock (&(philo->all->eating));
	while (philo->all->death == 0)
	{
		pthread_mutex_unlock (&(philo->all->eating));
		philo_do (philo);
		printf_with_time (philo->all->start, philo->num, \
		"is sleeping\n", philo->all);
		ft_usleep (philo->sleep_time);
		printf_with_time (philo->all->start, philo->num, \
		"is thinking\n", philo->all);
		pthread_mutex_lock (&(philo->all->eating));
	}
	return (0);
}

void	*death_check(void *data)
{
	t_all	*all;
	int		i;

	all = (t_all *)data;
	while (all->eat_check != all->philo_num || all->eat_num == 0)
	{
		i = -1;
		while (++i < all->philo_num)
		{
			pthread_mutex_lock (&(all->eating));
			if ((int)((check_time () - all->philo[i].life_time) * 1000) \
				> all->life)
			{
				pthread_mutex_lock (&(all->write));
				printf_died(all->start, i + 1, "died\n");
				all->death = 1;
				end_philo (all);
				return (0);
			}
			pthread_mutex_unlock (&(all->eating));
		}
	}
	return (0);
}

int	monitor(t_all *all)
{
	pthread_t	tid;

	if (pthread_create (&tid, NULL, death_check, (void *)all) != 0)
	{
		end_philo (all);
		return (1);
	}
	pthread_join (tid, NULL);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_all			all;
	int				i;

	if (argc < 5 || argc > 6)
		return (1);
	if (make_all (&all, argc, argv) == -1)
		return (1);
	if (start_mutex(&all) == 1)
		return (1);
	i = -1;
	while (++i < all.philo_num)
	{
		if (pthread_create (&(all.philo[i].tid), NULL, \
			check_philo, (void *)&all.philo[i]) != 0)
			return (error_free_thread (&all, i));
	}
	if (monitor (&all) != 0)
		return (1);
	return (0);
}
