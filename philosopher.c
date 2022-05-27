#include "philosopher.h"

int	make_philo (t_philo *p, int argc, char *argv[]);

int	*make_fork(t_all *all)
{
	int	*fork;

	fork = (int *)malloc(sizeof(int) * all->num);
	if (fork == 0)
		return (NULL);
	memset (fork, 0, sizeof(int) * all->num);
	return (fork);
}

t_all	*make_all(int argc, char *argv[])
{
	t_all			*all;
	t_philo			*p;
	//pthread_mutex_t	mutex;

	all = (t_all *)malloc(sizeof(t_all));
	if (all == 0)
		return (NULL);
	gettimeofday (&all->start, NULL);
	all->num = ft_atoi(argv[1]);
	all->fork = make_fork(all);
	//all->mutex_fork = &mutex;
	p = (t_philo *)malloc(sizeof(t_philo) * all->num);
	if (p == 0)
		return (NULL);
	if (make_philo(p, argc, argv) == 1)
		return (NULL);
	all->philo = p;
	return (all);
}

int	make_philo (t_philo *p, int argc, char *argv[])
{
	int	i;
	int	*arg;

	arg = (int *)malloc(sizeof(int) * (argc - 1));
	if (arg == 0)
		return (1);
	i = -1;
	while (++i < argc - 1)
		arg[i] = ft_atoi(argv[i + 1]);
	memset (p, 0, sizeof(t_philo) * arg[0]);
	i = -1;
	while (++i < arg[0])
	{
		p[i].num = i + 1;
		p[i].life = arg[1];
		p[i].eat_time = arg[2];
		p[i].sleep_time = arg[3];
		if (argc == 6)
			p[i].eat_num = arg[4];
		else
			p[i].eat_num = -1;
	}
	free (arg);
	return (0);
}


void	*check_philo(void *data)
{
	t_all	*all;
	int		n;

	all = (t_all *)data;
	pthread_mutex_lock(all->mutex_fork);
	n = all->philo_num;
	while (all->philo[n].life > 0)
	{
	if (all->philo[n].num == 1)
	{
		if (all->fork[n] == 0 && all->fork[all->num - 1] == 0 && all->num > 1)
		{
			all->fork[n] = 1;
			all->fork[all->num - 1] = 1;
			printf ("%d has taken a fork\n", n + 1);
			//pthread_mutex_unlock (all->mutex_fork);
			usleep (all->philo[n].eat_time * 1000);
			printf ("%d eat the food\n", n + 1);
		}
		else if (all->fork[n] == 1 && all->fork[all->num - 1] == 1 && all->num > 1)
		{
			all->fork[n] = 0;
			all->fork[all->num - 1] = 0;
			//pthread_mutex_unlock (all->mutex_fork);
			//printf ("%d eat the food\n", n + 1);
		}
		//else
		//	printf ("%d is thinking\n", n + 1);
		//pthread_mutex_unlock (all->mutex_fork);
	}
	else if (all->philo[n].num > 1)
	{
		if (all->fork[n] == 0 && all->fork[n - 1] == 0 && all->num > 1)
		{
			all->fork[n] = 1;
			all->fork[n - 1] = 1;
			printf ("%d has taken a fork\n", n + 1);
			pthread_mutex_unlock (all->mutex_fork);
			usleep (all->philo[n].eat_time * 1000);
			printf ("%d eat the food\n", n + 1);
		}
		else if (all->fork[n] == 1 && all->fork[n - 1] == 1 && all->num > 1)
		{
			all->fork[n] = 0;
			all->fork[n - 1] = 0;
			pthread_mutex_unlock (all->mutex_fork);
			//printf ("%d eat the food\n", n + 1);
		}
		//else
		//	printf ("%d is thinking\n", n + 1);
		//pthread_mutex_unlock (all->mutex_fork);
	}
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_all	*all;
	int		status;
	pthread_mutex_t	mutex;

	if (argc < 5 || argc > 6)
		return (1);
	all = make_all (argc, argv);
	if (all == NULL)
		return (1);
	all->mutex_fork = &mutex;
	pthread_mutex_init (all->mutex_fork, NULL);
	for (int i = 0; i < all->num; i++)
	{
		all->philo_num = i;
		pthread_create (&all->philo[i].tid, NULL, check_philo ,(void *)all);
		usleep(50);
	}
	for (int i = 0; i < all->num; i++)
		pthread_join (all->philo[i].tid, (void **)&status);
	return (0);	
}