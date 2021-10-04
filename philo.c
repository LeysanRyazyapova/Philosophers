#include "philo.h"

void	*life(void *philo)
{
	t_philo			*ph;
	unsigned int	time;

	ph = (t_philo *)philo;
	while (1)
	{
		if (ph->num % 2 == 0)
			even_eating(ph, time);
		else
			odd_eating(ph, time);
		timestamp_ms(ph->all.start, &time);
		ph->last_meal = time;
		timestamp_ms(ph->all.start, &time);
		printf("%u %d is sleeping\n", time, ph->num);
		mysleep(time, ph->all.start, ph->all.time_to_sleep);
		timestamp_ms(ph->all.start, &time);
		printf("%u %d is thinking\n", time, ph->num);
		waiting(ph->last_meal, ph->all.time_to_die,
			ph->all.start, ph->all.time_to_eat);
	}
	return (NULL);
}

void	make_threads(t_all all, int n, t_philo *philo)
{
	int				i;
	pthread_t		*thread;
	pthread_mutex_t	*mutex;

	thread = malloc(sizeof(pthread_t) * n);
	mutex = malloc(sizeof(pthread_mutex_t) * n);
	i = -1;
	while (++i < n)
		pthread_mutex_init(&mutex[i], NULL);
	i = -1;
	while (++i < n)
	{
		init_philo(mutex, i, &philo[i], n);
		philo[i].all = all;
		philo[i].last_meal = 0;
		if (n % 2 != 0 && philo[i].num == n)
			mysleep(0, philo[i].all.start, philo[i].all.time_to_eat * 2);
		pthread_create(&thread[i], NULL, life, &philo[i]);
		pthread_detach(thread[i]);
	}
}

void	check_die(t_philo *philo, int n)
{
	int				i;
	unsigned int	time;
	int				k;

	i = 0;
	k = 0;
	while (1)
	{
		if (i == n)
			i = 0;
		timestamp_ms(philo[i].all.start, &time);
		if ((int)(time - philo[i].last_meal) >= philo[i].all.time_to_die)
		{
			printf("%u %d died\n", time, philo[i].num);
			break ;
		}
		if (philo[i].all.number_to_eat != 0 && philo[i].all.counter == philo[i].all.number_to_eat + 1)
		{
			k++;
			if (k == n)
				break ;
		}		
		i++;
	}
}

int	init_main(char **argv, int argc, t_all *all)
{
	if(check_valid(argv[2]) || check_valid(argv[3]) || check_valid(argv[4])
		|| check_valid(argv[5]))
		return(1);
	all->time_to_die = ft_atoi(argv[2]);
	all->time_to_eat = ft_atoi(argv[3]);
	all->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		all->number_to_eat = ft_atoi(argv[5]);
	else
		all->number_to_eat = 0;
	get_time(&all->start);
	all->counter = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	int				phil_count;
	t_philo			*philo;
	t_all			all;

	if (argc == 5 || argc == 6)
	{
		if(check_valid(argv[1]))
		{
			printf("Wrong number of philosophers\n");
			return (0);
		}
		phil_count = ft_atoi(argv[1]);
		philo = malloc(sizeof(t_philo) * phil_count);
		if (init_main(argv, argc, &all))
		{
			printf("Wrong arguments\n");
			return (0);
		}
		make_threads(all, phil_count, philo);
		check_die(philo, phil_count);
	}
	printf("Wrong number of arguments\n");
	return (0);
}
