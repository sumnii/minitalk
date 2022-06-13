#include <unistd.h>
#include <stdio.h>
#include "minitalk.h"

void	ft_write_sig(int signum)
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
}

void	ft_sigaction(int signum, siginfo_t *info, void *ucp)
{
	static char	chr = 0;
	static char	bit_cnt = 0;

	chr <<= 1;
	if (signum == SIGUSR1)
		chr = chr | 1; // 0000 0001
	else
		chr = chr | 0; // 0000 0000
	++bit_cnt;
	if (bit_cnt == 8)
	{
		write(1, &chr, 1);
		kill(info->si_pid, SIGUSR1);
		usleep(50);
		if (chr == 0)
		{
			write(1, " null! ", 7);
			kill(info->si_pid, SIGUSR2);
			usleep(50);
			write(1, "\n", 1);
		}
		bit_cnt = 0;
	}
}

int	main()
{
	struct sigaction s_sig;

	printf("server pid : ");
	printf("%d\n", getpid());
//	signal(SIGUSR1, (void *)ft_write_sig);
//	signal(SIGUSR2, (void *)ft_write_sig);
	s_sig.sa_flags = SA_SIGINFO;
	s_sig.sa_sigaction = ft_sigaction;
	sigaction(SIGUSR1, &s_sig, NULL);
	sigaction(SIGUSR2, &s_sig, NULL);
	while (1)
		pause();
}