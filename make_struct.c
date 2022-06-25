/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:13:34 by youskim           #+#    #+#             */
/*   Updated: 2022/06/25 20:01:37 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

pthread_mutex_t	*make_fork(t_all *all)
{
	pthread_mutex_t	*fork;
	int				i;

	fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * all->philo_num);
	if (fork == 0)
		return (NULL);
	i = 0;
	while (i < all->philo_num)
	{
		if (pthread_mutex_init (&fork[i], NULL) == -1)
		{
			while (--i > 0)
				pthread_mutex_destroy (&fork[i]);
			free (fork);
			return (NULL);
		}
		i++;
	}
	return (fork);
}

int	make_philo(t_philo *p, int argc, char *argv[], t_all *all)
{
	int	i;
	int	arg[5];

	i = -1;
	while (++i < argc - 1)
		arg[i] = ft_atoi(argv[i + 1]);
	if (memset (p, 0, sizeof(t_philo) * arg[0]) == NULL)
		return (1);
	i = -1;
	while (++i < arg[0])
	{
		p[i].num = i + 1;
		pthread_mutex_lock (&(all->eating));
		p[i].life_time = check_time ();
		pthread_mutex_unlock (&(all->eating));
		p[i].eat_time = arg[2];
		p[i].sleep_time = arg[3];
		p[i].left = (i + 1) % arg[0];
		p[i].right = i;
		p[i].eat_num = 0;
		p[i].all = all;
	}
	return (0);
}

int	start_mutex(t_all *all)
{
	if (pthread_mutex_init (&(all->write), NULL) == -1)
		return (error_free(all));
	if (pthread_mutex_init (&(all->eating), NULL) == -1)
		return (error_free(all));
	return (0);
}

int	check_argv(int argc, char *argv[])
{
	int	i;

	i = 0;
	while (i < argc - 1)
	{
		if (ft_atoi(argv[i + 1]) <= 0)
			return (1);
		i++;
	}
	return (0);
}

int	make_all(t_all *all, int argc, char *argv[])
{
	t_philo			*p;

	if (check_argv(argc, argv) == 1)
		return (-1);
	if (memset (all, 0, sizeof(t_all)) == NULL)
		return (-1);
	all->start = check_time ();
	all->philo_num = ft_atoi(argv[1]);
	all->life = ft_atoi(argv[2]);
	if (argc == 6)
		all->eat_num = ft_atoi (argv[5]);
	p = (t_philo *)malloc(sizeof(t_philo) * all->philo_num);
	if (p == 0)
		return (-1);
	if (make_philo(p, argc, argv, all) == 1)
		return (-1);
	all->philo = p;
	all->fork = make_fork(all);
	if (all->fork == NULL)
	{
		free (all->philo);
		return (-1);
	}
	return (0);
}
