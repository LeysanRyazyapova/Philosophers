#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>
typedef struct s_all
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_to_eat;
	int				counter;
	int				i;
	unsigned int	start;
	pthread_mutex_t	*mutex_to_print;
}	t_all;
typedef struct s_philo
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_all			all;
	unsigned int	last_meal;
	int				num;
}	t_philo;
void	get_time(unsigned int *time);
void	timestamp_ms(unsigned int start, unsigned int *time);
int		right(int n, int phil_count);
void	init_philo(pthread_mutex_t *mutex, int number,
			t_philo *philo, int phil_count);
void	odd_eating(t_philo *philo, unsigned int	time);
void	even_eating(t_philo *philo, unsigned int	time);
void	waiting(unsigned int last_meal, unsigned int ttd,
			unsigned int start, unsigned int tte);
void	mysleep(unsigned int time, unsigned int start, unsigned int tts);
int		check_valid(char *str);
int		ft_atoi(const char *str);
#endif