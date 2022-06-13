#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "minitalk.h"

void	ft_send_str(pid_t pid, char *message);
void	ft_send_signal(pid_t pid, char chr);

int main(int argc, char **argv)
{
	int	pid;
	char	*message;

	if (argc != 3)
	{
		printf("type => \"./client <pid> <string>\"\n");
		exit (1);
	}
	pid = ft_atoi(argv[1]);
	message = argv[2];
	ft_send_str(pid, message);
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
			usleep(50);
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				exit(1);
			usleep(50);
		}
		bit >>= 1;
	}
}