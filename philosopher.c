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

void	check_time(double *time)
{
	struct timeval	now;

	gettimeofday (&now, NULL);
	*time = now.tv_sec + + now.tv_usec * 0.000001;
}

void	ft_usleep(int spend_time)
{
	double	now_time;
	double	after_time;
	double	temp;

	check_time(&now_time);
	check_time(&after_time);
	temp = spend_time * 0.001;
	while ((after_time - now_time) <= temp)
	{
		usleep (100);
		check_time(&after_time);
	}
}

void	*check_philo(void *data)
{
	t_all	*all;
	int		n;
	double	now;
	double	life_time;
	double	after;

	check_time (&life_time);
	check_time (&now);
	all = (t_all *)data;
	n = all->philo_num;
	while (all->philo[n].life > 0)
	{
	pthread_mutex_lock(all->mutex_fork);
	if (all->philo[n].num == 1)
	{
		if (all->fork[n] == 0 && all->fork[all->num - 1] == 0 && all->num > 1)
		{
			all->fork[n] = 1;
			all->fork[all->num - 1] = 1;
			check_time (&after);
			printf ("%d %d has taken a fork\n", (int)((after - now) * 1000), n + 1);
			pthread_mutex_unlock (all->mutex_fork);
			ft_usleep (all->philo[0].eat_time);
			pthread_mutex_lock(all->mutex_fork);
			all->fork[n] = 0;
			all->fork[all->num - 1] = 0;
			check_time (&after);
			printf ("%d %d eat the food\n", (int)((after - now) * 1000), n + 1);
			check_time (&life_time);
			pthread_mutex_unlock (all->mutex_fork);
			ft_usleep (all->philo[0].sleep_time);
			check_time (&after);
			printf ("%d %d is sleeping\n", (int)((after - now) * 1000), n + 1);
			usleep (50);
		}
		else
		{
			check_time (&after);
			if ( (int)((after - life_time) * 1000) > all->philo[n].life)
			{
				printf ("%d %d died\n", (int)((after - now) * 1000), n + 1);
				break ;
			}
			pthread_mutex_unlock (all->mutex_fork);
		}
		
	}
	else if (all->philo[n].num > 1)
	{
		if (all->fork[n] == 0 && all->fork[n - 1] == 0 && all->num > 1)
		{
			all->fork[n] = 1;
			all->fork[n - 1] = 1;
			check_time (&after);
			printf ("%d %d has taken a fork\n", (int)((after - now) * 1000), n + 1);
			pthread_mutex_unlock (all->mutex_fork);
			ft_usleep (all->philo[0].eat_time);
			pthread_mutex_lock(all->mutex_fork);
			all->fork[n] = 0;
			all->fork[n - 1] = 0;
			check_time (&after);
			printf ("%d %d eat the food\n", (int)((after - now) * 1000), n + 1);
			check_time (&life_time);
			pthread_mutex_unlock (all->mutex_fork);
			ft_usleep (all->philo[0].eat_time);
			check_time (&after);
			printf ("%d %d is sleeping\n", (int)((after - now) * 1000), n + 1);
			usleep (50);
		}
		else
		{
			check_time (&after);
			if ( (int)((after - life_time) * 1000) > all->philo[n].life)
			{
				printf ("%d %d died\n", (int)((after - now) * 1000), n + 1);
				break ;
			}
			pthread_mutex_unlock (all->mutex_fork);
		}
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