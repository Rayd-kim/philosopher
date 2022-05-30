#include "philosopher.h"

int	make_philo (t_philo *p, int argc, char *argv[]);

pthread_mutex_t	*make_fork(t_all *all)
{
	pthread_mutex_t	*fork;
	int				i;
	int				*fork_num;

	fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * all->philo_num);
	if (fork == 0)
		return (NULL);
	fork_num = (int *)malloc(sizeof(int) * all->philo_num);
	if (fork_num == 0)
		return (NULL);
	memset (fork_num, 0, sizeof(int) * all->philo_num);
	all->fork_num = fork_num;
	i = 0;
	while (i < all->philo_num)
	{
		pthread_mutex_init (&fork[i], NULL);
		i++;
	}
	return (fork);
}

t_all	*make_all(int argc, char *argv[])
{
	t_all			*all;
	t_philo			*p;

	all = (t_all *)malloc(sizeof(t_all));
	if (all == 0)
		return (NULL);
	gettimeofday (&all->start, NULL);
	all->philo_num = ft_atoi(argv[1]);
	all->fork = make_fork(all);
	p = (t_philo *)malloc(sizeof(t_philo) * all->philo_num);
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
	int	arg[5];

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
		p[i].left = (i + 1) % arg[0];
		p[i].right = i;
		if (argc == 6)
			p[i].eat_num = arg[4];
		else
			p[i].eat_num = 0;
	}
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
		usleep (50);
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
	n = all->num;
	while (all->philo[n].life > 0)
	{
		while (all->fork_num[all->philo[n].right] == 1)
			usleep (10);
		pthread_mutex_lock(&all->fork[all->philo[n].left]);
		all->fork_num[all->philo[n].left] = 1;
		check_time (&after);
		printf ("%d %d has taken a fork\n", (int)((after - now) * 1000), n + 1);
		pthread_mutex_lock(&all->fork[all->philo[n].right]);
		all->fork_num[all->philo[n].right] = 1;
		check_time (&after);
		printf ("%d %d has taken a fork\n", (int)((after - now) * 1000), n + 1);
		check_time (&after);
		printf ("%d %d is eating\n", (int)((after - now) * 1000), n + 1);
		ft_usleep (all->philo[n].eat_time);
		pthread_mutex_unlock(&all->fork[all->philo[n].left]);
		pthread_mutex_unlock(&all->fork[all->philo[n].right]);
		all->fork_num[all->philo[n].left] = 0;
		all->fork_num[all->philo[n].right] = 0;
		check_time (&after);
		printf ("%d %d is sleeping\n",  (int)((after - now) * 1000), n + 1);
		ft_usleep (all->philo[n].sleep_time);
		check_time (&after);
		printf ("%d %d is thinking\n" , (int)((after - now) * 1000), n + 1);
	}
	return (0);
}

/*
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
	pthread_mutex_lock(&all->fork[all->num]);
	if (all->philo[n].num == 1)
	{
		if (all->fork[n] == 0 && all->fork[all->num - 1] == 0 && all->num > 1)
		{
			all->fork[n] = 1;
			all->fork[all->num - 1] = 1;
			check_time (&after);
			printf ("%d %d has taken a fork\n", (int)((after - now) * 1000), n + 1);
			printf ("%d %d eat the food\n", (int)((after - now) * 1000), n + 1);
			pthread_mutex_unlock (all->mutex_fork);
			ft_usleep (all->philo[0].eat_time);
			pthread_mutex_lock(all->mutex_fork);
			all->fork[n] = 0;
			all->fork[all->num - 1] = 0;
			check_time (&after);
			//printf ("%d %d eat the food\n", (int)((after - now) * 1000), n + 1);
			check_time (&life_time);
			printf ("%d %d is sleeping\n", (int)((after - now) * 1000), n + 1);
			pthread_mutex_unlock (all->mutex_fork);
			ft_usleep (all->philo[0].sleep_time);
			check_time (&after);
			//printf ("%d %d is sleeping\n", (int)((after - now) * 1000), n + 1);
			usleep (50);
		}
		else
		{
			check_time (&after);
			if ( (int)((after - life_time) * 1000) > all->philo[n].life)
			{
				printf ("%d %d died\n", (int)((after - life_time) * 1000), n + 1);
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
			printf ("%d %d eat the food\n", (int)((after - now) * 1000), n + 1);
			pthread_mutex_unlock (all->mutex_fork);
			ft_usleep (all->philo[0].eat_time);
			pthread_mutex_lock(all->mutex_fork);
			all->fork[n] = 0;
			all->fork[n - 1] = 0;
			check_time (&after);
			//printf ("%d %d eat the food\n", (int)((after - now) * 1000), n + 1);
			check_time (&life_time);
			printf ("%d %d is sleeping\n", (int)((after - now) * 1000), n + 1);
			pthread_mutex_unlock (all->mutex_fork);
			ft_usleep (all->philo[0].eat_time);
			check_time (&after);
			//printf ("%d %d is sleeping\n", (int)((after - now) * 1000), n + 1);
			usleep (50);
		}
		else
		{
			check_time (&after);
			if ( (int)((after - life_time) * 1000) > all->philo[n].life)
			{
				printf ("%d %d died\n", (int)((after - life_time) * 1000), n + 1);
				break ;
			}
			pthread_mutex_unlock (all->mutex_fork);
		}
	}
	}
	return (0);
}
*/

int	main(int argc, char *argv[])
{
	t_all	*all;
	int		status;

	if (argc < 5 || argc > 6)
		return (1);
	all = make_all (argc, argv);
	if (all == NULL)
		return (1);
	for (int i = 0; i < all->philo_num; i++)
	{
		all->num = i;
		pthread_create (&all->philo[i].tid, NULL, check_philo ,(void *)all);
		usleep(50);
	}
	
	for (int i = 0; i < all->philo_num; i++)
		pthread_join (all->philo[i].tid, (void **)&status);
		
	return (0);	
}