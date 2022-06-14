#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "minitalk.h"

void	ft_send_str(pid_t pid, char *message);
void	ft_send_signal(pid_t pid, char chr);
void	ft_write_sig(int signum);

int main(int argc, char **argv)
{
	int		pid;
	char	*message;

	if (argc != 3)
	{
		printf("type => \"./client <pid> <string>\"\n");
		exit (1);
	}
	signal(SIGUSR1, (void *)ft_write_sig);
	signal(SIGUSR2, (void *)ft_write_sig);
	pid = ft_atoi(argv[1]);
	message = argv[2];
	ft_send_str(pid, message);
	usleep(10);
	while (1)
		pause();
}

void	ft_send_str(pid_t pid, char *message)
{
	while (*message)
	{
		ft_send_signal(pid, *message);
		++message;
	}
	ft_send_signal(pid, '\0');
}

void	ft_send_signal(pid_t pid, char chr)
{
	char			cnt;
	unsigned char	bit;

	cnt = 0;
	bit = 128;
	while (++cnt <= 8)
	{
		if ((chr & bit) == bit)
		{
			if (kill(pid, SIGUSR1) == -1)
				exit(1);
			pause();
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				exit(1);
			pause();
		}
		bit >>= 1;
	}
}

void	ft_write_sig(int signum)
{
	if (signum == SIGUSR1)
		write(1, ".", 1);
	else if (signum == SIGUSR2)
	{
		write(1, "done.\n", 6);
		exit (0);
	}
}