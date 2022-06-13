#include <unistd.h>
#include <stdio.h>
#include "minitalk.h"

void	ft_get_signal(void);
void	*ft_write_sig(int signum);
void	test(int sig);

int	main()
{
	printf("server pid : ");
	printf("%d\n", getpid());
	signal(SIGUSR1, (void *)ft_write_sig);
	signal(SIGUSR2, (void *)ft_write_sig);
	while (1)
		pause();
}

void	*ft_write_sig(int signum)
{
	static char	chr = 0;
	static char	bit_cnt = 0;

	chr <<= 1;
	if (signum == SIGUSR1)
		chr = chr | 1;
	else
		chr = chr | 0;
	++bit_cnt;
	if (bit_cnt == 8)
	{
		write(1, &chr, 1);
		if (chr == 0)
			write(1, "\n", 1);
		bit_cnt = 0;
	}
	return (0);
}
