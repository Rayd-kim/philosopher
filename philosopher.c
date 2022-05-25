#include "philosopher.h"

t_all	*make_all(int argc, char *argv[])
{
	t_all	*ret;
	t_philo	*p;

	ret = (t_all *)malloc(sizeof(t_all));
	if (ret == 0)
		return (NULL);
	ret->num = ft_atoi(argv[1]);
	ret->pork = pork[ret->num];
	p = (t_philo *)malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (p == 0)
		return (NULL);
	if (make_philo(p, argc, argv) == 1)
		return (NULL);
	ret->philo = p;
	return (ret);
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

int	main(int argc, char *argv[])
{
	t_all	*all;

	if (argc < 5 || argc > 6)
		return (1);
	all = make_all (argc, argv);
	if (all == NULL)
		return (1);
	
	return (0);	
}