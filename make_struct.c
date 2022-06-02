/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:13:34 by youskim           #+#    #+#             */
/*   Updated: 2022/06/02 15:13:38 by youskim          ###   ########.fr       */
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
		pthread_mutex_init (&fork[i], NULL);
		i++;
	}
	return (fork);
}

int	make_philo(t_philo *p, int argc, char *argv[])
{
	int	i;
	int	arg[5];

	i = -1;
	while (++i < argc - 1)
		arg[i] = ft_atoi(argv[i + 1]);
	memset (p, 0, sizeof(t_philo) * arg[0]);
	i = -1;
	while (++i < arg[0])
	{
		p[i].num = i + 1;
		check_time (&p[i].life_time);
		p[i].eat_time = arg[2];
		p[i].sleep_time = arg[3];
		p[i].left = (i + 1) % arg[0];
		p[i].right = i;
		p[i].eat_num = 0;
	}
	return (0);
}

t_all	*make_all(int argc, char *argv[])
{
	t_all			*all;
	t_philo			*p;

	all = (t_all *)malloc(sizeof(t_all));
	if (all == 0)
		return (NULL);
	check_time (&all->start);
	all->philo_num = ft_atoi(argv[1]);
	all->life = ft_atoi(argv[2]);
	all->fork = make_fork(all);
	if (argc == 6)
		all->eat_num = ft_atoi (argv[5]);
	p = (t_philo *)malloc(sizeof(t_philo) * all->philo_num);
	if (p == 0)
		return (NULL);
	if (make_philo(p, argc, argv) == 1)
		return (NULL);
	all->philo = p;
	return (all);
}