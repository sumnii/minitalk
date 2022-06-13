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
		chr = chr | 1;
	else
		chr = chr | 0;
	++bit_cnt;
	if (bit_cnt == 8)
	{
		write(1, &chr, 1);
		if (chr == 0)
		{
			kill(info->si_pid, SIGUSR2);
			write(1, "\n", 1);
		}
		bit_cnt = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main()
{
	struct sigaction s_sig;

	printf("server pid : ");
	printf("%d\n", getpid());
	s_sig.sa_flags = SA_SIGINFO;
	s_sig.sa_sigaction = ft_sigaction;
	sigaction(SIGUSR1, &s_sig, NULL);
	sigaction(SIGUSR2, &s_sig, NULL);
	while (1)
		pause();
}